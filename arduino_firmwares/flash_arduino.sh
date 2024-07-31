#!/bin/sh

cd "$(dirname "$0")"

flash_bin="Arduino-usbserial-atmega16u2-Mega2560-Rev3.hex"

while getopts "kh" flags; do
    case ${flags} in
        k)
            flash_bin="Arduino-keyboard.hex"
            ;;
        h)
            echo "Use -k to flash Arduino-keyboard.hex,"\
            "or nothing to reflash stock firmware."
            exit 0
            ;;
    esac
done

echo Selected file: $flash_bin

sudo dfu-programmer atmega16u2 erase
sudo dfu-programmer atmega16u2 flash ${flash_bin}
sudo dfu-programmer atmega16u2 reset
