/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t N_PORTS = 6;
const uint8_t PINS_INPUT[] = { 14, 27, 26, 25, 33, 32 };

/*--- Variables ---*/
uint32_t input_value = 0;

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    for (auto i : PINS_INPUT)
    {
        pinMode(i, INPUT);
    }

    // Serial communication
    Serial.begin(115200);
}

/*--- Loop ---*/
void loop()
{
    input_value = 0;
    for (uint8_t i = 0; i < N_PORTS; i++)
    {
        input_value += digitalRead(PINS_INPUT[i]) * (1 << i);
    }

    Serial.println(input_value);

    delay(500);
}
