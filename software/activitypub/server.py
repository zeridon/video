"""
server.py — FOSDEM ActivityPub actor

Serveert FOSDEM-talks als ActivityPub Video-objecten die PeerTube-instances
kunnen volgen en optioneel redundant hosten.

Vereisten:
    pip install fastapi uvicorn cryptography

Configuratie via environment-variabelen (of .env):
    AP_BASE_URL      https://fosdem.example.com   (geen trailing slash)
    AP_EVENTS_JSON   pad naar de JSON gegenereerd door fosdem_parse.py
    AP_STATE_DB      pad naar SQLite state-file   (default: state.db)
    AP_PRIVKEY_PEM   pad naar RSA private key     (default: privkey.pem)

Quickstart:
    # 1. Genereer een keypair
    python keygen.py

    # 2. Start de server
    AP_BASE_URL=https://fosdem.example.com \
    AP_EVENTS_JSON=fosdem2026_mp4.json \
    uvicorn server:app --host 0.0.0.0 --port 8000
"""

import base64
import contextlib
import hashlib
import json
import os
import sqlite3
import time
import urllib.request
from datetime import datetime, timezone
from typing import Optional

from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import padding
from fastapi import FastAPI, HTTPException, Request, Response
from fastapi.responses import JSONResponse

# ---------------------------------------------------------------------------
# Config
# ---------------------------------------------------------------------------

BASE_URL    = os.environ.get("AP_BASE_URL",    "https://fosdem.markvdb.be").rstrip("/")
EVENTS_JSON = os.environ.get("AP_EVENTS_JSON", "fosdem2026_mp4.json")
STATE_DB    = os.environ.get("AP_STATE_DB",    "state.db")
PRIVKEY_PEM = os.environ.get("AP_PRIVKEY_PEM", "privkey.pem")

ACTOR_ID    = f"{BASE_URL}/actor"
INBOX_URL   = f"{BASE_URL}/inbox"
OUTBOX_URL  = f"{BASE_URL}/outbox"
PUBKEY_URL  = f"{ACTOR_ID}#main-key"

PAGE_SIZE   = 50   # events per outbox-pagina

AP_CONTENT_TYPE = "application/activity+json"

AP_CONTEXT = [
    "https://www.w3.org/ns/activitystreams",
    "https://w3id.org/security/v1",
    {"RsaSignature2017": "https://w3id.org/security#RsaSignature2017"},
    {
        "pt":  "https://joinpeertube.org/ns#",
        "sc":  "http://schema.org/",
        "Hashtag":               "as:Hashtag",
        "category":              "sc:category",
        "licence":               "sc:license",
        "subtitleLanguage":      "sc:subtitleLanguage",
        "automaticallyGenerated": "pt:automaticallyGenerated",
        "sensitive":             "as:sensitive",
        "language":              "sc:inLanguage",
        "identifier":            "sc:identifier",
        "isLiveBroadcast":       "sc:isLiveBroadcast",
        "liveSaveReplay":        {"@type": "sc:Boolean", "@id": "pt:liveSaveReplay"},
        "permanentLive":         {"@type": "sc:Boolean", "@id": "pt:permanentLive"},
        "latencyMode":           {"@type": "sc:Number",  "@id": "pt:latencyMode"},
        "Infohash":              "pt:Infohash",
        "SensitiveTag":          "pt:SensitiveTag",
        "aspectRatio":           {"@type": "sc:Float",   "@id": "pt:aspectRatio"},
        "uuid":                  {"@type": "sc:identifier", "@id": "pt:uuid"},
        "originallyPublishedAt": "sc:datePublished",
        "schedules":             "sc:eventSchedule",
        "startDate":             "sc:startDate",
        "embedUrl":              "sc:embedUrl",
        "uploadDate":            "sc:uploadDate",
        "hasParts":              "sc:hasParts",
        "playerSettings":        "pt:playerSettings",
        "views":                 {"@type": "sc:Number",  "@id": "pt:views"},
        "state":                 {"@type": "sc:Number",  "@id": "pt:state"},
        "size":                  {"@type": "sc:Number",  "@id": "pt:size"},
        "fps":                   {"@type": "sc:Number",  "@id": "pt:fps"},
        "canReply":              "pt:canReply",
        "commentsPolicy":        {"@type": "sc:Number",  "@id": "pt:commentsPolicy"},
        "downloadEnabled":       {"@type": "sc:Boolean", "@id": "pt:downloadEnabled"},
        "waitTranscoding":       {"@type": "sc:Boolean", "@id": "pt:waitTranscoding"},
        "support":               {"@type": "sc:Text",    "@id": "pt:support"},
        "likes":                 {"@id": "as:likes",    "@type": "@id"},
        "dislikes":              {"@id": "as:dislikes", "@type": "@id"},
        "shares":                {"@id": "as:shares",   "@type": "@id"},
        "comments":              {"@id": "as:comments", "@type": "@id"},
        "PropertyValue":         "sc:PropertyValue",
        "value":                 "sc:value",
    },
]

CHANNEL_ID = f"{BASE_URL}/channel"

LICENCE_MAP = {
    "cc by":       {"identifier": "1", "name": "Attribution"},
    "cc by-sa":    {"identifier": "2", "name": "Attribution - Share Alike"},
    "cc by-nd":    {"identifier": "3", "name": "Attribution - No Derivatives"},
    "cc by-nc":    {"identifier": "4", "name": "Attribution - Non Commercial"},
    "cc by-nc-sa": {"identifier": "5", "name": "Attribution - Non Commercial - Share Alike"},
    "cc by-nc-nd": {"identifier": "6", "name": "Attribution - Non Commercial - No Derivatives"},
    "cc0":         {"identifier": "7", "name": "Public Domain Dedication"},
}

def duration_to_seconds(raw: str) -> str:
    """Convert ISO 8601 duration to PTxxxS format PeerTube requires."""
    import re
    if not raw:
        return "PT0S"
    # Already in seconds format
    if re.fullmatch(r'PT\d+S', raw):
        return raw
    total = 0
    for value, unit in re.findall(r'(\d+)([HMS])', raw.upper()):
        v = int(value)
        if unit == 'H':
            total += v * 3600
        elif unit == 'M':
            total += v * 60
        elif unit == 'S':
            total += v
    return f"PT{total}S"


def slug_to_uuid4(slug: str) -> str:
    """Derive a deterministic UUID v4 from a slug via SHA-256.
    Forces version=4 and variant=RFC4122 bits so PeerTube accepts it."""
    import hashlib
    h = hashlib.sha256(slug.encode()).digest()
    b = bytearray(h[:16])
    b[6] = (b[6] & 0x0F) | 0x40  # version 4
    b[8] = (b[8] & 0x3F) | 0x80  # variant RFC4122
    return (
        f"{b[0:4].hex()}-{b[4:6].hex()}-{b[6:8].hex()}"
        f"-{b[8:10].hex()}-{b[10:16].hex()}"
    )


def resolve_licence(raw):
    if not raw:
        return None
    label = raw.get("label", "").lower()
    for key, val in LICENCE_MAP.items():
        if key in label:
            return val
    return None


# ---------------------------------------------------------------------------
# Data laden
# ---------------------------------------------------------------------------

def load_events() -> tuple[dict, list[dict]]:
    with open(EVENTS_JSON, encoding="utf-8") as f:
        data = json.load(f)
    return data["conference"], data["events"]


CONFERENCE, EVENTS = load_events()
# Slug → event index voor snelle lookup
SLUG_INDEX = {e["slug"]: i for i, e in enumerate(EVENTS)}


# ---------------------------------------------------------------------------
# Crypto — RSA keypair + HTTP Signatures
# ---------------------------------------------------------------------------

def load_private_key():
    with open(PRIVKEY_PEM, "rb") as f:
        return serialization.load_pem_private_key(f.read(), password=None)


def load_public_key_pem() -> str:
    key = load_private_key()
    return key.public_key().public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo,
    ).decode()


def sign_request(method: str, url: str, body: bytes) -> dict[str, str]:
    """
    Genereert HTTP Signature headers voor een uitgaand verzoek.
    Implementeert de subset die Mastodon/PeerTube verwacht.
    """
    from urllib.parse import urlparse
    parsed  = urlparse(url)
    path    = parsed.path + (f"?{parsed.query}" if parsed.query else "")
    host    = parsed.netloc
    date    = datetime.now(timezone.utc).strftime("%a, %d %b %Y %H:%M:%S GMT")
    digest  = "SHA-256=" + base64.b64encode(hashlib.sha256(body).digest()).decode()

    signed_string = (
        f"(request-target): {method.lower()} {path}\n"
        f"host: {host}\n"
        f"date: {date}\n"
        f"digest: {digest}"
    )

    privkey   = load_private_key()
    signature = privkey.sign(signed_string.encode(), padding.PKCS1v15(), hashes.SHA256())
    sig_b64   = base64.b64encode(signature).decode()

    sig_header = (
        f'keyId="{PUBKEY_URL}",'
        f'headers="(request-target) host date digest",'
        f'algorithm="rsa-sha256",'
        f'signature="{sig_b64}"'
    )

    return {
        "Host":        host,
        "Date":        date,
        "Digest":      digest,
        "Signature":   sig_header,
        "Content-Type": AP_CONTENT_TYPE,
    }


def send_signed(method: str, url: str, body: dict) -> None:
    """Stuur een gesigneerd ActivityPub-verzoek."""
    raw = json.dumps(body).encode()
    headers = sign_request(method, url, raw)
    req = urllib.request.Request(url, data=raw, headers=headers, method=method.upper())
    try:
        with urllib.request.urlopen(req, timeout=10):
            pass
    except Exception as exc:
        print(f"[warn] {method} {url} → {exc}")


# ---------------------------------------------------------------------------
# State — SQLite voor follows
# ---------------------------------------------------------------------------

@contextlib.contextmanager
def db():
    con = sqlite3.connect(STATE_DB)
    con.row_factory = sqlite3.Row
    try:
        yield con
        con.commit()
    finally:
        con.close()


def init_db() -> None:
    with db() as con:
        con.execute("""
            CREATE TABLE IF NOT EXISTS followers (
                actor_id   TEXT PRIMARY KEY,
                inbox_url  TEXT NOT NULL,
                followed_at INTEGER NOT NULL
            )
        """)
        con.execute("""
            CREATE TABLE IF NOT EXISTS inbox_log (
                id         INTEGER PRIMARY KEY AUTOINCREMENT,
                received_at INTEGER NOT NULL,
                body       TEXT
            )
        """)


def get_followers() -> list[dict]:
    with db() as con:
        rows = con.execute("SELECT actor_id, inbox_url FROM followers").fetchall()
    return [dict(r) for r in rows]


def add_follower(actor_id: str, inbox_url: str) -> None:
    with db() as con:
        con.execute(
            "INSERT OR REPLACE INTO followers (actor_id, inbox_url, followed_at) VALUES (?, ?, ?)",
            (actor_id, inbox_url, int(time.time())),
        )


def remove_follower(actor_id: str) -> None:
    with db() as con:
        con.execute("DELETE FROM followers WHERE actor_id = ?", (actor_id,))


# ---------------------------------------------------------------------------
# ActivityPub object builders
# ---------------------------------------------------------------------------

def build_actor() -> dict:
    return {
        "@context": AP_CONTEXT,
        "type":     "Person",
        "id":       ACTOR_ID,
        "name":     CONFERENCE.get("title", "FOSDEM"),
        "preferredUsername": "fosdem",
        "summary":  f"FOSDEM video archive — {CONFERENCE.get('city', 'Brussels')}",
        "url":      "https://fosdem.org",
        "inbox":    INBOX_URL,
        "outbox":   OUTBOX_URL,
        "followers": f"{BASE_URL}/actor/followers",
        "following": f"{BASE_URL}/actor/following",
        "publicKey": {
            "id":           f"{ACTOR_ID}#main-key",
            "owner":        ACTOR_ID,
            "publicKeyPem": load_public_key_pem(),
        },
    }


def build_channel() -> dict:
    return {
        "@context": AP_CONTEXT,
        "type":     "Group",
        "id":       CHANNEL_ID,
        "name":     f"{CONFERENCE.get('title', 'FOSDEM')} Videos",
        "preferredUsername": "fosdem_channel",
        "summary":  f"Video channel for {CONFERENCE.get('title', 'FOSDEM')}",
        "url":      "https://fosdem.org",
        "inbox":    INBOX_URL,
        "outbox":   OUTBOX_URL,
        "followers": f"{BASE_URL}/channel/followers",
        "attributedTo": [{"type": "Person", "id": ACTOR_ID}],
        "publicKey": {
            "id":           f"{CHANNEL_ID}#main-key",
            "owner":        CHANNEL_ID,
            "publicKeyPem": load_public_key_pem(),
        },
    }


def build_video_object(event: dict) -> dict:
    video = event.get("video", {})
    url_links = []

    # peertube_format_flag verplicht zodat PeerTube de link als afspeelbaar herkent
    format_attachment = [
        {"type": "PropertyValue", "name": "peertube_format_flag", "value": "web-video"},
    ]

    if video.get("mp4"):
        url_links.append({
            "type": "Link", "mediaType": "video/mp4",
            "href": video["mp4"], "height": 1080,
            "attachment": format_attachment,
        })
    if video.get("av1_webm"):
        url_links.append({
            "type": "Link", "mediaType": "video/webm",
            "href": video["av1_webm"], "height": 1080,
            "attachment": format_attachment,
        })
    if video.get("vp9_webm"):
        url_links.append({
            "type": "Link", "mediaType": "video/webm",
            "href": video["vp9_webm"], "height": 1080,
            "attachment": format_attachment,
        })

    tags = [{"type": "Hashtag", "name": "#fosdem"}]
    if event.get("track_slug"):
        tags.append({"type": "Hashtag", "name": f"#{event['track_slug']}"})

    subtitle_language = []
    if video.get("subtitles"):
        subtitle_language.append({
            "identifier": event.get("language", "en"),
            "name":       event.get("language", "en").upper(),
            "url": [{"type": "Link", "mediaType": "text/vtt", "href": video["subtitles"]}],
        })

    content = event.get("abstract", "")
    if event.get("persons"):
        content = (content + "\n\nSpeakers: " + ", ".join(event["persons"])).strip()

    obj = {
        "@context":    AP_CONTEXT,
        "type":        "Video",
        "id":          f"{BASE_URL}/videos/{event['slug']}",
        "uuid":        slug_to_uuid4(event.get("guid") or event["slug"]),
        "name":        event["title"],
        # Person eerst, Group tweede — volgorde conform PeerTube-voorbeeld
        "attributedTo": [
            {"type": "Person", "id": ACTOR_ID},
            {"type": "Group",  "id": CHANNEL_ID},
        ],
        "audience":    CHANNEL_ID,
        "to":          ["https://www.w3.org/ns/activitystreams#Public", CHANNEL_ID],
        "cc":          [f"{BASE_URL}/channel/followers", f"{BASE_URL}/actor/followers"],
        "url":         url_links,
        "tag":         tags,
        "language": {
            "identifier": event.get("language", "en"),
            "name":       event.get("language", "en").upper(),
        },
        "category": {
            "identifier": "0",
            "name":       event.get("track", ""),
        },
        "duration":    duration_to_seconds(event.get("duration", "PT0S")),
        "views":       0,
        "sensitive":   False,
        "summary":     None,
        "waitTranscoding": False,
        "isLiveBroadcast": False,
        "liveSaveReplay":  None,
        "permanentLive":   None,
        "latencyMode":     None,
        "state":       1,
        "canReply":    None,
        "commentsPolicy": 2,
        "downloadEnabled": True,
        "published":   event.get("date", ""),
        "updated":     event.get("date", ""),
        "originallyPublishedAt": None,
        "mediaType":   "text/markdown",
        "content":     content,
        "support":     None,
        "aspectRatio": None,
        "subtitleLanguage": subtitle_language,
        "schedules":   [],
        "icon": [
            {
                "type": "Image",
                "url": "https://archive.fosdem.org/2016/assets/style/logo-gear-7204a6874eb0128932db10ff4030910401ac06f4e907f8b4a40da24ba592b252.png",
                "mediaType": "image/png",
                "width": 200,
                "height": 200,
            }
        ],
        "likes":    f"{BASE_URL}/videos/{event['slug']}/likes",
        "dislikes": f"{BASE_URL}/videos/{event['slug']}/dislikes",
        "shares":   f"{BASE_URL}/videos/{event['slug']}/announces",
        "comments": f"{BASE_URL}/videos/{event['slug']}/comments",
    }

    licence = resolve_licence(event.get("licence"))
    if licence:
        obj["licence"] = licence

    return obj


def build_create_activity(event: dict) -> dict:
    return {
        "@context": AP_CONTEXT,
        "type":     "Create",
        "id":       f"{BASE_URL}/activities/create/{event['slug']}",
        "actor":    ACTOR_ID,
        "to":       ["https://www.w3.org/ns/activitystreams#Public", CHANNEL_ID],
        "cc":       [f"{BASE_URL}/channel/followers", f"{BASE_URL}/actor/followers"],
        "object":   build_video_object(event),
        "published": event.get("date", ""),
    }


# ---------------------------------------------------------------------------
# FastAPI app
# ---------------------------------------------------------------------------

app = FastAPI(title="FOSDEM ActivityPub", docs_url=None, redoc_url=None)


def ap_response(data: dict, status: int = 200) -> Response:
    return Response(
        content=json.dumps(data, ensure_ascii=False),
        status_code=status,
        media_type=AP_CONTENT_TYPE,
    )


# --- WebFinger ---

@app.get("/.well-known/webfinger")
async def webfinger(resource: str = ""):
    """
    Laat clients fosdem@<domein> resolven naar de actor.
    Voorbeeld: ?resource=acct:fosdem@fosdem.example.com
    """
    expected = f"acct:fosdem@{BASE_URL.split('://',1)[-1]}"
    if resource and resource != expected:
        raise HTTPException(404, "Resource niet gevonden")
    return JSONResponse({
        "subject": expected,
        "links": [{
            "rel":  "self",
            "type": AP_CONTENT_TYPE,
            "href": ACTOR_ID,
        }],
    })


# --- Actor ---

@app.get("/actor")
async def actor():
    return ap_response(build_actor())

@app.get("/channel")
async def channel():
    return ap_response(build_channel())


# --- Followers / following ---

@app.get("/followers")
@app.get("/actor/followers")
@app.get("/channel/followers")
async def followers():
    return ap_response({
        "@context": "https://www.w3.org/ns/activitystreams",
        "type": "OrderedCollection", "totalItems": 0, "orderedItems": [],
    })

@app.get("/actor/following")
async def following():
    return ap_response({
        "@context": "https://www.w3.org/ns/activitystreams",
        "type": "OrderedCollection", "totalItems": 0, "orderedItems": [],
    })

@app.get("/actor/outbox")
async def actor_outbox():
    return ap_response({
        "@context": "https://www.w3.org/ns/activitystreams",
        "type": "OrderedCollection", "totalItems": 0, "orderedItems": [],
    })


# --- Outbox ---

def events_with_video():
    return [
        e for e in EVENTS
        if e.get("video", {}).get("mp4")
        or e.get("video", {}).get("av1_webm")
        or e.get("video", {}).get("vp9_webm")
    ]


@app.get("/outbox")
async def outbox(page: Optional[int] = None):
    publishable = events_with_video()
    total = len(publishable)

    if page is None:
        # Collection-index zonder items (PeerTube-conventie)
        return ap_response({
            "@context":   "https://www.w3.org/ns/activitystreams",
            "type":       "OrderedCollection",
            "id":         OUTBOX_URL,
            "totalItems": total,
            "first":      f"{OUTBOX_URL}?page=1",
            "last":       f"{OUTBOX_URL}?page={max(1, -(-total // PAGE_SIZE))}",
        })

    start = (page - 1) * PAGE_SIZE
    end   = start + PAGE_SIZE
    slice_  = publishable[start:end]
    items   = [build_create_activity(e) for e in slice_]
    max_page = max(1, -(-total // PAGE_SIZE))

    result = {
        "@context":   "https://www.w3.org/ns/activitystreams",
        "type":       "OrderedCollectionPage",
        "id":         f"{OUTBOX_URL}?page={page}",
        "partOf":     OUTBOX_URL,
        "totalItems": total,
        "orderedItems": items,
    }
    if page > 1:
        result["prev"] = f"{OUTBOX_URL}?page={page - 1}"
    if page < max_page:
        result["next"] = f"{OUTBOX_URL}?page={page + 1}"

    return ap_response(result)


# --- Individueel Video-object ---

@app.get("/videos/{slug}")
async def video(slug: str):
    idx = SLUG_INDEX.get(slug)
    if idx is None:
        raise HTTPException(404, "Video niet gevonden")
    event = EVENTS[idx]
    v = event.get("video", {})
    if not (v.get("mp4") or v.get("av1_webm") or v.get("vp9_webm")):
        raise HTTPException(404, "Video niet beschikbaar")
    return ap_response(build_video_object(event))


@app.get("/videos/{slug}/likes")
@app.get("/videos/{slug}/dislikes")
@app.get("/videos/{slug}/announces")
@app.get("/videos/{slug}/comments")
async def video_collection(slug: str):
    if slug not in SLUG_INDEX:
        raise HTTPException(404, "Video niet gevonden")
    return ap_response({
        "@context": "https://www.w3.org/ns/activitystreams",
        "type": "OrderedCollection",
        "totalItems": 0,
        "orderedItems": [],
    })


# --- Inbox ---

@app.post("/inbox")
async def inbox(request: Request):
    """
    Verwerkt inkomende ActivityPub-activiteiten.
    Relevant: Follow → stuur Accept + sla follower op.
              Undo(Follow) → verwijder follower.
    Al het andere wordt gelogd en genegeerd.
    """
    body = await request.body()

    # Log voor debugging
    with db() as con:
        con.execute(
            "INSERT INTO inbox_log (received_at, body) VALUES (?, ?)",
            (int(time.time()), body.decode(errors="replace")),
        )

    try:
        activity = json.loads(body)
    except json.JSONDecodeError:
        raise HTTPException(400, "Geen geldige JSON")

    a_type  = activity.get("type", "")
    actor   = activity.get("actor", "")
    act_id  = activity.get("id", "")

    # --- Follow ---
    if a_type == "Follow":
        # Haal inbox-URL van de follower op
        inbox_url = await _resolve_inbox(actor)
        if inbox_url:
            add_follower(actor, inbox_url)

        # Stuur Accept terug
        accept = {
            "@context": "https://www.w3.org/ns/activitystreams",
            "type":    "Accept",
            "id":      f"{BASE_URL}/activities/accept/{int(time.time())}",
            "actor":   ACTOR_ID,
            "object":  activity,
        }
        if inbox_url:
            import threading
            threading.Thread(
                target=send_signed, args=("POST", inbox_url, accept), daemon=True
            ).start()

        return Response(status_code=200)

    # --- Undo(Follow) ---
    if a_type == "Undo":
        obj = activity.get("object", {})
        if isinstance(obj, dict) and obj.get("type") == "Follow":
            remove_follower(actor)
        return Response(status_code=200)

    # Al het andere: 200 OK, verder niets
    return Response(status_code=200)


async def _resolve_inbox(actor_url: str) -> Optional[str]:
    """Haal de inbox-URL op van een externe actor."""
    try:
        req = urllib.request.Request(actor_url)
        req.add_header("Accept", AP_CONTENT_TYPE)
        req.add_header("User-Agent", "fosdem-ap-bot/1.0")
        with urllib.request.urlopen(req, timeout=8) as resp:
            data = json.load(resp)
        return data.get("inbox")
    except Exception as exc:
        print(f"[warn] kon inbox niet resolven voor {actor_url}: {exc}")
        return None


# ---------------------------------------------------------------------------
# Startup
# ---------------------------------------------------------------------------

@app.on_event("startup")
async def startup():
    init_db()
    print(f"Actor:  {ACTOR_ID}")
    print(f"Events: {len(EVENTS)}")
    print(f"WebFinger: acct:fosdem@{BASE_URL.split('://',1)[-1]}")
