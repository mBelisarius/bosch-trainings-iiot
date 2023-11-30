#include <Arduino.h>

// THERMISTOR NTC_10K;
float NTC_10K_temp[] = {-55, -50, -45, -40, -35,
                        -30, -25, -20, -15, -10,
                         -5,   0,   5,  10,  15,
                         20,  25,  30,  35,  40,
                         45,  50,  55,  60,  65,
                         70,  75,  80,  85,  90,
                         95, 100, 105, 110, 115,
                        120, 125};

float NTC_10K_res[] = {1214600, 844390, 592430, 419380, 299480,
                        215670, 156410, 114660,  84510,  62927,
                         47077,  35563,  27119,  20860,  16204,
                         12683,  10000,   7942,   6327,   5074,
                          4103,   3336,   2724,   2237,   1846,
                          1530,   1275,   1068,  899.3,  760.7,
                         645.2,  549.4,  470.0,  403.6,  347.4,
                         300.1,  260.1};

// Interpolation scheme
// Linear interpolation
// Assumes x is sorted in descending order
float interp(float x[], float y[], uint16_t size, float t)
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

    return y[index] + ((y[index] - y[index - 1]) / (x[index] - x[index - 1])) * (t - x[index]);
}

// readNTC10K
float readNTC10K(uint8_t pin, float vcc, float r1, int adcMaxValue)
{
    uint16_t inputValue = analogRead(pin);
    float voltage = vcc * inputValue / (adcMaxValue - 1);
    float resistence = r1 * voltage / (vcc - voltage);
    float temperature = interp(NTC_10K_res, NTC_10K_temp, 37, resistence);

    return temperature;
}
