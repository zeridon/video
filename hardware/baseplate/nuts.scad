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
