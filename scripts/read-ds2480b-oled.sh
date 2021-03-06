#!/bin/bash

while [ 1 ]; do
    IFS=$'\n'
    sensor=0
    while [ $sensor -le 1 ]
    do
        temp=`digitemp_DS9097U -t $sensor -q -c /opt/beerbox/etc/digitemp.conf`
	if [ $sensor -eq 0 ];
	then
	    /opt/beerbox/bin/OLED.py --parameter TEMP_IN --value $temp
	else
	    sleep 3
	    /opt/beerbox/bin/OLED.py --parameter TEMP_OUT --value $temp
	fi
	sensor=$(( $sensor + 1 ))
    done
    sleep 3
done
