// washer to fit on top of the low-profile screw things

$fn=100;

difference() {
    cylinder(d=10,h=1);
    translate([0,0,-1]) cylinder(d=3.4,h=3);
}