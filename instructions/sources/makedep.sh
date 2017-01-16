#!/bin/bash

for i in *.tex; do
	pdfn=`echo $i|sed s/\.tex$/.pdf/`
	epubn=`echo $i|sed s/\.tex$/.epub/`
	echo $pdfn: `grep includegraphics FOSDEM_AV_manual.tex |cut -d \{ -f 2|cut -d \} -f 1|sort|uniq |grep '\.'`
	echo $epubn: `grep includegraphics FOSDEM_AV_manual.tex |cut -d \{ -f 2|cut -d \} -f 1|sort|uniq |grep '\.'`
done
