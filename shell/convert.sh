#!/usr/bin/env bash

RATIO=0.0331788079

while read line
do
    echo $line | grep begin > /dev/null
    if [ $? -eq 0 ]
    then
       VAR=$(echo $line | cut -d ':' -f 1)
       VALUE=$(echo $line | cut -d ':' -f 2 | cut -d '"' -f 2)
       VALUE=$(echo "$VALUE * $RATIO" | bc)
       echo "$VAR: \"$VALUE\","
    else
        echo $line | grep end > /dev/null
        if [ $? -eq 0 ]
        then
            VAR=$(echo $line | cut -d ':' -f 1)
            VALUE=$(echo $line | cut -d ':' -f 2 | cut -d '"' -f 2)
            VALUE=$(echo "$VALUE * $RATIO" | bc)
            echo "$VAR: \"$VALUE\","
        else
            echo $line
        fi
    fi
done < ./skeleton_footman.json