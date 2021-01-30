## Diagnostics
From ingestion to website, you want to check where things go wrong
- Is the prerecorded file there?

  ```ssh root@<track>-vocto.video.fosdem.org ls -lh /mnt/video/*.mp4```
- Is the prerecorded file a sensible length?

  ```ssh root@<track>-vocto.video.fosdem.org ffprobe /mnt/video/<penta_id>.mp4 |& grep Duration```
- Are all talks for this room properly scheduled?

```ssh root@<track>-vocto.video.fosdem.org systemctl list-timers```
- Is the output of the voctomix mixer nominal?

  ```mpv http://<track>-vocto.video.fosdem.org:8899 checks the output of the vocto mixer for the room```
- Is the public stream output nominal?

  ```mpv https://stream.fosdem.org/<track>.m3u8```
