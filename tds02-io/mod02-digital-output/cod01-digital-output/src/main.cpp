/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t OUTPUT_PIN = 26;

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(OUTPUT_PIN, OUTPUT);
}

/*--- Loop ---*/
void loop()
{
    digitalWrite(OUTPUT_PIN, HIGH);
    delay(500);

    digitalWrite(OUTPUT_PIN, LOW);
    delay(500);
}
