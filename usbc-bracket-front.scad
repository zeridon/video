$fn=50;

module arm() {
    difference() {
        cube([56,5,2]);
        translate([6,3,-1])
            cube([44,3,4]);
    }
}


// version +1mm arm width, -1mm height
module foot() {
    cube([18,5,5]);

    translate([13,0,5])
        cube([3.5,5,3,]);
    
    cube([18,15,2]);
}

translate([13,0,8])
    arm();

foot();

//translate([59,0,0])
//translate([13,5,0])
//rotate(a=[0,0,-180])
mirror()
   translate([-82,0,0])
      foot();