#!/usr/bin/env bash

while read line
do
	echo -n "{"
	line=`echo -n ${line} | tr ',\n' ' '`
	echo -n "$(echo $line | tr '[:lower:]' '[:upper:]'), "
	A=`echo ${line} | sed 's/_JSON_/\|/g'| cut -d '|' -f 1`
	A=`echo ${A} | tr '[:upper:]' '[:lower:]'`
	B=`echo ${line} | sed 's/_JSON_/\|/g' | cut -d '|' -f 2`
	echo -n "{ \"$1\", \"$B\" }"
	echo "},"
done <./.tmp