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

## Streaming

More information soon.
