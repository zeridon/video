use <nuts.scad>

module radxa_x4_holes() {
    translate([3.53,3.5,0]) nuthole_m3();
    translate([3.53,56-3.5,0]) nuthole_m3();
    translate([3.53+58,3.5,0]) nuthole_m3();
    translate([3.53+58,56-3.5,0]) nuthole_m3();

    // hole for power inductors to fit into (they are tall)
    translate([8, 6, 0]) rrect(10, 45, 2);
}


module radxa_x4() {
    brd_thickness = 1.6;
    // precise measurements available at
    // https://dl.radxa.com/x/x4/radxa_x4_product_brief.pdf
    color("#ebac54")
    linear_extrude(brd_thickness)
    difference() {
        union() {
            rrect(85, 56, 3);
            translate([4, 56 - 4, 0]) rrect(56, 6, 2);
        }
        radxa_x4_holes();
    };
}
