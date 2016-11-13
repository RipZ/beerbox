#!/bin/bash

# detect devices on 1w-bus and write config
digitemp_DS9097U -i -s /dev/ttyS1 -c /root/digitemp.conf

# read device's data on 1w-bus
#digitemp_DS9097U -a -s /dev/ttyS1 -c /root/digitemp.conf

# read one device -t 0
#digitemp_DS9097U -t 0 -q -c /root/digitemp.conf