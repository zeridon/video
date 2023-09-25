#!/usr/bin/env python3

# assumptions:
# - laserbed.svg exists and is a blank SVG of 350mm x 550mm
# - arguments are basenames of SVG files of 40mm x 426.5mm (one per front plate)

import sys
import svgutils.transform as svg

if len(sys.argv) < 2:
	print('no frontplate filename supplied')
	exit(1)

if len(sys.argv) > 8:
	print('maximum 7 frontplates at a time')
	exit(1)

laserbed = svg.fromfile('laserbed.svg')

plates = sys.argv
plates.pop(0)

for i in range(len(plates)):
	plate = svg.fromfile('output/' + plates[i] + '.svg')

	root = plate.getroot()
	root.moveto(0, 45*i)

	laserbed.append([root])

laserbed.save('output/combined-' + plates[0] + '-' + plates[-1] + '.svg')
