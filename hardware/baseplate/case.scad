use <nuts.scad>

module case_fit_shape() {
    supportd=10.5;
    screwd=8.1;

    margin_x = 1;
    case_lock_grow_y = 0.3;

    color("red", 0.1) {
        difference() {
            translate([margin_x, 0, 0]) square(size=[423.8 - 2*margin_x,195.0]);

            // case lock things
            translate([0 + margin_x,6.5 - case_lock_grow_y,0]) square(size=[6.5,14.5 + case_lock_grow_y*2]);
            translate([0 + margin_x,173.5 - case_lock_grow_y,0]) square(size=[6.5,14.5 + case_lock_grow_y*2]);
            translate([417.3 - margin_x,7 - case_lock_grow_y,0]) square(size=[6.5,14.5 + case_lock_grow_y*2]);
            translate([417.3 - margin_x,173.5 - case_lock_grow_y,0]) square(size=[6.5,14.5 + case_lock_grow_y*2]);

            // screw stands
            // outer
            hull() {
                // this hole is too close to the fan
                // cutout, so merge the cut
                translate([12,40,0]) circle(d=screwd);
                translate([21.15 - 0.5,33.85 - 0.2,0]) circle(d=screwd);
            }
            translate([21.15 - 0.5,160.85 + 0.2,0]) circle(d=screwd);
            translate([402.2 + 0.5,33.85 - 0.2,0]) circle(d=screwd);
            translate([402.2 + 0.5,160.85 + 0.2,0]) circle(d=screwd);

            // inner
            translate([148.25 - 0.5,33.85 - 0.2,0]) circle(d=screwd);
            translate([148.25 - 0.5,160.85 + 0.2,0]) circle(d=screwd);
            translate([275.25 + 0.5,33.85 - 0.2,0]) circle(d=screwd);
            translate([275.25 + 0.5,160.85 + 0.2,0]) circle(d=screwd);

            // support stands
            translate([100.05,33.85,0]) circle(d=supportd);
            translate([100.05,160.85,0]) circle(d=supportd);
            translate([323.3,33.85,0]) circle(d=supportd);
            translate([323.3,160.85,0]) circle(d=supportd);
        }
    }
}

module case() {
    color("gray")
    translate([285, 158.5, -4 + 0.15]) import("thirdparty_3dmodels/box.stl");
}

case();
linear_extrude(2) case_fit_shape();
