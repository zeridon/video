#! /bin/bash
# Creates 10 second still image interroll.
# Example usage: create_interrol.sh still_image.png

ffmpeg -loop 1 -framerate 25 -i $1 -f lavfi -i anullsrc  \
  -c:v libx264 -tune stillimage -crf 18 -c:a aac \
  -ab 128k -strict -2 -shortest -pix_fmt yuv420p -t 10 interroll.mp4
