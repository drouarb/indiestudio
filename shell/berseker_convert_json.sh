#!/usr/bin/env bash

I=0

while read line
do
	echo "$line"
	if [ ${I} -eq 0 ]
	then
		printf "\n"
	else
		printf ",\n"
	fi
	NAME="$(echo $line | cut -d ':' -f 1)"
	BEGIN="$(echo $line | cut -d ':' -f 2 | cut -d '-' -f 1)"
	END="$(echo $line | cut -d ':' -f 2 | cut -d '-' -f 2)"
	END=$(echo "$BEGIN + $END" | bc)
	LINE="{\nname:\"$NAME\", \nbegin:\"$BEGIN\", end: \"$END\"\n}"
I=$(($I+1))

printf "$LINE"

done < ./berseker.txt