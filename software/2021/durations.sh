#! /bin/bash

rm -rf durations.txt
for f in $(ls -1 *.mp4);do
  echo "Processing $f"
  duration=$(ffprobe $f |& grep Duration|sed -e 's/  Duration\: \([0-9].\:[0-9].\:[0-9].\).*/\1/g')
  penta_id=$(echo $(basename -s .mp4 $f))
  echo "$penta_id,$duration" >> durations.txt
done
exit 0
