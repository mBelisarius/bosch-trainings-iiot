/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>
#include <vector>

template<class T>
using Vector = std::vector<T>;

/*--- Hardware mapping ---*/
const uint8_t PIN_SENSOR = 26;

/*--- Constants ---*/
const uint32_t ADC_MAX = (1 << 12) - 1;
const float VREF = 3.3f;
const float R1 = 10000;

Vector<float> NTC_10K_temp = { -55, -50, -45, -40, -35,
                               -30, -25, -20, -15, -10,
                               -5, 0, 5, 10, 15,
                               20, 25, 30, 35, 40,
                               45, 50, 55, 60, 65,
                               70, 75, 80, 85, 90,
                               95, 100, 105, 110, 115,
                               120, 125 };

Vector<float> NTC_10K_res = { 1214600, 844390, 592430, 419380, 299480,
                              215670, 156410, 114660, 84510, 62927,
                              47077, 35563, 27119, 20860, 16204,
                              12683, 10000, 7942, 6327, 5074,
                              4103, 3336, 2724, 2237, 1846,
                              1530, 1275, 1068, 899.3, 760.7,
                              645.2, 549.4, 470.0, 403.6, 347.4,
                              300.1, 260.1 };

/*--- Variables ---*/
uint16_t input_value = 0;
float voltage = 0;
float resistence = 0;
float temperature = 0;

/*--- Functions ---*/
// Interpolation scheme
// Linear interpolation
// Assumes x is sorted in descending order
float interp(Vector<float> x, Vector<float> y, float t)
{
    uint8_t index = x.size() - 1;
    for (size_t i = 1; i < x.size(); i++)
    {
        if (t > x[i])
        {
            index = i;
            break;
        }
    }

    return y[index] + ((y[index] - y[index - 1]) / (x[index] - x[index - 1]))
                      * (t - x[index]);
}

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(PIN_SENSOR, INPUT);

    // Serial communication
    Serial.begin(115200);
}

/*--- Loop ---*/
void loop()
{
    input_value = analogRead(PIN_SENSOR);

    voltage = static_cast<float>(input_value) * VREF / static_cast<float>(ADC_MAX);

    // Vout = Vin * [Rt / (R1 + Rt)]
    resistence = R1 * voltage / (VREF - voltage);

    // Interpolation
    temperature = interp(NTC_10K_res, NTC_10K_temp, resistence);

    Serial.print("Voltage: ");
    Serial.println(voltage);
    Serial.print("Resistence: ");
    Serial.println(resistence);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.println();

    delay(500);
}
