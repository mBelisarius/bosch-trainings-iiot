/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t PIN_SENSOR = 33;

/*--- Constants ---*/
const uint32_t ADC_MAX = (1 << 12) - 1;
const float VREF = 3.3f;
const float R1 = 10000.0f;

/*--- Variables ---*/
float voltage = 0.0f;
float resistence = 0.0f;
float temperature = 0.0f;

/*--- Functions ---*/
float temperatureNTC10K(float res)
{
    return -19.49123972f * log(res - 204.49123972f) + 208.78577114f;
}

float calibratedVoltage(float raw_voltage)
{
    const float a = -0.0591924f,
                b =  0.1815789f,
                c =  0.0267364f;

    return raw_voltage + ((a * raw_voltage + b) * raw_voltage + c);
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
    voltage = static_cast<float>(analogRead(PIN_SENSOR)) * VREF
              / static_cast<float>(ADC_MAX);
    voltage = calibratedVoltage(voltage);
    resistence = R1 * voltage / (VREF - voltage);
    temperature = temperatureNTC10K(resistence);

    Serial.print("Temperature: ");
    Serial.println(temperature);

    delay(500);
}
