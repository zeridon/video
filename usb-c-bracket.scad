include <modules/standembracer.scad>

$fn = 100;

module wall2() {
    translate([0,4.2,0]) cube([25,3,12]);

    translate([0,0,0]) cube([3.5,4.2,10]);
    translate([7,0,0]) cube([3.5,4.2,10]);
    translate([14,0,0]) cube([3.5,4.2,10]);
    translate([21,0,0]) cube([3.5,4.2,10]);
}

module front() {
    // this is the front of the bracket, without the cooling fin fillers
    difference() {
        cube([70,13,10]);
        translate([23,3,-1]) cube([39,11,12]); // main
        translate([14.5,8,7]) cube([10,10,4]); // right holder cut out
        translate([60.5,8,7]) cube([3,10,4]); // left holder cut out
        translate([32.5,-1,3]) cube([12.5,6,8]); // USB-C cut out

        translate([6.25,8, 1]) cylinder(d=3, h=12); // right screwhole
        translate([66.5,8,1]) cylinder(d=3, h=12); // left screwhole
    }

    translate([0,13,0]) difference() { // right pad with large screwhole cut out
        cube([14,14,4]);
        translate([7,7,-1]) cylinder(d=8, h=6);
    }
}

module oldback() {
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

module back() {
    translate([32.5,3,0]) cube([12.5,87,3]); // tail

    difference() {
        translate([10,90,0]) cube([57,8,11]); // bar and towers
        translate([20,88,3]) cube([38,20,12]); // cut out middle of the bar/tower
        translate([13.8,88,7]) cube([7,8,2]); // left tower slot cut out
        translate([56,88,7]) cube([8,8,2]); // right tower slot cut out
    }
}

module transversalbar() {
    // there is a longer pad on top (or bottom...) of the bar to clamp the board better
    // the shorter pad on top of the long pad sits right above the USB-C port in an
    // attempt to provide more rigidity
    difference() {
        cube([69.5,13,2]); // bar
        translate([6.25,5,-1]) cylinder(d=3.2, h=4); // screwhole
        translate([66.5,5,-1]) cylinder(d=3.2, h=4); // screwhole
    }
    
    translate([24,1,2]) color("#0ff") cube([37,8.5,0.6]); // long pad
    translate([33,1,2.4]) color("#0ff") cube([12,8.5,1]); // short pad
}


module bracket() {
    front();
    back();
    //color("#faa",0.7) translate([66.75,98,-1]) rotate([0,0,180]) oldback();
}

bracket();
translate([64,15,0]) rotate([0,0,90]) transversalbar();

//wall2();
//translate([0,13,12.5]) rotate([180,0,0]) transversalbar();

