/** @file keyring.ino
 *
 * @brief Type keys.
 *
 * @details
 *  - MEGA R3 firmware: https://github.com/harlequin-tech/arduino-usb
 *
 */

/*--------------------------------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------------------------------*/

#include "usb_hid_char_to_key.h"

/* *INDENT-OFF* */
/* *INDENT-ON* */

/*--------------------------------------------------------------------------------------------------
 * Global Defines
 *--------------------------------------------------------------------------------------------------*/

#define DEBUG (0)

#define HID_REPORT_SIZE (8)
#define STRING_LEN(s) (sizeof(s) / sizeof(s[0]))

/*--------------------------------------------------------------------------------------------------
 * Local typedefs
 *--------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------
 * Local Variables
 *--------------------------------------------------------------------------------------------------*/

/* *INDENT-OFF* */
/* *INDENT-ON* */

const uint8_t text[] = "Aa";
// const uint8_t text[] = "OoooOOoOOoooh! I'm a ghost!";

/*--------------------------------------------------------------------------------------------------
 * Local Function Prototypes
 *--------------------------------------------------------------------------------------------------*/

static void type_char(char c);

/*--------------------------------------------------------------------------------------------------
 * Global Function Definitions
 *--------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------
 * Local Function Definitions
 *--------------------------------------------------------------------------------------------------*/

void setup()
{
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);
    delay(500);
}

void loop()
{
    // put your main code here, to run repeatedly:
    static bool toggle;
    digitalWrite(LED_BUILTIN, toggle);

    for (uint8_t i = 0; i < STRING_LEN(text) - 1; i++)
    {
        type_char(text[i]);
    }

    delay(5000);
    toggle = !toggle;
}

static void type_char(char c)
{
    uint8_t hid_buffer[HID_REPORT_SIZE];
    uint8_t char_ind = c - ASCII_KEY_OFFSET;

    hid_buffer[0] = ascii_to_hid_key_map[char_ind][MODIFIER_KEY];
    hid_buffer[2] = ascii_to_hid_key_map[char_ind][KEY_CODE];

#if !defined(DEBUG) || (DEBUG == 0)
    Serial.write(hid_buffer, HID_REPORT_SIZE); // Send keypress
    hid_buffer[0] = 0;
    hid_buffer[2] = 0;
    Serial.write(hid_buffer, HID_REPORT_SIZE); // Release key
#else
    Serial.write(c);
    Serial.print(" - ");
    Serial.print("MOD: ");
    Serial.print(hid_buffer[0]);
    Serial.print(", Key: ");
    Serial.print(hid_buffer[2]);
    Serial.print("\n");
#endif
}
