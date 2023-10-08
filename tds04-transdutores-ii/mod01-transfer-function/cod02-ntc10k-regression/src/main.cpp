/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t PIN_SENSOR = 26;

/*--- Constants ---*/
const uint32_t ADC_MAX = 4096;
const float VREF = 3.3f;
const float R1 = 10000;

/*--- Variables ---*/
uint16_t input_value = 0;
float voltage = 0;
float resistence = 0;
float temperature = 0;

/*--- Functions ---*/
float regressor(float x)
{
    return -19.49123972f * log(x - 204.88328885f) + 208.78577114f;
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
    voltage = static_cast<float>(input_value) * VREF
              / static_cast<float>(ADC_MAX);

    // Vout = Vin * [Rt / (R1 + Rt)]
    resistence = R1 * voltage / (VREF - voltage);

    temperature = regressor(resistence);

    Serial.print("Voltage: ");
    Serial.println(voltage);
    Serial.print("Resistence: ");
    Serial.println(resistence);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.println();

    delay(500);
}
