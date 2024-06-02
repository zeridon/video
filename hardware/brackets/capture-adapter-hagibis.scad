$fn=100;

color("green") {
    difference() {
        square([75,108.5]);
        translate([2.5,2.5,-1]) circle(d=3);
        translate([61.5,2.5,-1]) circle(h=10,d=3);
        translate([2.5,105.5,-1]) circle(h=10,d=3);
        translate([61.5,105.5,-1]) circle(h=10,d=3);

        // hagibis
        translate([18.5,2.5,-1]) circle(h=10,d=3);
        translate([70,2.5,-1]) circle(h=10,d=3);

        translate([18.5,54,-1]) circle(h=10,d=3);
        translate([70,54,-1]) circle(h=10,d=3);

    }
}
    
    
    
    
