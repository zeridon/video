# Parts

A full build needs several parts. All of these should be easily reproducible,
while for the ones where we rely on an external manufacturer, we made sure to
have ample spares.

You will need one of each item, except when stated otherwise.

## Case

The case is an off-the-shelf widely available 1U case, made by Gainta.

  * [G17081UBK](https://www.gainta.com/en/g17081ubk.html)

We only use the actual enclosure and one side cover. All other bits can be
discarded.

Each side of the case has 8 4mm high screw holes. These are just too tight to
fit our standard M3 bolts, so we will need to enlarge them. Using a manual
threading tool works, but using a drill press with a 2.8mm drill works best.

## Front

The front is made out of 2.5mm MDF and cut using a laser cutter.

  * [Front plate](frontplate.svg)

## Brackets

We use three different boards in the case. Each of these needs to be removed
from the enclosure it comes in. The bare boards should fit nicely in the
brackets.

The brackets are 3D-printed in PLA using 0.2mm layers.

  * [Capture board](capture-bracket.scad)
  * [Ethernet phy/switch](ether-bracket.scad)
  * [USB-C hub](usb-c-bracket.scad)

## Boards

The boards are the hardest part to source, so we made sure to have ample stock
to last us a while. Should these ever become obsolete, it should not be too hard
to source a substitute.

  * [Cable Matters USB 3.1 to 4-port Ethernet](https://www.cablematters.com/pc-1273-138-usb-31-to-4-port-gigabit-ethernet-adapter.aspx)
  * [UNI USB-C 8 in 1 UNI8IN101](https://uniaccessories.com/products/usb-c_8in1_hub)
  * [MS2131 board](http://www.ultrasemi.com/index.php/td-3-48-72-450) (in development)

The MS2131 board we started off with is the demo board as produced by Ultrasemi.
We are in the process of customising this design with our own additions, details
will be added when we have them.

## Cables

The ethernet phy/switch board comes with a cable attached. For the USB-C
connection to the controlling device, we use the supplied 20cm USB-C 100W PD
cable from UNI.

For internal cabling, you will need some extra cables.

  * HDMI 2.0 50cm with slim heads (2x)
  * USB 3.0 A-A 50cm (1x)

We bought our HDMI cables in bulk, directly from the manufacturer. We don't have
an exact type number.

For the USB 3.0 A-A cable, any cable should do. We used a "Vention CONBD".

## Connectors

Aside from the ethernet switch which we expose directly, we only expose two
HDMI connecors. We use Neutrik connectors, fitting in a standard D-shape hole.

  * [Neutrik NAHDMI-W](https://www.neutrik.com/en/product/nahdmi-w) (2x)

## Bits and bobs

Some smaller pieces are needed to assemble the case and keep everything
together nicely.

  * [Washer](washer.scad) (4x)
  * [Case lock](case-lock.scad) (4x)
  * Bolts
    * M3x6 (14x)
    * M3x12 (8x)
    * M3x25 (4x)
  * Nuts
    * M3 (8x)

For the bolts, we have opted for a mix of black and galvanised bolts, to make
them easy to identify. The shorter (6mm and 10mm) ones have different colours,
and as there is only a single longer one, we opted for black to fit the case
colour better. All bolts have 2mm HEX heads.

The brand and thread size don't matter, but this is what we used:

  * M3x6 Bossard 1348663 (galvanised)
  * M3x10 Bossard 1020536 (black)
  * M3x25 Bossard 1135015 (black)

You will also need a handful of M3 nuts. Again, the specific type doesn't matter
but this is what we used:

  * M3 H2.4 W5.5mm Bossard 1874659 (galvanised)

# Production

## Preparation

### Case

  * Unpack the case
  * Discard everything but the two case halves and one panel
  * Identify which half is the top and which is the bottom
    * The top one is completely flat on the outside
    * The bottom one has holes to bolt the two halves together
  * On the bottom cover, pick a front and back (doesn't matter)
  * With the front towards you, identify the back left 4th and 5th vent fins
  * Cut these fins away using cable cutters
  * Clean up the rest using a hobby knife

### Ethernet phy/switch

  * Unpack the device
  * Remove the rubber grommets from the bottom, revealing the screws
  * Remove the screws
  * Unscrew the board from the case
  * Using sturdy wire cutters, cut open the hole the cable feeds through
  * Discard everything but the board assembly

### USB-C hub

  * Unpack the device
  * Set the 20cm USB-C cable aside
  * Remove the rubber-ish outer protection
  * Remove the front cover (or back, doesn't matter)
    * Place the device belly down on a flat surface
    * Using a hobby knife, make a cut in the cover (cutting at a 20 degree angle
      seems to work best)
    * Pry off the cover
  * Undo the 4 screws
  * Remove the metal plate
  * Slide out the board
  * Discard everything but the USB-C cable and the board

## Assembly

  1.  Take the bottom half of the case
  2.  Enlarge the 8 internal screw holes to accept M3 bolts
  3.  Slide in the MDF front panel
  4.  Place the Ethernet bracket
  5.  Put a washer over the screwhole, fasten using an M3x6 bolt
  6.  Place the ethernet board in the bracket (make sure the side notches fit
      snugly!)
  7.  Take the oddly shaped dual washer, place it over the holes closest to the
      side and tighten with an M3x6 bolt
  8.  Put a washer over the other hole and tighten with an M3x6 bolt
  9. Thread the cable through the strain relief
  10. Place the rectangular clip over the strain relief and tighten with two
      M3x6 bolts
  11. Install the USB-C board in its bracket (ethernet port down)
  12. Place the USB-C bracket, sliding it in at an angle works best
  13. Put a washer over the screwhole, fasten using an M3x6 bolt
  14. Place the bar over the USB-C port, fasten using two M3x6 bolts
  15. Connect the ethernet device's USB cable, coil up overlength
  16. Place the capture bracket
  17. Put a washer over each screwhole, fasten using two M3x6 bolts
  18. Run a USB 3.0 A-A cable from the USB-C hub towards the other side of the
      case, coil it up once between the capture bracket
  19. Place the board over the screwholes, HDMI to the left, USB to the right
      and fasten using 4 M3x6 bolts
  20. Connect the USB cable
  21. Connect two HDMI cables to the capture board
  22. Using 4 M3x10 bolts and 4 M3 nuts each, install the Neutrik connectors in
      the front panel
  23. Connect the HDMI cables to the Neutrik connectors (pay attention that RX
      goes to IN and TX goes to OUT)
