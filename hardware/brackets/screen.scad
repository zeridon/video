include <modules/rcube.scad>

difference() {
    rcube([65,34,1], 1);

    translate([3.9, 28.6, -1]) cylinder(d=2.5, h=3); // top left
    translate([3.9,  5, -1]) cylinder(d=2.5, h=3); // bottom left
    
    translate([61.5,  28.6, -1]) cylinder(d=2.5, h=3); // top right
    translate([61.5,  5, -1]) cylinder(d=2.5, h=3); // bottom right

    translate([5.65,7,-1]) cube([53.7,25.5,3]);
}
