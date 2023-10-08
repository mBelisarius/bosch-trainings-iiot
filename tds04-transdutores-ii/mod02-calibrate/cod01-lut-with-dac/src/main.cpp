/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include "driver/dac.h"
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t PIN_ADC = 33;
#define PIN_DAC DAC_CHANNEL_1

/*--- Constants ---*/
const uint32_t ADC_BITS = 12;
const uint32_t ADC_MAX = 4096;

/*--- Variables ---*/
float results[ADC_MAX] = { 0 };

/*--- Functions ---*/
void buildLUT(uint8_t samples = 128, uint8_t delay = 10)
{
    for (uint16_t i = 0; i < ADC_MAX; i++)
    {
        dac_output_voltage(PIN_DAC, round(static_cast<float>(i) * 256.0f
                                          / static_cast<float>(ADC_MAX)));
        for (uint8_t j = 0; j < samples; j++)
        {
            delayMicroseconds(delay);
            results[i] += static_cast<float>(analogRead(PIN_ADC))
                          / static_cast<float>(samples);
        }
    }
}

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(PIN_ADC, INPUT);
    analogReadResolution(ADC_BITS);
    dac_output_enable(PIN_DAC);
    dac_output_voltage(PIN_DAC, 0);

    // Serial communication
    Serial.begin(115200);
}

/*--- Loop ---*/
void loop()
{
    buildLUT();

    Serial.println("const float ADC_LUT[4096] = { 0,");

    for (uint16_t i = 1; i < ADC_MAX; i++)
    {
        Serial.print(results[i], 4);
        Serial.print(", ");
        if ((i + 1) % 16 == 0) { Serial.println(); }
    }

    Serial.println("};");
}
