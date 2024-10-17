use <nuts.scad>

module radxa_x4_holes() {
    radxa_x4_mounting_holes();
    radxa_x4_protrusion_cutouts();
}

module radxa_x4_mounting_holes() {
    translate([3.53,3.5,0]) nuthole_m25();
    translate([3.53,56-3.5,0]) nuthole_m25();
    translate([3.53+58,3.5,0]) nuthole_m25();
    translate([3.53+58,56-3.5,0]) nuthole_m25();
}

module radxa_x4_protrusion_cutouts() {
    // TODO: proper cutouts under radxa
    // hole for power inductors to fit into (they are tall)
    translate([12, 5.5, 0]) rrect(25 - 12, 43, 2);
    hull() {
        translate([19.5, 51.5, 0]) circle(d=6);
        translate([19.5, 40, 0]) circle(d=6);
    }
    translate([51.5, 47.5, 0]) circle(d=6);
    
    translate([70, 0, 0]) rrect(15.5, 56, 2);
    
    translate([83, 7.5, 0]) circle(d=11);
    translate([83, 27.5, 0]) circle(d=11);
}

module radxa_x4_thermal_zone() {
    translate([26, 15, 0])
    rrect(35, 24, 1.5);
}

module radxa_x4() {
    brd_thickness = 1.6;
    // precise measurements available at
    // https://dl.radxa.com/x/x4/radxa_x4_product_brief.pdf
    union() {
        // board
        color("#ebac54")
        linear_extrude(brd_thickness)
        difference() {
            union() {
                rrect(85, 56, 3);
                translate([4, 56 - 4, 0]) rrect(56, 6, 2);
            }
           
            radxa_x4_mounting_holes();
        };
        
        color("gray")
        translate([0, 0, -1.5])
        linear_extrude(1.5)
        radxa_x4_protrusion_cutouts();
        
        // thermal zone
        color("cyan")
        translate([0, 0, -1])
        linear_extrude(1)
        radxa_x4_thermal_zone();
    }
}

rotate([0, 180, 0]) radxa_x4();