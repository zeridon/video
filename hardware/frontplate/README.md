# requirements:
#
# inkscape         https://archlinux.org/packages/extra/x86_64/inkscape/
# xmlstarlet       https://archlinux.org/packages/extra/x86_64/xmlstarlet/
# python-qrcode    https://archlinux.org/packages/extra/any/python-qrcode/
# python-svgutils  https://aur.archlinux.org/packages/python-svgutils

# assumptions:
# - the frontplate.svg file is a template for a front plate
# - this template contains elements with id box-qr and box-label

for i in {0..69}; do ./generate.sh A $i; done;


max=69

for i in $(seq 0 6 $max); do
	end=$(($i+5))

	list=""
	for j in $(seq $i $end); do
		if [ $j -gt $max ]; then
			break
		fi

		id=$(printf %03d $j)
		list="$list A$id"
	done

	./combine.py $list
done
