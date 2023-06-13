$fn=50;

module arm() {
    difference() {
        cube([56,5,2]);
        translate([6,-1,-1])
            cube([44,3,4]);
    }
}

module foot() {
    difference() {
        cube([13,5,6]);
        translate([4,2.5,0])
            cylinder(h=7,r1=1.5);
    }
}

translate([8,0,9])
    arm();

foot();