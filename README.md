#FOSDEM Video Repository

This repository is meant to keep track of the development for Video on FOSDEM.

In its current form it describes the hardware architecture that has been used inside the video boxes.

##Hardware Architecture

For 2016, 2 types of boxes are in use: 1 type connected to a camera, and 1 connected to a presentation laptop. 

The main components of the boxes are the following:

* [Blackmagicdesign H.264 Pro Recorder](https://www.blackmagicdesign.com/nl/products/h264prorecorder "H.264 Pro Recorder") (__BMD__)

  This is a professional-grade H264 encoder that can encode a signal from HDMI, SDI or Component video to an encoded MPEG2 Transport Stream over USB.

  Altough intended for Video-on-demand encoding only, there is exists a [libusb-based driver](https://github.com/fabled/bmd-tools "BMD-Tools") to encode the stream in real-time with only a slight delay.

* [Banana Pi](http://www.lemaker.org/product-bananapi-specification.html "Banana Pi") (__Banana Pi__)

  The banana pi is a small development based on the allwinner A20 chipset.

* [Banana Pi 3.5" LCD Module](http://www.lemaker.org/product-bananapi-specification.html "Banana Pi 3.5" LCD Module") (__LCD__)

  An LCD Module that works flawlessly with the Banana Pi. Used for status display on the box itself.

* [Sandisk SDSSDP-064G-G25](http://kb.sandisk.com/app/answers/detail/a_id/17225 "Sandisk SSD") (__SSD__)

  A regular SSD with SATA connection connected to the Banana Pi. Used for local storage of recordings.

* Gigabit Network Switch (__Network__)

  A regular Gigabit-capable network switch, with 3 RJ-45 connectors exposed to the outside of the box.

In addition to the basics, the presenter boxes have the following extra components:
  
* [Lenkeng LKV391 MINI Switch](http://www.lenkeng.net/home/Index/detail/id/105 "Lenkeng Scaler") (__Scaler__)

  A device that can take VGA, HDMI or Composite video in, combines it with audio where needed and scales the output into a desired resolution on HDMI.

* VGA Splitter (__Splitter__)

  A simple VGA splitter that allows for simulatneous input of the VGA signal to both the scaler and the output port.

###Schematics

The Camera box is wired as follows:

    +------+    +-----+
    | HDMI |    | SDI |
    +--+---+    +---+-+
       |            |
       |  +-----+   |
       +--+ BMD +---+
          +--+--+
             |
       +-----+-----+    +-----+
       | Banana Pi +----+ LCD |
       +-+-------+-+    +-----+
         |       |
    +----++    +-+-------+
    | SSD |    | Network |
    +-----+    +---------+

The Presenter box is wired as follows:

    +---------+   +----------+   +--------+
    | JACK In |-+-| JACK Out |   | VGA In |
    +--+------+ | +----------+   +--+-----+
                |                   |
                | +--------+   +----+-----+  +---------+
                +-+ Scaler +---+ Splitter +--+ VGA Out |
                  +---+----+   +----------+  +---------+
                      |
                   +--+--+
                   | BMD |
                   +--+--+
                      |
                +-----+-----+   +-----+
                | Banana Pi +---+ LCD |
                +-+-------+-+   +-----+
                  |       |
             +----++    +-+-------+
             | SSD |    | Network |
             +-----+    +---------+
