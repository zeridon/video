#!/bin/bash

#uncomment this one for HDMI
bmd-streamer -f /usr/lib/firmware -B -S hdmi | mplayer -fs -quiet -hardframedrop -screenw 320 -screenh 240 -ao none -vo directfb -

#uncomment this one for SDI
#./bmd-streamer -B -S sdi | mplayer -fs -quiet -hardframedrop -screenw 320 -screenh 240 -ao none -vo directfb -

