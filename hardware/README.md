# Parts

A full build needs several parts. All of these should be easily reproducible,
while for the ones where we rely on an external manufacturer, we made sure to
have ample spares.

You will need one of each item, except when stated otherwise.

## Case

The case is an off-the-shelf widely available 1U case, made by Gainta.

  * [G17081UBK](https://www.gainta.com/en/g17081ubk.html)

We only use the actual enclosure. All other bits can be discarded.

Each side of the case has 8 4mm high screw holes. These are just too tight to
fit our standard M3 bolts, so we will need to enlarge them. Using a manual
threading tool works, but using a drill press with a 2.8mm drill works best.

## Front

The front is made out of 2.5mm MDF and cut using a laser cutter, see `frontplate/`

## Back

The back is made out of 2.5mm MDF and cut using a laser cutter, see `backplate/`


## Boards


### Externally sourced

The boards are the hardest part to source, so we made sure to have ample stock
to last us a while.

  * [MS2131 board](https://www.shophagibis.com/products/video-capture-card-hagibis?variant=45797324783897)
  * [Raxda X4](https://radxa.com/products/x/x4/)

The MS2131 board we started off with is the demo board as produced by Ultrasemi.
Currently we use the Hagibis version, as this proved to be the most stable from
all MS2131 boards we tested.

The Raxda X4 is a x86-based SBC that handles all computing needs.

### Boards we make

* Ethernet switch
* Power board
* Audio mixer

## Cables

* 6 x MTA100 cables (white ones) to connect "hats"
* 2 x USB 3.0 A-A cables, any cable should do. We used a "Vention CONBD".
* 1 x USB 2.0 A-microUSB to connect the Teensy on the audio mixed
* 1 x HDMI-to-microHDMI cable for the loop-out from radxa
* 1 x ethernet cable from Radxa to the switch
* 1 x power cable from the power board to the Radxa
* 1 x power cable from the external jack to the power board

## Connectors

We expose:

* HDMI IN, HDMI loop out from the MS2131;
* HDMI out from the Radxa via a Neutrik connector
* 4 x ethernet ports
* 3 x audio inputs, XLR
* 2 x audio outputs, XLR
* 1 x headphone jack

## Bits and bobs

TBD 

# Production

See `assembly`.
