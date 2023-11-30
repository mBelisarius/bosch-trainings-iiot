/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t PIN_INPUT = 26;

/*--- Constants ---*/
const float VREF = 3.3f;
const uint32_t ADC_MAX = (1 << 12) - 1;
const uint32_t MMA_LEN = 500;

/*--- Variables ---*/
uint16_t input_value = 0;
float voltage = 0;

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(PIN_INPUT, INPUT);

    // Serial communication
    Serial.begin(115200);
}

/*--- Loop ---*/
void loop()
{
    input_value = 0;
    for (uint32_t i = 0; i < MMA_LEN; i++)
    {
        input_value += analogRead(PIN_INPUT);
    }
    input_value /= MMA_LEN;

    voltage = static_cast<float>(input_value) * VREF / static_cast<float>(ADC_MAX);

    Serial.print("Input: ");
    Serial.println(input_value);
    Serial.print("Voltage: ");
    Serial.println(voltage);
    Serial.println();

    delay(500);
}
