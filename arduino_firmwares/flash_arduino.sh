#!/bin/sh

cd "$(dirname "$0")"
STOCK_FIRMWARE="Arduino-usbserial-atmega16u2-Mega2560-Rev3.hex"
STOCK_DOWNLOAD="https://raw.githubusercontent.com/harlequin-tech/arduino-usb/master/firmwares/arduino-usbserial/Arduino-usbserial-atmega16u2-Mega2560-Rev3.hex"
KEYBOARD_FIRMWARE="Arduino-keyboard.hex"
KEYBOARD_DOWNLOAD="https://raw.githubusercontent.com/harlequin-tech/arduino-usb/master/firmwares/Arduino-keyboard.hex"

if [ ! -f $STOCK_FIRMWARE ]; then
    echo "${STOCK_FIRMWARE} not found! Downloading..."
    curl -o $STOCK_FIRMWARE $STOCK_DOWNLOAD
else
    echo "${STOCK_FIRMWARE} exists!"
fi

if [ ! -f $KEYBOARD_FIRMWARE ]; then
    echo "${KEYBOARD_FIRMWARE} not found! Downloading..."
    curl -o $KEYBOARD_FIRMWARE $KEYBOARD_DOWNLOAD
else
    echo "${KEYBOARD_FIRMWARE} exists!"
fi

flash_bin=$STOCK_FIRMWARE

while getopts "kh" flags; do
    case ${flags} in
        k)
            flash_bin=$KEYBOARD_FIRMWARE
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
