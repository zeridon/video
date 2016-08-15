#Software Architecture

The software hierarchy is dictated by 2 main goals: _recording_ and _streaming_ of the video streams encoded inside the box.

An external server is used to keep backups of the recordings as they are made, and to serve the video streams to the broader audience outside of FOSDEM premises.

Status monitoring is an aspect of the software that has been set up last-minute during FOSDEM 2016, and as development progresses we want to make this an essential integrated element of the software

After the event we have put a lot of effort into the post-processing of the recorded videofiles, and the scripts and files used for this will be documented here as well.

##Video Boxes

All software on the boxes runs on the Banana Pi, registered as a systemd service. The systemd services are discussed below, ordered by type.

###Recording

Recording is started by the `recording.service` service file. This script starts the bmd-streamer software from the /root/directory, it then starts the `tsSink.sh` script to parse the video data as it arrives.

####recording.service
The options specified for the bmd-streamer program denote the following:

* `-f /root/` tells the executable where the bmd firmware is found. The software looks here for the `bmd-atemtvstudio.bin` and the `bmd-h264prorecorder.bin` files.
* `-B` tells the executable to not use B-Frames in its encoding. This enhances the suitability of the output stream for live.
* `-S hdmi` tells the executable the executable on which source it should listen for video data.
* `-k 1000` tells the executable to generate a keyframe every second.
* `-x /root/tsSink.sh` tells the executable that instead of writing the contents to standard output, it should fork a new process, and pipe the video data (in ts) to this script.

####tsSink.sh

This script records the data to a file on the ssd of the box. It uses `tee`, but pipes the results to `/dev/null/`. This script was intended to do more, but changed at the last moment.

###Streaming

The streaming is started by the `streaming.service` file. This in turn only starts the `streaming.sh` script, without further options. We will therefore only discuss this script. The script pushes to a MistServer instance, as started by `mistserver.service`. Documentation for MistServer can be found at [http://mistserver.org](http://mistserver.org)

####stream.sh

This script is used to stream the recorded file over RTMP to the MistServer instance. This is done using `avconv`, and by seeking to the end of the currently latest recorded file.
###Status

##Off-Premise Server

##Status Monitoring

##Post-Processing
