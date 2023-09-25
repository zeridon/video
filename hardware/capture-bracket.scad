/**
 * The case-lock replaces the stock slide-in case locks of the Gainta G17081U
 * case. These come with rackmount ears, which we don't need and take up
 * unnecessary space.
 *
 * You will need 4 of these per case.
 */

$fn=100;

module screwring() { // 10mm high M3 screw holder with ledge
    difference() {
        cylinder(d=12, h=4.5);
        translate([0,0,-1]) cylinder(d=8, h=6); // low-profile screw hole cut-out
    }
}

module screwstand(id = 3, od = 6, h=10) {
    difference() {
        cylinder(d=od, h=h);
        translate([0,0,1]) cylinder(d=id, h=h);
    }
}

module standarm() {
    arm_length = 64;

    screw_outer_d = 5;
    screw_inner_d = 3;
    screw_height = 12;

    difference() {
        cube([arm_length,5,4.5]);
        translate([screw_outer_d/2,screw_outer_d/2,1])    
            cylinder(d=screw_outer_d, h=screw_height);
        translate([arm_length-(screw_outer_d/2),screw_outer_d/2,1])
            cylinder(d=screw_outer_d, h=screw_height);
    }
    

    translate([screw_outer_d/2,screw_outer_d/2,0])
        screwstand(id = screw_inner_d, od = screw_outer_d, h=screw_height);

    translate([arm_length-(screw_outer_d/2),screw_outer_d/2,0])
        screwstand(id = screw_inner_d, od = screw_outer_d, h=screw_height);
}

translate([32,2,0]) screwring();

translate([29,6,0]) cube([6,118,4.5]); // long arm

translate([0,11.5,0]) standarm();
translate([0,114.5,0]) standarm();

translate([32,129,0]) screwring();