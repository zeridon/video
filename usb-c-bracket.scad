//include <modules/standembracer.scad>

$fn = 100;

module support() {
    //right foot
    difference() { // pad with hole cut-out
        cube([18,27,4]);
        translate([9,19,-1]) cylinder(d=8, h=6);
    }

    cube([16.5,3,10]); // transversal bar holder

    cube([25,10,5]); // bottom support block (reaches under the grounding pads)

    // transversal bar
    translate([0,0,8]) cube([69,3,2]);


    // left foot
    translate([64,0,0]) cube([18,15,2]); // pad

    translate([65.5,0,0]) cube([16.5,3,10]); // transversal bar holder

    translate([64,0,0]) cube([18,10,5]); // bottom support block (reaches under the grounding pads)
}

module wall() {
    difference() { // wall with transversal slot & usb-c slot
        cube([82,3,10]);
        translate([34,-1,1]) cube([13,6,7]);
    }
}

translate([0,3,0]) support();

wall();