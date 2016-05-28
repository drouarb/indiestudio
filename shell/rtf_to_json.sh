#!/usr/bin/env bash

if [ "$1" = "" ]
then
echo "./rtf_to_json file"
exit 1;
fi

NAME=$(echo $1 | cut -d '.' -f 1)

printf "{\nname : \"$1\", animation: ["

LINE=""
I=0

while read line
do
if [ ${I} -eq 0 ]
then
	printf "\n"
else
	printf ",\n"
fi
NAME="$(echo $line | cut -d ':' -f 1)"
BEGIN="$(echo $line | cut -d ':' -f 2 | cut -d '-' -f 1)"
END="$(echo $line | cut -d ':' -f 2 | cut -d '-' -f 2)"

LINE="{\nname:\"$NAME\", \nbegin:\"$BEGIN\", end: \"$END\"\n}"

I=$(($I+1))

printf "$LINE"

done < "$1"

printf "]"