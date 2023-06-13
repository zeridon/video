$fn=50;

module bracket() {
    difference() {
        union() {
            cube(size=[56,6,12]);
            cube(size=[10,10,12]);
            translate([46,0,0])
                cube(size=[10,10,12]);
        }

        translate([3,2,7])
            cube(size=[50,10,3]);
    }
}

module foot() {
    difference() {
        cube([8,10,6]);
        translate([4,5,0])
            cylinder(h=7,r1=1.5);
    }
}

translate([8,0])
    bracket();
translate([0,0])
    foot();
translate([64,0,0])
    foot();