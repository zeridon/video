#!/bin/bash -e

cd `dirname "$0"`

for d in 1 2; do
	for r in `cat rooms`; do
		p=`pwgen -B 8 1`
		echo "${d}-${r}:${p}"
	done
done

for i in `seq 0 9`; do
	p=`pwgen -B 8 1`
	echo "voc${i}:${p}"
done
