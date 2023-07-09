$fn=60;

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