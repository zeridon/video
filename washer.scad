/**
 * This 2mm thick washer will fit over the 4mm high low-profile screw hole.
 * Together, these will accept 6mm screws.
 */

$fn=100;

difference() {
    cylinder(d=12,h=2);
    translate([0,0,-1]) cylinder(d=3.6,h=4);
}