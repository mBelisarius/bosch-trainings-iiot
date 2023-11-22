#ifndef READNTC10K_H
#define READNTC10K_H

#include <Arduino.h>

/** Temperature experimental data for the NTC10K sensor. */
static const float NTC10K_TEMPERATURE[] = {
    -55,
    -50,
    -45,
    -40,
    -35,
    -30,
    -25,
    -20,
    -15,
    -10,
    -5,
    0,
    5,
    10,
    15,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
    55,
    60,
    65,
    70,
    75,
    80,
    85,
    90,
    95,
    100,
    105,
    110,
    115,
    120,
    125,
};

/** Resistence experimental data for the NTC10K sensor. */
static const float NTC10K_RESISTENCE[] = {
    1214600,
    844390,
    592430,
    419380,
    299480,
    215670,
    156410,
    114660,
    84510,
    62927,
    47077,
    35563,
    27119,
    20860,
    16204,
    12683,
    10000,
    7942,
    6327,
    5074,
    4103,
    3336,
    2724,
    2237,
    1846,
    1530,
    1275,
    1068,
    899.3,
    760.7,
    645.2,
    549.4,
    470.0,
    403.6,
    347.4,
    300.1,
    260.1,
};

/**
 * Linear interpolation scheme.
 * Assumes x is sorted in descending order
 */
inline float interp(const float x[], const float y[], uint16_t size, float t)
{
    uint16_t index = size - 1;
    for (uint16_t i = 1; i < size; i++)
    {
        if (t > x[i])
        {
            index = i;
            break;
        }
    }

    return y[index] + ((y[index] - y[index - 1]) / (x[index] - x[index - 1])) *
           (t - x[index]);
}

/** Read the temperature from a NTC10K sensor. */
inline float readNTC10K(uint8_t pin, float vref, float r1, int adc_max)
{
    float input_value = analogRead(pin);
    float voltage = input_value * vref / static_cast<float>(adc_max);
    float resistence = r1 * voltage / (vref - voltage);
    float temperature = interp(NTC10K_RESISTENCE, NTC10K_TEMPERATURE, 37, resistence);

    return temperature;
}

#endif
