PCBS=$(wildcard ../../pcbs/*/*.kicad_pcb)
NAMES=$(basename $(notdir $(PCBS)))

.phony: all make_links clean

all: $(addsuffix .stl,$(NAMES))

clean:
	rm -rf *.{kicad_pcb,vrml,stl}

make_links:
	ln -sf $(PCBS) .

$(addsuffix .vrml,$(NAMES)): %.vrml: make_links %.kicad_pcb
	kicad-cli pcb export vrml --user-origin=0x0mm --units mm -f $(filter-out $<,$^) -o $@

$(addsuffix .stl,$(NAMES)): %.stl: %.vrml
	mayo-conv $^ -e $@


