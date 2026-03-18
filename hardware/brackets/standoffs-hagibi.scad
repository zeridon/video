/**
 * This 2mm thick washer will fit over the 4mm high low-profile screw hole.
 * Together, these will accept 6mm screws.
 */

$fn=100;
hdmi_hole_half_dist = 52 / 2;
hdmi_main_square = 58.7;
hdmi_centre = hdmi_main_square / 2;

module cyl_standoff(ind, outd, h) {
    difference() {
        cylinder(d=outd,h=h);
        translate([0,0,-1]) cylinder(d=ind,h=h+2);
    }
}

module hagibi_standoffs() {
    margin = hdmi_centre - hdmi_hole_half_dist;
    far = hdmi_centre + hdmi_hole_half_dist;

    translate([margin, far, 0])     cyl_standoff(5, 7.5, 15);
    translate([far, far, 0])        cyl_standoff(5, 7.5, 15);

    translate([margin, margin, 0])  cyl_standoff(4, 6.6, 15);
    translate([far, margin, 0])     cyl_standoff(4, 6.6, 15);
}

hagibi_standoffs();
