#!/bin/bash

OUTDIR=../dm

mkdir -p $OUTDIR

for day in 1 2; do
	for room in `grep ^1- plaintext|cut -d : -f 1|cut -d - -f 2`; do
		username=$day-$room
		password=`grep ^$username plaintext | cut -d: -f 2`
		sed "s/ROOM/$room/g;s/DAY/$day/;s/USERNAME/$username/g;s/PASSWORD/$password/g" FOSDEM_Devroom_manual.md | \
		pandoc -f markdown -t latex --template tmpl.my --variable papersize=a4paper  --variable classoption=twocolumn  --variable columnsep=1in -V geometry:margin=2cm - -o $OUTDIR/$day-$room.pdf
	done
done
