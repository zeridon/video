#!/bin/bash -e

cd `dirname "$0"`

for d in 1 2; do
	for r in `cat rooms`; do
		p=`apg -m8 -n1 -E ':$%><"'`
		echo "${d}-${r}:${p}"
	done
done

for i in `seq 0 9`; do
	p=`apg -m8 -n1 -E ':$%><"'`
	echo "voc${i}:${p}"
done
