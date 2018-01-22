

all: ../FOSDEM_AV_manual.pdf ../FOSDEM_AV_manual.epub dm

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

dm: .depend makedep.sh tmpl.my FOSDEM_Devroom_manual.md plaintext pregen.sh dm-build-timestamp
	./pregen.sh
	touch dm-build-timestamp

clean:
	rm -f dm-build-timestamp ../dm/* ../FOSDEM_AV_manual.pdf ../FOSDEM_AV_manual.epub .depend FOSDEM_AV_manual.4ct FOSDEM_AV_manual.css  FOSDEM_AV_manual.dvi FOSDEM_AV_manual.html FOSDEM_AV_manual.idv FOSDEM_AV_manual.lg FOSDEM_AV_manual.tmp FOSDEM_AV_manual.xref  FOSDEM_AV_manual0x.png
