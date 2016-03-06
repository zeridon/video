#FOSDEM Video Repository

This repository is meant to keep track of the development for Video on FOSDEM.

##Hardware Architecture

###Camera Box

    +------+    +-----+
    | HDMI |    | SDI |
    +--+---+    +---+-+
       |            |
       |  +-----+   |
       +--+ BMD +---+
          +--+--+
             |
       +-----+-----+
       | Banana Pi |
       +-+-------+-+
         |       |
    +----++    +-+-------+
    | SSD |    | Network |
    +-----+    +---------+

###Presenter Box

    +------+     +-----+
    | JACK |     | VGA |
    +--+---+     +---+-+
       |             |
       | +--------+  |    +--------+
       +-+ Scaler +--+----+ Beamer |
         +---+----+       +--------+
             |
          +--+--+
          | BMD |
          +--+--+
             |
       +-----+-----+
       | Banana Pi |
       +-+-------+-+
         |       |
    +----++    +-+-------+
    | SSD |    | Network |
    +-----+    +---------+
