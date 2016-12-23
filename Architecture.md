# General overview of the video streaming/recording architecture for FOSDEM

## TLDR

camera & presenter laptop -> videoboxes -> voctops -> restreamer -> caches <- browsers

## Elements

The main elements are:

* Cameras and presenter laptops (sources for video)
* Microphones
* Videoboxes
* Voctops (laptops with voctomix)
* Dumpers & pushers
* Restreamers

## In-room setup

Better described in the instruction manual.

Here we have the microphones connected to an audio mixer (in the case of the smallest rooms, the mixer is skipped), which goes then in one of the inputs of the camera. The camera is connected to the camera videobox over HDMI, and the videobox records the input and streams it in MPEG-TS over multicast UDP. The presenter's laptop is connected to the presenter videobox, which also records the input and streams it in the same way. 

For the hardware in the videoboxes, see `hardware/README.md`.

For the software running on the videoboxes and their configs, see `software/ansible/playbooks/roles/videobox/`.

## Video mixing

All the voctops are stored in a central location, and each one runs an instance of voctomix (https://github.com/voc/voctomix/).

Each voctomix is fed with three sources:

* camera
* presenter
* background

The camera and presenter sources are fed using ffmpeg from the multicast UDP stream, the background is also fed with ffmpeg, using a raw video image. 

The output of voctomix is encoded to H.264 and sent again as MPEG-TS over multicast UDP.

All the voctomix scripts can be seen in `software/ansible/playbooks/roles/voctop/files/scripts/`.

## Video streaming and recording

The streams are forwarded to the main restreamer in (some hosting provider) and the backup on by the voctops, from the streamed-out H.264 UDP stream, using the `streamcast.sh` script.

The recordings of the final material are done on the main restreamer and on a separate laptop with the ansible role `stream-dumper`, from the same UDP stream.

The main restreamer is nginx with the RTMP module (https://github.com/arut/nginx-rtmp-module) and receives the streams via RTMP. It makes there the primary recordings and server HLS to the caching servers.

The end-users connect to the caching servers and see the streams via HLS.
