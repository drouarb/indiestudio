#!/usr/bin/env bash


find ./ -name "*.cpp" > listFile
find ./ -name "*.hpp" >> listFile

LINE=0;

while read files
do
	NB=$(cat $files | wc -l)
	LINE=$(($LINE + $NB))
done < listFile

rm -f listFile

echo "nb line total: $LINE"

git log --author="$(git config --global user.name)" --oneline --shortstat > stat

LINE=0

while read line
do
	TMP=$(line | grep insertions | cut -d ' ' -f 2)
	if [ "$TMP" != "" ]; then
	LINE=$(($LINE + $TMP))
	fi
done < stat

echo "Line pour $(git config --global user.name): $LINE"

git log  --oneline --shortstat | grep insertions | cut -d " " -f 5 > stat
LINE=0

while read line
do
	if [ "$line" != "" ]; then
	LINE=$(($LINE + $line))
	fi
done < stat

echo "Lignes totale: $LINE"


