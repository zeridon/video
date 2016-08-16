#!/bin/bash -x

if [ -z "$1" ] ; then
  echo "Usage: $0 SD_CARD_DEVICE"
  exit
fi

DEV=$1
HN="fosbox"

echo "Mounting partitions..."
mkdir -p ./boxmounts/FBRoot
mount ${DEV}3 ./boxmounts/FBRoot

echo "Copying root files..."
chown -R root:root ./FBRoot
chmod -R g-rwx ./FBRoot/root
chmod 700 ./FBRoot/root/.ssh
chmod 600 ./FBRoot/root/.ssh/authorized_keys
cp -var ./FBRoot/* ./boxmounts/FBRoot/

echo "Unmounting partitions"
umount ./boxmounts/*

sync
echo "Done. You can unplug the SD card now."

