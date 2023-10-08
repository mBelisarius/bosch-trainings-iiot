/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t LED_PIN = 2;

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(LED_PIN, OUTPUT);
}

/*--- Loop ---*/
void loop()
{
    digitalWrite(LED_PIN, HIGH);
    delay(500);

    digitalWrite(LED_PIN, LOW);
    delay(500);
}
