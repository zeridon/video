# Experiment: ActivityPub for PeerTube
The following steps set up an experimental ActivityPub server that can be federated with PeerTube. The video metadata and subtitles get imported and are searchable. The actual videos do not play for some reason to still be examined.

## Set up the experimental ActivityPub server
- Prepare the environment
<pre>
apt install certbot nginx python3.13-venv
certbot certonly -d fosdem.markvdb.be
python3 -m venv ~/.venv/fosdemfans
. ~/.venv/fosdemfans/bin/activate
pip install fastapi uvicorn cryptography
</pre>
- Get the FOSDEM schedule: <pre>wget -O schedule.xml https://fosdem.org/2026/schedule/xml</pre>
- Get a pub and private key for the PeerTube specific stuff:
<pre>python keygen.py</pre>
- Convert the parts of the schedule xml with video file links to json: <pre>python fosdem_parse.py schedule.xml --output fosdem2026_mp4.json</pre>
- Start the uvicorn server:
<pre>AP_BASE_URL=https://fosdem.markvdb.be AP_EVENTS_JSON=fosdem2026_mp4.json uvicorn server:app --host 0.0.0.0 --port 8000</pre>
- Get a letsencrypt certificate.
- Set up nginx according to the example config in this dir.

## Set up a PeerTube server
- Set up according to official PeerTube docker setup docs.
- Federate with the ActivityPub server:
  - Go to https://peertube.markvdb.be/admin/settings/follows/following-list .
  - Follow fosdem@fosdem.markvdb.be .
  - Reload and notice the federation request has been accepted.
  - Go to the front page. The video metadata become visible and the subtitles can be seen, but the video does not play, nor is the preview image visible.
