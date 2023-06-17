$fn=50;

module bracket() {
    difference() {
        union() {
            cube(size=[56,5,12]);
            cube(size=[10,9,12]);
            translate([46,0,0])
                cube(size=[10,9,12]);
        }

        translate([3,2,8])
            cube(size=[50,10,2]);

        translate([18.5,2,9])
            cube(size=[20,10,4]);
    }
}

module foot() {
    difference() {
        cube([8,9,6]);
        translate([4,4.5,0])
            cylinder(h=7,r1=1.5);
    }
}

translate([8,0])
    bracket();
translate([0,0])
    foot();
translate([64,0,0])
    foot();