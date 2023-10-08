/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t BUTTON = 13;
const uint8_t LED = 26;

/*--- Variables ---*/
bool input_value = false;

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(BUTTON, INPUT);
    pinMode(LED, OUTPUT);
}

/*--- Loop ---*/
void loop()
{
    input_value = digitalRead(BUTTON);

    digitalWrite(LED, input_value);
}
