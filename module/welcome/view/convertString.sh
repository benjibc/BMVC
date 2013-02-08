#!/bin/sh
cat $1 | sed -e 's/\\/\\\\/g
s/"/\\"/g
s/  /\\t/g
s/^/"/
s/$/\\n"/' > $2
