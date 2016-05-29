#!/usr/bin/env bash


while [ "$1" != "" ]
do
	cat $1 | grep "name\:" > .tmp

	while read line
	do
		echo -n "$1_" | tr '[:lower:]' '[:upper:]' | tr '\.' '_' | tr '_json' '_'
		echo "$line " | cut -d '"' -f 2 | tr '[:lower:]' '[:upper:]' | tr '\n' ' '
		echo ","
#		echo -n ", \""
#		echo -n "$line" | cut -d '"' -f 2 | tr '\n' ' '
#		echo "\""
	done < .tmp
shift
done