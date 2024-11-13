use <nuts.scad>

$fn=120;

module through_hole() {
    circle(d=3.5);
}

module th_standoff_holes() {
    hull() {
        translate([128.46, -94.56, 0]) through_hole();
        translate([186.88, -94.56, 0]) through_hole();
    }

    hull() {
        translate([128.46, -109.8, 0]) through_hole();
        translate([186.88, -109.8, 0]) through_hole();
    }

    // caps
    hull() {
        translate([84.15, -100.35, 0]) through_hole();
        translate([86.15, -100.35, 0]) through_hole();
    }
    hull() {
        translate([84.15, -106.1, 0]) through_hole();
        translate([86.15, -106.1, 0]) through_hole();
    }

    // debug connector
    translate([0, 0.05, 0]) hull() {
        translate([135.18, -91.0, 0]) through_hole();
        translate([142.8, -91.0, 0]) through_hole();
        translate([133.54, -94.56, 0]) through_hole();
        translate([144.3, -94.56, 0]) through_hole();
    }

    // DECT module mount
    hull() {
        translate([193.75, -98.75, 0]) through_hole();
        translate([193.75, -111.45, 0]) through_hole();
    }
    hull() {
        translate([219.15, -98.75, 0]) through_hole();
        translate([219.15, -111.45, 0]) through_hole();
    }

    // XLR 1
    hull() {
        translate([84.81, -132.155, 0]) through_hole();
        translate([84.81, -137.235, 0]) through_hole();
        translate([81.0, -132.155, 0]) through_hole();
        translate([88.62, -132.155, 0]) through_hole();
    }

    // XLR 2
    hull() {
        translate([111.81, -132.155, 0]) through_hole();
        translate([111.81, -137.235, 0]) through_hole();
        translate([108.0, -132.155, 0]) through_hole();
        translate([115.62, -132.155, 0]) through_hole();
    }

    // XLR 3
    hull() {
        translate([138.81, -132.78, 0]) through_hole();
        translate([135.0, -136.595, 0]) through_hole();
        translate([142.62, -137.23, 0]) through_hole();
        translate([147.06, -142.95, 0]) through_hole();
    }

    // XLR 4
    hull() {
        translate([162.0, -136.595, 0]) through_hole();
        translate([169.62, -137.23, 0]) through_hole();
        translate([165.81, -132.78, 0]) through_hole();
        translate([174.06, -142.95, 0]) through_hole();
    }

    // XLR 5
    hull() {
        translate([189.0, -136.595, 0]) through_hole();
        translate([196.62, -137.23, 0]) through_hole();
        translate([192.81, -132.78, 0]) through_hole();
        translate([201.06, -142.95, 0]) through_hole();
    }

    // more pins on XLRs
    // translate([155.67, -139.98, 0]) through_hole();
    // translate([155.67, -147.53, 0]) through_hole();
    // translate([182.67, -139.98, 0]) through_hole();
    // translate([182.67, -147.53, 0]) through_hole();
    // translate([128.67, -139.98, 0]) through_hole();
    // translate([128.67, -147.53, 0]) through_hole();

    // mechanical holes under XLRs
    // translate([81.0, -141.045, 0]) through_hole();
    // translate([88.62, -146.125, 0]) through_hole();
    // translate([108.0, -141.045, 0]) through_hole();
    // translate([115.62, -146.125, 0]) through_hole();
    // translate([135.0, -141.04, 0]) through_hole();
    // translate([142.62, -146.12, 0]) through_hole();
    // translate([162.0, -141.04, 0]) through_hole();
    // translate([169.62, -146.12, 0]) through_hole();
    // translate([189.0, -141.04, 0]) through_hole();
    // translate([196.62, -146.12, 0]) through_hole();

    // weird holes between XLRs
    // translate([97.75, -134.75, 0]) through_hole();
    // translate([124.5, -134.75, 0]) through_hole();
    // translate([152.0, -134.75, 0]) through_hole();
    // translate([179.25, -134.75, 0]) through_hole();
    // translate([206.0, -134.75, 0]) through_hole();


    // audio jack
    hull() {
        translate([76.01, -111.95, 0]) through_hole();
        translate([78.01, -114.35, 0]) through_hole();
        translate([78.01, -119.85, 0]) through_hole();
    }

    // audio jack
    hull() {
        translate([213.25, -139.6, 0]) through_hole();
        translate([213.25, -145.1, 0]) through_hole();
        translate([215.25, -147.5, 0]) through_hole();

        // this is too close to the edge, just cut it off
        translate([213.25, -155, 0]) through_hole();
        translate([215.25, -155, 0]) through_hole();
    }

    // MTA100
    hull() {
        translate([105.25, -93.0, 0]) through_hole();
        translate([123.03, -93.0, 0]) through_hole();
    }

    // smooth drop around centre hole
    hull() {
        translate([153.4, -116.2, 0])
            circle(r=5.3);
        translate([147.8, -109.9, 0]) through_hole();
        translate([158.94, -109.9, 0]) through_hole();
    }
}

module audio_holes() {
    translate([153.4, 116.2, 0])
        circle(r=5.2);
    translate([217.75, 129, 0])
        hole_for_standoff_m3_2mm();
    translate([74.75, 93.25, 0])
        hole_for_standoff_m3_2mm();
    translate([217.75, 93.25, 0])
        hole_for_standoff_m3_2mm();
    translate([74.75, 129, 0])
        hole_for_standoff_m3_2mm();
    scale([1, -1, 1]) th_standoff_holes();
}

module audio() {
    brd_thickness = 1.6;
    color("#009900")
    scale([1, -1, 1])
    difference() {
        linear_extrude(brd_thickness) {
            polygon(points = [[222.25,90.75], [222.25,148.25], [222.22538,148.56286], [222.15212,148.86804], [222.03202,149.15798], [221.86804,149.42558], [221.66422,149.66422], [221.42558,149.86804], [221.15798,150.03202], [220.86804,150.15212], [220.56286,150.22538], [220.25,150.25], [72.25,150.25], [71.93714,150.22538], [71.63196,150.15212], [71.34202,150.03202], [71.07442,149.86804], [70.83578,149.66422], [70.63196,149.42558], [70.46798,149.15798], [70.34788,148.86804], [70.27462,148.56286], [70.25,148.25], [70.25,90.75], [70.27462,90.43714], [70.34788,90.13196], [70.46798,89.84202], [70.63196,89.57442], [70.83578,89.33578], [71.07442,89.13196], [71.34202,88.96798], [71.63196,88.84788], [71.93714,88.77462], [72.25,88.75], [220.25,88.75], [220.56286,88.77462], [220.86804,88.84788], [221.15798,88.96798], [221.42558,89.13196], [221.66422,89.33578], [221.86804,89.57442], [222.03202,89.84202], [222.15212,90.13196], [222.22538,90.43714], [222.25,90.75]]);
        }
        translate([0, 0, -1]) linear_extrude(brd_thickness+2) audio_holes();
    }
}

audio();
