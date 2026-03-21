Building this document:

For building the typst file, install https://github.com/typst/typst/ .

Now run:
<pre>typst compile FOSDEM_AV_manual.typ --root ../../</pre>

## obsolete TeX file
For building the obsolete TeX file, install some dependencies:
<pre>apt-get install texlive texlive-latex-extra calibre tex4ht</pre>

Now run make:
<pre>make</pre>

It will build a pdf and epub files.
