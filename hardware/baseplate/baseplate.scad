$fn=120;
brd_thickness = 1.6;

module case() {
    supportd=10.5;
    screwd=7.5;
    color("red", 0.1) {
        difference() {
            square(size=[423.8,195.0]);

            // case lock things
            translate([0,6.5,0]) square(size=[6.5,14.5]);
            translate([0,173.5,0]) square(size=[6.5,14.5]);
            translate([417.3,7,0]) square(size=[6.5,14.5]);
            translate([417.3,173.5,0]) square(size=[6.5,14.5]);

            // screw stands
            // outer
            hull() {
                // this hole is too close to the fan
                // cutout, so merge the cut
                translate([12,40,0]) circle(d=screwd);
                translate([20.4,33.85,0]) circle(d=screwd);
            }
            translate([20.4,161.15,0]) circle(d=screwd);
            translate([403.05,33.85,0]) circle(d=screwd);
            translate([403.05,161.15,0]) circle(d=screwd);

            // inner
            translate([148.15,33.85,0]) circle(d=screwd);
            translate([148.15,161.15,0]) circle(d=screwd);
            translate([275.65,33.85,0]) circle(d=screwd);
            translate([275.65,161.15,0]) circle(d=screwd);

            // support stands
            translate([100.05,33.85,0]) circle(d=supportd);
            translate([100.05,161.15,0]) circle(d=supportd);
            translate([323.5,33.85,0]) circle(d=supportd);
            translate([323.5,161.15,0]) circle(d=supportd);
        }
    }
}

module nuthole_m2() {
    circle(r=1.055);
}

module nuthole_m3() {
    circle(r=1.61);
}

module rrect(w,l,r) {
    translate([r,r,0]) {
        minkowski() {
            square(size = [w-(2*r), l-(2*r)]);
            circle(r=r);
        }
    }
}

module switch_holes() {
    translate([172, 100, -1]) nuthole_m3();
    translate([119,  64, -1]) nuthole_m3();
    translate([166,  64, -1]) nuthole_m3();
    translate([ 99,  99, -1]) nuthole_m3();
}

module switch() {
    color("#009900")
    scale([1, -1, 1])
    difference() {
        linear_extrude(brd_thickness) {
            polygon(points = [[175,142], [95,142], [94.68714,141.97538], [94.38196,141.90212], [94.09202,141.78202], [93.82442,141.61804], [93.58578,141.41422], [93.38196,141.17558], [93.21798,140.90798], [93.09788,140.61804], [93.02462,140.31286], [93,140], [93,61], [93.02462,60.68714], [93.09788,60.38196], [93.21798,60.09202], [93.38196,59.82442], [93.58578,59.58578], [93.82442,59.38196], [94.09202,59.21798], [94.38196,59.09788], [94.68714,59.02462], [95,59], [169,59], [169.31286,59.02462], [169.61804,59.09788], [169.90798,59.21798], [170.17558,59.38196], [170.41422,59.58578], [170.61804,59.82442], [170.78202,60.09202], [170.90212,60.38196], [170.97538,60.68714], [171,61], [171,92], [171.02462,92.31286], [171.09788,92.61804], [171.21798,92.90798], [171.38196,93.17558], [171.58578,93.41422], [171.82442,93.61804], [172.09202,93.78202], [172.38196,93.90212], [172.68714,93.97538], [173.0,94.0], [175,94], [175.31286,94.02462], [175.61804,94.09788], [175.90798,94.21798], [176.17558,94.38196], [176.41422,94.58578], [176.61804,94.82442], [176.78202,95.09202], [176.90212,95.38196], [176.97538,95.68714], [177,96], [177,140], [176.97538,140.31286], [176.90212,140.61804], [176.78202,140.90798], [176.61804,141.17558], [176.41422,141.41422], [176.17558,141.61804], [175.90798,141.78202], [175.61804,141.90212], [175.31286,141.97538], [175,142]]);
        }
        translate([0, 0, -1]) linear_extrude(brd_thickness+2) switch_holes();
    }
}

module audio_holes() {
    translate([153.4, 116.2, -1])
        circle(r=4.4);
    translate([217.75, 129, -1])
        nuthole_m3();
    translate([74.75, 93.25, -1])
        nuthole_m3();
    translate([217.75, 93.25, -1])
        nuthole_m3();
    translate([74.75, 129, -1])
        nuthole_m3();
}

module audio() {
    color("#009900")
    scale([1, -1, 1])
    difference() {
        linear_extrude(brd_thickness) {
            polygon(points = [[222.25,90.75], [222.25,148.25], [222.22538,148.56286], [222.15212,148.86804], [222.03202,149.15798], [221.86804,149.42558], [221.66422,149.66422], [221.42558,149.86804], [221.15798,150.03202], [220.86804,150.15212], [220.56286,150.22538], [220.25,150.25], [72.25,150.25], [71.93714,150.22538], [71.63196,150.15212], [71.34202,150.03202], [71.07442,149.86804], [70.83578,149.66422], [70.63196,149.42558], [70.46798,149.15798], [70.34788,148.86804], [70.27462,148.56286], [70.25,148.25], [70.25,90.75], [70.27462,90.43714], [70.34788,90.13196], [70.46798,89.84202], [70.63196,89.57442], [70.83578,89.33578], [71.07442,89.13196], [71.34202,88.96798], [71.63196,88.84788], [71.93714,88.77462], [72.25,88.75], [220.25,88.75], [220.56286,88.77462], [220.86804,88.84788], [221.15798,88.96798], [221.42558,89.13196], [221.66422,89.33578], [221.86804,89.57442], [222.03202,89.84202], [222.15212,90.13196], [222.22538,90.43714], [222.25,90.75]]);
        }
        translate([0, 0, -1]) linear_extrude(brd_thickness+2) audio_holes();
    }
}

module power_holes() {
    translate([493, 132, -1])
        nuthole_m3();
    translate([433, 66.5, -1])
        nuthole_m3();
    translate([498, 85, -1])
        nuthole_m3();
    translate([433, 132, -1])
        nuthole_m3();
}

module power() {
    color("#009900")
    scale([1, -1, 1])
    difference() {
        linear_extrude(brd_thickness) {
            polygon(points = [[497,135], [497,93], [497.01848,92.52924], [497.07386,92.06142], [497.16578,91.5993], [497.29364,91.14588], [497.45672,90.70392], [497.65394,90.27606], [497.88416,89.865], [498.14588,89.47326], [498.43754,89.1033], [498.75734,88.75734], [499.1033,88.43754], [499.47326,88.14588], [499.865,87.88416], [500.27606,87.65394], [500.70392,87.45672], [501.14588,87.29364], [501.5993,87.16578], [502.06142,87.07386], [502.52924,87.01848], [503,87], [515,87], [515.15643,86.98769], [515.30902,86.95106], [515.45399,86.89101], [515.58779,86.80902], [515.70711,86.70711], [515.80902,86.58779], [515.89101,86.45399], [515.95106,86.30902], [515.98769,86.15643], [516.0,86.0], [516,61.000001], [515.9848098481,60.8263482634], [515.9396893969,60.657976579700005], [515.8660186602,60.500005], [515.7660376604,60.3572135721], [515.6427864279,60.233962339600005], [515.499995,60.1339813398], [515.3420234203,60.06031060310001], [515.1736517366,60.0151901519], [515.0000000001,60.0], [430,60], [429.84357,60.01231], [429.69098,60.04894], [429.54601,60.10899], [429.41221,60.19098], [429.29289,60.29289], [429.19098,60.41221], [429.10899,60.54601], [429.04894,60.69098], [429.01231,60.84357], [429.0,61.0], [429,135], [429.01231,135.15643], [429.04894,135.30902], [429.10899,135.45399], [429.19098,135.58779], [429.29289,135.70711], [429.41221,135.80902], [429.54601,135.89101], [429.69098,135.95106], [429.84357,135.98769], [430.0,136.0], [496,136], [496.15643,135.98769], [496.30902,135.95106], [496.45399,135.89101], [496.58779,135.80902], [496.70711,135.70711], [496.80902,135.58779], [496.89101,135.45399], [496.95106,135.30902], [496.98769,135.15643], [497.0,135.0]]);
        }
        translate([0, 0, -1]) linear_extrude(brd_thickness+2) power_holes();
    }
}
display_size_x = 70;
display_size_y = 22.5;

module display_footprint() {
    union() {
        rrect(display_size_x, display_size_y, 2);
        square([display_size_x, 2]);
    }
}

harness_hole_spacing = 4.5;
module display_holes() {
    half_hole_spacing_x = (128.4175 - 70.4175) / 2;
    centre_x = display_size_x / 2;
    translate([-harness_hole_spacing, harness_hole_spacing]) nuthole_m3();
    translate([-harness_hole_spacing, 16]) nuthole_m3();
    translate([display_size_x + harness_hole_spacing, harness_hole_spacing]) nuthole_m3();
    translate([display_size_x + harness_hole_spacing, 16]) nuthole_m3();
    translate([centre_x - half_hole_spacing_x, harness_hole_spacing + display_size_y]) nuthole_m3();
    translate([centre_x + half_hole_spacing_x, harness_hole_spacing + display_size_y]) nuthole_m3();
}

module display_cutout() {
    display_holes();
    display_footprint();
}

module display() {
    linear_extrude(20)
    display_cutout();
}

onlyfans_size_x = 16.5;
onlyfans_size_y = 105;

module onlyfans_holes() {
    translate([harness_hole_spacing, -harness_hole_spacing]) nuthole_m3();
    translate([12, -harness_hole_spacing]) nuthole_m3();
    translate([harness_hole_spacing, harness_hole_spacing + onlyfans_size_y]) nuthole_m3();
    translate([12, harness_hole_spacing + onlyfans_size_y]) nuthole_m3();
}

module onlyfans_footprint() {
    union() {
        rrect(onlyfans_size_x, onlyfans_size_y, 2);
        square([3, onlyfans_size_y]);
    }
}

module onlyfans_cutout() {
    onlyfans_holes();
    onlyfans_footprint();
}

module onlyfans() {
    linear_extrude(20)
    onlyfans_cutout();
}

module hdmi_holes() {
    translate([4,54,0]) nuthole_m3();
    translate([54,54,0]) nuthole_m3();

    translate([4,4,0]) nuthole_m3();
    translate([54,4,0]) nuthole_m3();
}

module hdmi() {
    // fixme: re-measure
    linear_extrude(brd_thickness)
    difference() {
        rrect(58,58,2);
        hdmi_holes();
    }
}

module radxa_x2l_holes() {
    translate([4, 3.8, 0]) nuthole_m2();
    translate([4, 3.8+58.4, 0]) nuthole_m2();
    translate([4+58.2, 3.8, 0]) nuthole_m2();
    translate([4+58.2, 3.8+49.2, 0]) nuthole_m2();
    translate([4+148.2, 3.8, 0]) nuthole_m2();
    translate([4+148.2, 3.8+58.4, 0]) nuthole_m2();
}

module radxa_x2l() {
    // precise measurements available at https://dl.radxa.com/x/x2l/radxa_x2l_product_brief.pdf
    linear_extrude(brd_thickness)
    difference() {
        rrect(155.6,80.6,2);
        radxa_x2l_holes();
    }
}

module radxa_x4_holes() {
    translate([3.53,3.5,0]) nuthole_m3();
    translate([3.53,56-3.5,0]) nuthole_m3();
    translate([3.53+58,3.5,0]) nuthole_m3();
    translate([3.53+58,56-3.5,0]) nuthole_m3();

    // hole for power inductors to fit into (they are tall)
    translate([8, 6, 0]) rrect(10, 45, 2);
}


module radxa_x4() {
    // precise measurements available at
    // https://dl.radxa.com/x/x4/radxa_x4_product_brief.pdf
    color("#ebac54")
    linear_extrude(brd_thickness)
    difference() {
        union() {
            rrect(85, 56, 3);
            translate([4, 56 - 4, 0]) rrect(56, 6, 2);
        }
        radxa_x4_holes();
    };
}

switch_transl = [187.5,53,0];
power_transl = [523.5,-60,0];
audio_transl = [170,150,0];
radxa_x2l_transl = [265,191,0];
radxa_x4_transl = [150,133,0];
hdmi_transl = [329.5,136.9,0];
onlyfans_transl = [0, 34.5, 0];
display_transl = [120, 0, 0];

module case_with_holes() {
    difference() {
        case();

        translate(switch_transl) rotate(180) scale([1, -1, 1]) switch_holes();
        translate(power_transl) rotate(180) scale([1, -1, 1]) power_holes();
        translate(audio_transl) scale([1, -1, 1]) audio_holes();
        translate(radxa_x2l_transl) rotate(180) radxa_x2l_holes();
        translate(radxa_x4_transl) radxa_x4_holes();
        translate(hdmi_transl) hdmi_holes();
        translate(onlyfans_transl) onlyfans_cutout();
        translate(display_transl) display_cutout();
    };
}

module boards() {
    translate(switch_transl) rotate(180) switch();
    translate(power_transl) rotate(180) power();
    translate(audio_transl) audio();
    translate(radxa_x2l_transl) rotate(180) radxa_x2l();
    translate([0, 0, 5]) translate(radxa_x4_transl) radxa_x4();
    translate(hdmi_transl) hdmi();
    translate(onlyfans_transl) onlyfans();
    translate(display_transl) display();
}

// boards();
case_with_holes();
