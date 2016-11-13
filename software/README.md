# Software Architecture

The software hierarchy is dictated by 2 main goals: _recording_ and _streaming_
of the video streams encoded inside the box.

## Video boxes

The video boxes are the boxes we deploy to each room. These will run ffmpeg to
grab the output from the H.264 encoders and send that to our voctocore servers.

We are currently using a "vanilla" Bananian Linux 16.04 as our base system.
Additional software is distributed and installed via Ansible.

Ultimately, we would like to move to Debian, but for the time being this will
do.

If you want to realisticly fake the streaming output of a video box, that is easy!
<pre>
youtube-dl -f 22 https://www.youtube.com/watch?v=T6AEhM1GWvw -o 720p.mp4
ffmpeg -i 720p.mp4 -c copy -f mpegts udp://227.0.0.2:9000
</pre>

Testing your stream is easy:
<pre>
mpv udp://227.0.0.2:9000
</pre>

## Streaming

