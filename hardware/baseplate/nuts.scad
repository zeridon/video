module rrect(w,l,r) {
    translate([r,r,0]) {
        minkowski() {
            square(size = [w-(2*r), l-(2*r)]);
            circle(r=r);
        }
    }
}

module nuthole_m2() {
    circle(d=2.1);
}

module nuthole_m25() {
    circle(d=2.6);
}

module nuthole_m3() {
    circle(d=3.15);
}

module nuthole_m4() {
    circle(d=4.2);
}

module hole_for_standoff_m3_2mm() {
    nuthole_m3();
}

module hole_for_standoff_m4_6mm() {
    nuthole_m4();
}

module hole_for_standoff_m3_4mm() {
    nuthole_m3();
}

module hole_for_standoff_m3_6mm() {
    nuthole_m3();
}

module hole_for_standoff_m25_2mm() {
    nuthole_m25();
}

module hole_for_treaded_pin_m3_8mm() {
    circle(d=3);
}
