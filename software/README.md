#Software Architecture

The software hierarchy is dictated by 2 main goals: _recording_ and _streaming_ of the video streams encoded inside the box.

##Partitioning and filesystem
The custom arch distro expects an SD card with 3 partitions, labelled:
- FBBoot (partition 1, vfat)
- FBSettings (partition 2, ext3)
- FBRoot (partition 3, ext3)

##Some dependencies
You will need bsdtar and ansible.

##Preparing the initial image
In FBSettings, create a file containing the hostname of the machine called "hostname". Also create a file containing the wanted MAC address, called "mac".

The prepare_sd.sh script in this directory will do all the hard work for you. Call it as root, as follows:

> ./prepare_sd.sh SD_CARD_DEVICE HOSTNAME MAC_ADDRESS

If anything goes wrong, read the script and see what it is supposed to do, fix it by hand.
Use common sense, it helps!

##Adding your ssh pubkey to the sd card
In order to use ansible, you will need ssh root on the box. Let's add our key to the device.

> cat ~user/.ssh/id_rsa.pub >> /path/to/FBRoot/root/.ssh/authorized_keys

##Booting the box for the first time
The box should now boot fine. It will attempt to get a dhcp lease. You will need its ip address, so either configure your dhcp server to give out a predetermined ip address to the mac address for the box, or check your dhcp server client table for the ip address it has given out.

##Further preparations for ansible deployment
Now add the ip address for your video box(es) to the relevant section of the file ansible_inventory . You should find that file in the same directory as this README.md.

Then, to enable ansible to work, python2 must be installed onto the box(es). To do this, run:
> ansible-playbook prepare_boxes.yml

##Updating boxes
Ansible can update the root and install any needed packages. To do so, first make sure you did the "first use" instructions as mentioned above, then run:
> ansible-playbook remote_update_boxes.yml

##Troubleshooting
Check the streaming status on the box:
> systemctl status stream

Restart the streaming 
> systemtl restart mistserver && systemctl restart stream

##Usage instructions
Coming when software is more complete. Until then...
> It's not safe to go alone - take this!

