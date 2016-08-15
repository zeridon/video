#Software Architecture

The software hierarchy is dictated by 2 main goals: _recording_ and _streaming_ of the video streams encoded inside the box.

##Partitioning and filesystem
The custom arch distro expects an SD card with 3 partitions, labelled:
- FBBoot (partition 1, vfat)
- FBSettings (partition 2, ext4)
- FBRoot (partition 3, ext4)

The prepare_sd.sh script in this directory will do all the hard work for you.
If anything goes wrong, read it and see what it is supposed to do, fix it by hand.
Use common sense, it helps!

##Usage instructions
Coming when software is more complete. Until then...
> It's not safe to go alone - take this!

