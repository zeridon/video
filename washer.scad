// washer to fit on top of the low-profile screw things

$fn=100;

difference() {
    cylinder(d=12,h=2);
    translate([0,0,-1]) cylinder(d=3.6,h=4);
}