Program for indexing files.

An index is labelled in a text with a:
\index{index name}{index entry}

An index is printed with a command:
\printindex{index name}{index header}

An index has a header. Index entries are printed in alphabetical order. Each
entry is followed by line numbers holding the entry. Duplicates of line numbers
for one entry are not used. This is a command line program with switches:
-i input text file
-o output file
