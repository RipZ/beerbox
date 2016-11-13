#!/bin/bash

while [ 1 ]; do
    IFS=$'\n'
    sensor=0
    TIME=`date "+%d-%m-%Y %T"`
    echo -n "$TIME " >> /var/log/temperature.log
    while [ $sensor -le 6 ]
    do
	if [ $sensor -eq 0 ];
	then
	    echo -n "[out]=`digitemp_DS9097U -t $sensor -q -c /root/digitemp.conf`" >> /var/log/temperature.log
	else
	    echo -n ", [in$sensor]=`digitemp_DS9097U -t $sensor -q -c /root/digitemp.conf`" >> /var/log/temperature.log
	fi
	sensor=$(( $sensor + 1 ))
    done
    echo "" >> /var/log/temperature.log
    sleep 300
done
