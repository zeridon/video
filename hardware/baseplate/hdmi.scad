use <nuts.scad>

module hdmi_holes() {
    translate([4,54,0]) nuthole_m3();
    translate([54,54,0]) nuthole_m3();

    translate([4,4,0]) nuthole_m3();
    translate([54,4,0]) nuthole_m3();
}

module hdmi() {
    brd_thickness = 1.6;
    // fixme: re-measure
    linear_extrude(brd_thickness)
    difference() {
        rrect(58,58,2);
        hdmi_holes();
    }
}

