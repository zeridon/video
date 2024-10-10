use <nuts.scad>

display_size_x = 70;
display_size_y = 22.5;

holder_hole_spacing = 4.5;

module display_footprint() {
    union() {
        rrect(display_size_x, display_size_y, 2);
        square([display_size_x, 2]);
    }
}

module display_holes() {
    half_hole_spacing_x = (128.4175 - 70.4175) / 2;
    centre_x = display_size_x / 2;
    translate([-holder_hole_spacing, holder_hole_spacing]) nuthole_m3();
    translate([-holder_hole_spacing, 16]) nuthole_m3();
    translate([display_size_x + holder_hole_spacing, holder_hole_spacing]) nuthole_m3();
    translate([display_size_x + holder_hole_spacing, 16]) nuthole_m3();
    translate([centre_x - half_hole_spacing_x, holder_hole_spacing + display_size_y]) nuthole_m3();
    translate([centre_x + half_hole_spacing_x, holder_hole_spacing + display_size_y]) nuthole_m3();
}

module display_cutout() {
    display_holes();
    display_footprint();
}

module display() {
    linear_extrude(20)
    display_cutout();
}
