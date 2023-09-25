/**
 * The case-lock replaces the stock slide-in case locks of the Gainta G17081U
 * case. These come with rackmount ears, which we don't need and take up
 * unnecessary space.
 *
 * You will need 4 of these per case.
 */

$fn=100;

module rcube(size, radius) {
    hull() {
        translate([radius, radius]) cylinder(r = radius, h = size[2]);
        translate([size[0] - radius, radius]) cylinder(r = radius, h = size[2]);
        translate([size[0] - radius, size[1] - radius]) cylinder(r = radius, h = size[2]);
        translate([radius, size[1] - radius]) cylinder(r = radius, h = size[2]);
    }
}

rcube(size=[31,9.5,4], radius=3.5);

translate([0,3.25,4])
    cube(size=[31,2.5,2.7]);