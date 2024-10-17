use <nuts.scad>

module radxa_x2l_holes() {
    radxa_x2l_mounting_holes();
    radxa_x2l_protrusion_cutouts();
}

module radxa_x2l_mounting_holes() {
    // mounting holes
    translate([4, 3.8, 0]) nuthole_m2();
    translate([4, 3.8+58.4, 0]) nuthole_m2();
    translate([4+148.2-58.2, 3.8, 0]) nuthole_m2();
    translate([4+148.2-58.2, 3.8+49.2, 0]) nuthole_m2();
    translate([4+148.2, 3.8, 0]) nuthole_m2();
    translate([4+148.2, 3.8+58.4, 0]) nuthole_m2();
}

module radxa_x2l_protrusion_cutouts() {
    // nvme
    translate([0, 14.5, 0])
    rrect(89, 25, 2);
}

module radxa_x2l() {
    brd_thickness = 1.6;
    // precise measurements available at https://dl.radxa.com/x/x2l/radxa_x2l_product_brief.pdf
    linear_extrude(brd_thickness)
    difference() {
        rrect(155.6,80.6,2);
        radxa_x2l_mounting_holes();
    }
    
    color("gray")
    translate([0, 0, -1.5])
    linear_extrude(1.5)
    radxa_x2l_protrusion_cutouts();
}

radxa_x2l();
