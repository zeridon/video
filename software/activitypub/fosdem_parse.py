"""
fosdem_parse.py

Parst een FOSDEM Pentabarf schedule XML en exporteert alle events
die een H.264 MP4-video hebben naar JSON.

De videolinks worden rechtstreeks uit de XML gehaald (geen HEAD-checks
nodig — video.fosdem.org publiceert ze pas in de XML als ze beschikbaar zijn).

Gebruik:
    python fosdem_parse.py schedule.xml
    python fosdem_parse.py schedule.xml --output events.json
    python fosdem_parse.py https://fosdem.org/2026/schedule/xml
"""

import argparse
import html
import json
import re
import sys
import urllib.request
from xml.etree import ElementTree as ET


def resolve_redirect(url: str, timeout: int = 10) -> str:
    """Follow redirects and return the final URL, or the original on failure."""
    try:
        req = urllib.request.Request(url, method="HEAD")
        req.add_header("User-Agent", "fosdem-ap-bot/1.0")
        with urllib.request.urlopen(req, timeout=timeout) as r:
            return r.url
    except Exception as exc:
        print(f"[warn] kon redirect niet volgen voor {url}: {exc}", file=sys.stderr)
        return url


def strip_html(text: str) -> str:
    text = re.sub(r"<[^>]+>", " ", text or "")
    text = html.unescape(text)
    return re.sub(r"\s+", " ", text).strip()


def duration_to_iso(s: str) -> str:
    if not s:
        return "PT0M"
    parts = s.split(":")
    h, m = int(parts[0]), int(parts[1]) if len(parts) > 1 else (0, int(parts[0]))
    return f"PT{h}H{m}M" if h else f"PT{m}M"


def txt(el, tag: str, default: str = "") -> str:
    c = el.find(tag) if el is not None else None
    return (c.text or "").strip() if c is not None else default


LICENCE_MAP = {
    "cc by-sa":   {"id": 2, "label": "Attribution - Share Alike"},
    "cc by-nd":   {"id": 3, "label": "Attribution - No Derivatives"},
    "cc by-nc-sa":{"id": 5, "label": "Attribution - Non Commercial - Share Alike"},
    "cc by-nc-nd":{"id": 6, "label": "Attribution - Non Commercial - No Derivatives"},
    "cc by-nc":   {"id": 4, "label": "Attribution - Non Commercial"},
    "cc by":      {"id": 1, "label": "Attribution"},
    "cc0":        {"id": 7, "label": "Public Domain Dedication"},
}


def resolve_licence(raw: str):
    if not raw:
        return None
    low = raw.lower()
    for key, val in LICENCE_MAP.items():
        if key in low:
            return val
    return None


def load_xml(source: str) -> ET.Element:
    if source.startswith("http://") or source.startswith("https://"):
        print(f"Fetching {source} …", file=sys.stderr)
        req = urllib.request.Request(source)
        req.add_header("User-Agent", "fosdem-ap-bot/1.0")
        with urllib.request.urlopen(req, timeout=30) as resp:
            data = resp.read()
        return ET.fromstring(data)
    else:
        return ET.parse(source).getroot()


def parse(root: ET.Element) -> dict:
    conf_el = root.find("conference")

    # Persons index: id → naam
    persons = {}
    for p in root.findall(".//persons/person"):
        pid = int(p.get("id", 0))
        name = txt(p, "n")
        if name:
            persons[pid] = name

    events = []
    skipped = 0

    for day in root.findall("day"):
        for room_el in day.findall("room"):
            room_name = room_el.get("name", "").strip()
            room_slug = room_el.get("slug", room_name.lower()).strip()

            for ev in room_el.findall("event"):
                slug = txt(ev, "slug")
                if not slug:
                    continue

                # Haal alle links op uit <links>
                all_links = [
                    l.get("href", "").strip()
                    for l in ev.findall(".//links/link")
                    if l.get("href", "").strip()
                ]

                mp4_links = [l for l in all_links if l.endswith(".mp4")]
                if not mp4_links:
                    skipped += 1
                    continue

                av1_links = [l for l in all_links if ".av1.webm" in l]
                vp9_links = [l for l in all_links if ".vp9.webm" in l]
                vtt_links = [l for l in all_links if l.endswith(".vtt")]

                pnames = []
                for p in ev.findall(".//persons/person"):
                    pid = int(p.get("id", 0))
                    name = persons.get(pid, (p.text or "").strip())
                    if name:
                        pnames.append(name)

                events.append({
                    "id":          int(ev.get("id", 0)),
                    "guid":        ev.get("guid", ""),
                    "slug":        slug,
                    "title":       txt(ev, "title"),
                    "subtitle":    txt(ev, "subtitle"),
                    "room":        room_name,
                    "room_slug":   room_slug,
                    "track":       txt(ev, "track"),
                    "type":        txt(ev, "type"),
                    "date":        txt(ev, "date"),
                    "duration":    duration_to_iso(txt(ev, "duration")),
                    "abstract":    strip_html(txt(ev, "abstract")),
                    "description": strip_html(txt(ev, "description")),
                    "language":    txt(ev, "language") or "en",
                    "licence":     resolve_licence(txt(ev, "licence")),
                    "url":         txt(ev, "url"),
                    "persons":     pnames,
                    "video": {
                        "mp4":      resolve_redirect(mp4_links[0]),
                        "av1_webm": resolve_redirect(av1_links[0]) if av1_links else None,
                        "vp9_webm": resolve_redirect(vp9_links[0]) if vp9_links else None,
                        "subtitles": vtt_links[0] if vtt_links else None,
                    },
                })

    print(f"Events met mp4:           {len(events)}", file=sys.stderr)
    print(f"Events zonder mp4:        {skipped}", file=sys.stderr)

    return {
        "conference": {
            "acronym": txt(conf_el, "acronym"),
            "title":   txt(conf_el, "title"),
            "venue":   txt(conf_el, "venue"),
            "city":    txt(conf_el, "city"),
            "start":   txt(conf_el, "start"),
            "end":     txt(conf_el, "end"),
        },
        "events": events,
    }


def main():
    parser = argparse.ArgumentParser(
        description="Exporteer FOSDEM Pentabarf XML naar JSON (enkel events met mp4)"
    )
    parser.add_argument("source", help="Pad naar schedule.xml of URL")
    parser.add_argument("--output", "-o", default=None,
                        help="Outputbestand (default: stdout)")
    args = parser.parse_args()

    root = load_xml(args.source)
    data = parse(root)
    out  = json.dumps(data, indent=2, ensure_ascii=False)

    if args.output:
        with open(args.output, "w", encoding="utf-8") as f:
            f.write(out)
        print(f"Geschreven naar {args.output}", file=sys.stderr)
    else:
        print(out)


if __name__ == "__main__":
    main()
