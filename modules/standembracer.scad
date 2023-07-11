/**
 * Module to print a brace which fits nicely around the Gainta G17081U's stands
 */

module standembracer(height=10) {   
    difference() {
        cylinder(d=14, h=height);
        translate([0,0,-1]) cylinder(d=11, h=height+2);
    }

    difference() { // 4-edge cylinder clamp
        cylinder(d=11, h=height);
        translate([0,0,-1]) cylinder(d=6.1, h=height+2);

        translate([-5,-5, 0]) { // rest to 0,0 compared to the cylinder's edge
            translate([3.5,0,-1]) cube([3,3,height+2]); // cutout north
            translate([3.5,7,-1]) cube([3,3,height+2]); // cutout south
            translate([7,3.5,-1]) cube([3,3,height+2]); // cutout east
            translate([0,3.5,-1]) cube([3,3,height+2]); // cutout west
        }

        translate([0,0,-3]) sphere(6.1);
    }
}