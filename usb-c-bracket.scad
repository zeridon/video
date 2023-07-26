include <modules/standembracer.scad>

$fn = 100;

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

    translate([61.5,-4,0]) cube([3.8,4,10]); // protrusion to fit in between the cooling fins
}

module back() {
    translate([14,3,0]) cube([6,87,3]); // left tail
    translate([44,3,0]) cube([6,87,3]); // right tail
    translate([14,5,0]) rotate([0,0,-20]) cube([4,90,3]); // cross tail

    difference() {
        translate([10,90,0]) cube([57,8,11]); // bar and towers
        translate([20,88,3]) cube([38,20,12]); // cut out middle of the bar/tower
        translate([13.8,88,7]) cube([7,8,2]); // left tower slot cut out
        translate([56,88,7]) cube([8,8,2]); // right tower slot cut out

        translate([9,95,-1]) cube([3.2,4,4]); // left tower bottom corner standembracer cut out
    }

    translate([7,99.5,0]) standembracer(4); // hugging the standoff in the case
}

module transversalbar() {
    // there is a longer pad on top (or bottom...) of the bar to clamp the board better
    // the shorter pad on top of the long pad sits right above the USB-C port in an
    // attempt to provide more rigidity
    difference() {
        cube([69.5,13,2]); // bar
        translate([6.25,5,-1]) cylinder(d=3.6, h=4); // screwhole
        translate([66.5,5,-1]) cylinder(d=3.6, h=4); // screwhole
    }
    
    translate([24,1,2]) color("#0ff") cube([37,7,0.6]); // long pad
    translate([33,1,2.4]) color("#0ff") cube([12,7,1]); // short pad
}

module bracket() {
    front();
    back();
}

bracket();
translate([68,16,0]) rotate([0,0,90]) transversalbar();