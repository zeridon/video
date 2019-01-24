#! /bin/bash
# For the lazy. This will regenerate png and svg diagrams for all three room types.
for s in small large xxl; do
	dot -Tpng "cabling_"${s}"_rooms.dot" > "cabling_"${s}"_rooms.png"
	dot -Tsvg "cabling_"${s}"_rooms.dot" > "cabling_"${s}"_rooms.svg"

done
