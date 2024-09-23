$fn=120;

module case() {
    supportd=10.5;
    screwd=7.5;
    color("red", 0.1) {
        difference() {
            square(size=[423.8,195.0]);

            // case lock things
            translate([0,6.5,0]) square(size=[6.5,14.5]);
            translate([0,173.5,0]) square(size=[6.5,14.5]);
            translate([417.3,7,0]) square(size=[6.5,14.5]);
            translate([417.3,173.5,0]) square(size=[6.5,14.5]);

            // screw stands
            // outer
            translate([20.4,33.85,0]) circle(d=screwd);
            translate([20.4,161.15,0]) circle(d=screwd);
            translate([403.05,33.85,0]) circle(d=screwd);
            translate([403.05,161.15,0]) circle(d=screwd);

            // inner
            translate([148.15,33.85,0]) circle(d=screwd);
            translate([148.15,161.15,0]) circle(d=screwd);
            translate([275.65,33.85,0]) circle(d=screwd);
            translate([275.65,161.15,0]) circle(d=screwd);

            // support stands
            translate([100.05,33.85,0]) circle(d=supportd);
            translate([100.05,161.15,0]) circle(d=supportd);
            translate([323.5,33.85,0]) circle(d=supportd);
            translate([323.5,161.15,0]) circle(d=supportd);
        }
    }
}

module rrect(w,l,r) {
    translate([r,r,0]) {
        minkowski() {
            square(size = [w-(2*r), l-(2*r)]);
            circle(r=r);
        }
    }
}

// footprints
module switch() {
    difference() {
        rrect(84,83,2);
        translate([78,48,0]) rrect(10,40,2);

        // top holes
        translate([26.5,78,0]) circle(d=3);
        translate([73,78,0]) circle(d=3);

        // center holes
        translate([6,43,0]) circle(d=3);
        translate([79,42,0]) circle(d=3);
    }
}

module power() {
    difference() {
        rrect(87,90,2);
        translate([66.5,66,0]) rrect(25,30,2);
        translate([-5,27,0]) rrect(24,70,6);

        translate([83,6.5,0]) circle(d=3);
        translate([17.2,24.45,0]) circle(d=3); // idk, this might be wrong
        translate([45,69,0]) circle(d=3);
    }
}

module onlyfans() {
    square([15,101]);
}

module audio() {
    difference() {
        rrect(152,61.5,2);

        // top holes
        translate([4.5,57,0]) circle(d=3);
        translate([147.5,57,0]) circle(d=3);

        // center  holes
        translate([4.5,21.25,0]) circle(d=3);
        translate([147.5,21.25,0]) circle(d=3);

        // support hole
        translate([83.15,34.05,0]) circle(d=8.8);
    }
}

module hdmi() {
    // fixme: re-measure
    difference() {
        rrect(58,58,2);
        translate([4,54,0]) circle(d=3);
        translate([54,54,0]) circle(d=3);
        
        translate([4,4,0]) circle(d=3);
        translate([54,4,0]) circle(d=3);
    }
}

module radxa() {
    // fixme: re-measure
    difference() {
        rrect(155,80,2);

        // top holes
        translate([151,76,0]) circle(d=2);
        translate([4,76,0]) circle(d=2);

        // bottom holes
        translate([4,18,0]) circle(d=2);
        translate([151,18,0]) circle(d=2);
    }
}

translate([10.5,112,0]) translate([84,83,0]) rotate(180) switch();
translate([7.5,0,0]) power();
translate([0,33,0]) onlyfans();
translate([240,0,0]) audio();
translate([329.5,136.9,0]) hdmi();
translate([160,110,0]) radxa();


case();
