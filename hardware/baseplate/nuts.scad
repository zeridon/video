module rrect(w,l,r) {
    translate([r,r,0]) {
        minkowski() {
            square(size = [w-(2*r), l-(2*r)]);
            circle(r=r);
        }
    }
}

module nuthole_m2() {
    // circle(d=2.1);
    circle(d=30);
}

module nuthole_m25() {
    // circle(d=2.6);
    circle(d=30);
}

module nuthole_m3() {
    // circle(d=3.15);
    circle(d=30);
}

module nuthole_m4() {
    // circle(d=4.2);
    circle(d=30);
}

module hole_for_standoff_m3_2mm() {
    circle(d=5.41);
}

module hole_for_standoff_m4_6mm() {
    circle(d=7.14);
}

module hole_for_standoff_m3_4mm() {
    circle(d=5.41);
}

module hole_for_standoff_m3_6mm() {
    circle(d=5.41);
}

module hole_for_standoff_m25_2mm() {
    circle(d=3);
}

module hole_for_threaded_pin_m3_8mm() {
    circle(d=3);
}
