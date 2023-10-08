/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t PIN_INPUT = 26;
const uint8_t PIN_LED = 25;

/*--- Constants ---*/
const uint32_t ADC_MAX = (1 << 12) - 1;

/*--- Variables ---*/
uint16_t input_value = 0;

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(PIN_INPUT, INPUT);
    pinMode(PIN_LED, OUTPUT);

    // Serial communication
    Serial.begin(115200);
}

/*--- Loop ---*/
void loop()
{
    input_value = analogRead(PIN_INPUT);

    digitalWrite(PIN_LED, (input_value > 2048));

    Serial.print("Input: ");
    Serial.println(input_value);
    Serial.println();

    delay(500);
}
