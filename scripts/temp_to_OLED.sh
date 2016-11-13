#!/bin/bash

DELAY=3

while [ 1 ]; do
    IFS=$'\n'

    CPU_TEMP=`cat /sys/class/thermal/thermal_zone1/temp`
    /opt/beerbox/bin/OLED.py --parameter CPU_TEMP --value $CPU_TEMP
    sleep $DELAY

    sensor=0
    while [ $sensor -le 1 ]
    do
        temp=`digitemp_DS9097U -t $sensor -q -r2000 -c /opt/beerbox/etc/digitemp.conf`
	case $sensor in
	    0)
		/opt/beerbox/bin/OLED.py --parameter TEMP_IN --value $temp
		sleep $DELAY
		;;
	    1)
		/opt/beerbox/bin/OLED.py --parameter TEMP_OUT --value $temp
		sleep $DELAY
		;;
	esac
	echo $temp > /tmp/sensors/$sensor
	sensor=$(( $sensor + 1 ))
    done
done
