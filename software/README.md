#Software Architecture

The software hierarchy is dictated by 2 main goals: _recording_ and _streaming_ of the video streams encoded inside the box.

##Partitioning and filesystem
The custom arch distro expects an SD card with 3 partitions, labelled:
- FBBoot (partition 1, vfat)
- FBSettings (partition 2, ext4)
- FBRoot (partition 3, ext4)

In FBSettings, create a file containing the hostname of the machine called "hostname". Also create a file containing the wanted MAC address, called "mac".

The prepare_sd.sh script in this directory will do all the hard work for you. Call it as:

> ./prepare_sd.sh SD_CARD_DEVICE HOSTNAME MAC_ADDRESS

If anything goes wrong, read the script and see what it is supposed to do, fix it by hand.
Use common sense, it helps!

##First use
First of all, make sure your hosts are listed in ansible_inventory in this directory!

Then, to enable ansible to work, python2 must be installed. To do this, run:
> ansible-playbook prepare_boxes.yml

##Updating boxes
Ansible can update the root and install any needed packages. To do so, first make sure you did the "first use" instructions as mentioned above, then run:
> ansible-playbook remote_update_boxes.yml

##Usage instructions
Coming when software is more complete. Until then...
> It's not safe to go alone - take this!

