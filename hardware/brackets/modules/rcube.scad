$fn = 100;

// example: rcube([10,15,1], 1);

module rcube(xyz, rr) {

    xx = xyz[0];
    yy = xyz[1];
    zz = xyz[2];

    difference(){
        cube([xx, yy, zz]);

        difference(){
            translate([-0.5, -0.5, -0.2])
            cube([rr+0.5, rr+0.5, zz+0.5]);

            translate([rr, rr, zz/2])
            cylinder(zz, rr, rr, true);
        }

        translate([xx, 0, 0]) rotate(90) difference() {
            translate([-0.5, -0.5, -0.2])
                cube([rr+0.5, rr+0.5, zz+0.5]);

            translate([rr, rr, zz/2])
                cylinder(zz, rr, rr, true);
        }

        translate([xx, yy, 0]) rotate(180) difference() {
            translate([-0.5, -0.5, -0.2])
                cube([rr+0.5, rr+0.5, zz+0.5]);

            translate([rr, rr, zz/2])
                cylinder(zz, rr, rr, true);
        }

        translate([0, yy, 0]) rotate(270) difference() {
            translate([-0.5, -0.5, -0.2])
                cube([rr+0.5, rr+0.5, zz+0.5]);

            translate([rr, rr, zz/2])
                cylinder(zz, rr, rr, true);
        }
    }
}