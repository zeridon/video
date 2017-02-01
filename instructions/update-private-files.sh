#!/bin/sh

if [ $# != 1 -o ! -d $1 ]; then
  echo "ERROR: please tell me where I can find the private files."
  echo "usage: $(basename $0) <directory>"
  exit 1
fi

echo -n "copying private files from ${1}... "

cp $1/control/plaintext sources/

echo "done."
