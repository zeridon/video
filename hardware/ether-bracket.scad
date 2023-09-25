/**
 * This is a bracket for the Cable Matters USB 3.1 to 4-port Gigabit Ethernet Adapter
 * It fits around the low-profile screw hole and the stand in the Gainta G17081U case
 */

$fn=100;

height=10; // height from the frame up

include <modules/standembracer.scad>

// --------- modules --------- //

module screwholder() { // 10mm high M3 screw holder with ledge
    translate([3,5,0]) difference() {
        cylinder(d=6, h=10);
        cylinder(d=3, h=11);
    }

    translate([1,0,0]) cube([4,3,9]);
    translate([2.1,0,9]) cube([1.8,3,1]);
}

module frame() {
    difference() {

        union() {
            difference() {
                cube([40, 95, 4.5]);
                translate([4,4,-1]) cube([32, 87, 7]); // inner cut-out
            }

            union() { // peninsula (cut-out for low-profile screw hole comes later
                difference() { 
                    cube([16,22,4.5]);
                    translate([12,18,-1]) cube([5,5,7]);

                }

                translate([12,18,0]) cylinder(d=8, h=4.5); // round the corner
            }
        }

        translate([3,90,-1]) cube([11,6,6.5]); // standembracer cut-out
        translate([8.2,14,-1]) cylinder(d=8, h=6.5); // low-profile screw hole cut-out
    }
}

module strainrelief() {
    cutout_d=7.5;

    difference() {
        union() {
            cube([17,29,4.5]);
            translate([-1.5,22,0]) cube([20,7,12.5]);
        }

        translate([0,22,0]) { // screwholes and cut-out
            translate([1,3.5,height-9]) rotate([0,0,90]) cylinder(d=3, h=15);
            translate([16,3.5,height-9]) rotate([0,0,90]) cylinder(d=3, h=15);

            translate([8.5,-1,height-7+(cutout_d/2)+4]) rotate([0,90,90]) cylinder(d=cutout_d, h=9);
        }
    }
}

module strainrelief_clip() {
    difference() {
        cube([7,20,2]);
        translate([3.5,2.8,-1]) rotate([0,0,90]) cylinder(d=3.6, h=10);
        translate([3.5,17.2,-1]) rotate([0,0,90]) cylinder(d=3.6, h=10);
    }
}

module dualwasher() { // two-hole oddly shaped washer, fits neatly in the case
    difference() {
        union() {
            translate([6,0,0]) cylinder(d=12,h=1.5);
            cube([9,20,1.5]);
        }

        translate([6,0,-1]) cylinder(d=3.6,h=3);
        translate([6,16,-1]) cylinder(d=3.6,h=3);
        translate([-1,6,-1]) cube([3,6,5]);
    }
}

// --------- assembly --------- //

frame(); // main frame

translate([0,40,0]) rotate([0,0,90]) strainrelief(); // tail with USB cable support

translate([8,93.5,0]) { // cylinder with cross shape cut out, goes around the stand
    standembracer(height-1); // leave room to hold the board, so height-1
    union() { // faking part of a screw holder to hold up the board
        translate([4,-6.5,0]) cylinder(d=4, h=height-1);
        translate([3.1,-7,height-1]) cube([1.8,3,1]);
    }
}

translate([16,8,0]) { // back right
    rotate([0,0,180]) screwholder();
}

translate([32,8,0]) { // front right
    rotate([0,0,180]) screwholder();
}

translate([25,87,0]) { // front left
    screwholder();
}

translate([10,30,0]) strainrelief_clip(); // square clip, fits on the strain relief

translate([10,60,0])  dualwasher(); // oddly shaped washer