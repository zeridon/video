f = 10;
dist = 20;
height = 10;
screwhole=3.25;
tunnel_w = 12;
tunnel_h = 7.5;

use <../baseplate/nuts.scad>

module cable_holder_holes() {
    translate([-dist/2, 0, 0]) nuthole_m3();
    translate([dist/2, 0, 0]) nuthole_m3();
}

module cable_holder_column() {
    difference() {
        linear_extrude(height) union() {
            circle(d=f);
            translate([0, -f/2, 0]) square([f/2, f]);
        }

        translate([0, 0, -0.1]) linear_extrude(1.7) circle(d=6.5);
        translate([0, 0, -0.1]) linear_extrude(height + 0.2) circle(d=screwhole);
    }
}

module cable_holder() {
    difference() {
        union() {
            translate([-dist/2, 0, 0]) cable_holder_column();
            translate([dist/2, 0, 0]) rotate([0, 0, 180]) cable_holder_column();
            linear_extrude(height) square([dist - f + 0.01, f], center = true);
        }

        scale([1, 1, tunnel_h / (tunnel_w * 0.5)])
        translate([0, f, 0]) rotate([90, 0, 0]) linear_extrude(2 * f) circle(d=tunnel_w);
    }
}

module cable_tie() {
    d=8;
    w=10;
    l=15;
    hole_d = 3.2;

    linear_extrude(1)
    difference() {
        hull() {
            circle(d=w);
            translate([l-w, -w/2, 0]) square(w);
        }
        circle(d=hole_d);
    }

    translate([l, -w/2, d/2])
    rotate([0, 90, 90]) linear_extrude(w) circle(d=d);
}

// cable_holder();
cable_tie();
