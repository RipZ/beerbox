import argparse

parser = argparse.ArgumentParser(description='oled arguments')
parser.add_argument(
    '--port', '-p',
    type=int,
    default=0,
    help='i2c bus number',
)
parser.add_argument(
    '--parameter', '-t',
    type=str,
    default='',
    help='parameter to display',
)
parser.add_argument(
    '--value', '-v',
    type=str,
    default='',
    help='value of parameter to display',
)
parser.add_argument(
    '--address', '-a',
    type=str,
    default='0x3c',
    help='i2c display address',
)
parser.add_argument(
    '--display', '-d',
    type=str,
    default='ssd1306',
    help='display type, one of ssd1306 or sh1106',
)

args = parser.parse_args()
args.address = int(args.address, 0)

import oled.device
Device = getattr(oled.device, args.display)
device = Device(port=args.port, address=args.address)
