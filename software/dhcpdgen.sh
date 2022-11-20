#!/bin/bash
grep -E 'slides[0-9]|cam[0-9]|voctop[0-9]' README.md | awk '{print "host "$4" {\n\tfixed-address "$6";\n\thardware ethernet "$2";\n}"}' |tr -d \`
