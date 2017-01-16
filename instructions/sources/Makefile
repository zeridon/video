

all: ../FOSDEM_AV_manual.pdf ../FOSDEM_AV_manual.epub

depend: .depend

.depend: $(wildcard *.tex) makedep.sh
	rm -f .depend
	./makedep.sh > .depend

-include .depend

../FOSDEM_AV_manual.pdf: FOSDEM_AV_manual.tex
	pdflatex FOSDEM_AV_manual.tex
	mv FOSDEM_AV_manual.pdf ..

../FOSDEM_AV_manual.epub: FOSDEM_AV_manual.tex
	mk4ht htlatex FOSDEM_AV_manual.tex 'xhtml,charset=utf-8,pmathml' ' -cunihtf -utf8 -cvalidate'
	ebook-convert FOSDEM_AV_manual.html ../FOSDEM_AV_manual.epub  --language en --no-default-epub-cover
