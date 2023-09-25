#!/bin/sh

# This script will generate an svg file which you can feed to a laser cutter.
# It will grab frontplate.svg as the base template, set the correct box label,
# add this to a new SVG file and repeat as many times as the number of templates
# which can be cut at a time.

labelbatch=$(echo $1 | tr 'a-z' 'A-Z')
labelid=$(printf %03d $2)

cp frontplate.svg temp.svg

# convert the template to a plain svg
inkscape --actions="export-plain-svg; export-filename: temp.svg; export-do;" temp.svg


# create a QR code
qr --factory=svg-path B-$labelbatch-$labelid > temp-qr.svg
inkscape --actions="export-id: qr-path; export-overwrite; export-plain-svg; export-filename: temp-qr.svg; export-do" temp-qr.svg
qr=$(xmlstarlet select -t -v '//_:svg/_:path/@d' temp-qr.svg)
rm temp-qr.svg

# replace the QR code
xmlstarlet ed --inplace -u "//_:svg/_:g/_:path[@id='box-qr']/@d" -v "$qr" temp.svg
xmlstarlet ed --inplace -i "//_:svg/_:g/_:path[@id='box-qr']" --type attr -n transform -v "translate(3.4,11.4)" temp.svg

# replace the box label
xmlstarlet ed --inplace -u "//_:svg/_:g/_:text[@id='box-label']/_:tspan" -v "B-$labelbatch-$labelid" temp.svg



# convert all objects to paths
inkscape --actions="select-all; object-to-path; export-plain-svg; export-filename: temp.svg; export-do;" temp.svg

mv temp.svg output/$labelbatch$labelid.svg
