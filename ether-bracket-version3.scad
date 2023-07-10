$fn=100;

//color("#f00") mirror([1,0,0]) translate([-40,0,4.5]) rotate([180,0,0]) import("foo.stl");

module screwholder() { // 10mm high M3 screw holder with ledge
    translate([3,5,0]) difference() {
        cylinder(d=6, h=10);
        cylinder(d=3, h=11);
    }

    translate([1,0,0]) cube([4,3,9]);
    translate([2,0,9]) cube([2,3,1]);
}

module standembracer(height=9) {   
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

    }
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
        //translate([8.2,13.1,-1]) cylinder(d=9, h=6.5); // low-profile screw hole cut-out first print
        translate([8.2,14,-1]) cylinder(d=8, h=6.5); // low-profile screw hole cut-out
    }
}


frame();

translate([8,93.5,0]) {
    standembracer(height=9);
    union() { // faking part of a screw holder to hold up the board
        translate([0,-7.5,0]) cube([5,2,9]);
        translate([2,-7,9]) cube([2,3,1]);
    }
}

translate([15,8,0]) {
    rotate([0,0,180]) screwholder();
}

translate([31,8,0]) {
    rotate([0,0,180]) screwholder();
}

translate([24,87,0]) {
    screwholder();
}