#!/usr/bin/env python3

# Ported from:
# https://github.com/adafruit/Adafruit_Python_SSD1306/blob/master/examples/shapes.py

import os
import sys

from opts import device
from oled.render import canvas
from PIL import ImageFont
from opts import args

if args.parameter is (''):
    print ('empty parameter')
    sys.exit (1)

if args.value is (''):
    print ('empty value of parameter')
    sys.exit (1)

with canvas(device) as draw:

    padding = 2
    top = padding
    x = padding
    font_path_small = os.path.abspath(os.path.join(os.path.dirname(__file__), '/opt/beerbox', 'fonts', 'radiospace.ttf'))
    font_path_big = os.path.abspath(os.path.join(os.path.dirname(__file__), '/opt/beerbox', 'fonts', 'digital-7.ttf'))
    font_small = ImageFont.truetype(font_path_small, 16)

    # check if temperature over 0 degrees and add + before value
    if "-" not in args.value:
     args.value = '+' + args.value

    # check if temperature is 0.0 degrees - display as 0 without + and -
    if "0.0" in args.value:
     args.value = '0 C'

    if args.parameter in ('TANK_TEMP', ''):
     font_big = ImageFont.truetype(font_path_big, 64)
     draw.text((x, top+5), args.value,  font=font_big, fill=255)

    else:
     font_big = ImageFont.truetype(font_path_big, 54)
     draw.text((x, top), args.parameter + ': ',  font=font_small, fill=255)
     draw.text((x, top+20), args.value,  font=font_big, fill=255)
