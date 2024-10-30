include <modules/rcube.scad>

$fn=65;

//cube([3.8,4,10]); // protrusion to fit in between the cooling fins

// rough stamp of a Sunon MF35100V1-1000U-G99
module fan() {
    sink=1;

    module screwhole() {
        translate([1.6,1.6,-sink]) cylinder(h=10+sink*2, d=3.5);
        translate([1.6,1.6,-sink]) cylinder(h=2.5+sink, d=6);
    }

    color("black") {
        translate([17.5,17.5,-sink]) cylinder(h=10+sink*2, d=33);
        translate([1.4,1.4,0]) screwhole();
        translate([1.4,30.4,0]) screwhole();
        translate([30.4,30.4,0]) screwhole();
        translate([30.4,1.4,0]) screwhole();
    }
}

module foot() {
    fullw=11.6;
    cut=3.6;

    difference() {
        cube([fullw, 10, 11.2]);
        translate([0,15.75,12]) rotate(90, [0,1,0]) translate([0,0,-1]) cylinder(h=fullw+2, r=11);
        translate([(fullw/2)-(cut/2),-1,-1]) cube([cut, 4.4, 20]);
    }
}

module toe() {
    fullw=3;
    difference() {
        cube([fullw,9.8,11.2]);
        translate([0,-5,12]) rotate(90, [0,1,0]) translate([0,0,-1]) cylinder(h=fullw+2, r=11);
    }
}



module assembly() {
    difference() {
        framet = 3;
        frameh = 35;
        framew = 78.8+(11.2*2);

        cube([framew, frameh, framet]); // main frame

        // fan is 35x35
        translate([12, 0, 0])           fan(); // fan L
        translate([framew-35-12, 0, 0]) fan(); // fan R

        // saving some material with a cutout in the middle
        saverh = 30;
        saverw = 4;
        translate([(framew/2)-(saverw/2), (frameh/2)-saverh/2, -1]) rcube([saverw, saverh, framet+2], 1);

        // cutout on the side
        sidecutw = 12;
        sidecuth = 21;
        translate([-2, 7, -1]) rcube([sidecutw, sidecuth, framet+2], 2);
        translate([framew-sidecutw+2, 7, -1]) rcube([sidecutw, sidecuth, framet+2], 2);
    }

    //translate([11.6, 38.4, 0]) rotate(180) foot();
    translate([0, -3.4, 0]) foot();
    translate([78.8+11.2, -3.4, 0]) foot();

    color("blue") translate([0.5,28.4,0]) toe();
    color("blue") translate([97.7,28.4,0]) toe();
}

difference() {
    assembly();
    //translate([19,-10,-1]) cube([100,100,100]);
    //translate([0,8,-1]) cube([100,100,100]);
}