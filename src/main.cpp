/**
 * Main
 */

#include <Arduino.h>

void
setup ()
{
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
}

void
loop ()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);

    static uint8_t i = 0;
    Serial.print("Count: ");
    Serial.print(i);
    Serial.print("\n");
    i++;
}
