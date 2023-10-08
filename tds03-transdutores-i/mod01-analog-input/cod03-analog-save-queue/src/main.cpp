/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>
#include <queue>

template<class T>
using Queue = std::queue<T>;

/*--- Hardware mapping ---*/
const uint8_t PIN_INPUT = 26;

/*--- Constants ---*/
const float VREF = 3.3f;
const uint32_t ADC_MAX = (1 << 12) - 1;
const uint32_t QUEUE_SIZE = 128;

/*--- Variables ---*/
uint16_t input_value = 0;
float voltage = 0;
Queue<float> data;

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
    input_value = analogRead(PIN_INPUT);

    voltage = static_cast<float>(input_value) * VREF / static_cast<float>(ADC_MAX);

    if (data.size() >= QUEUE_SIZE) { data.pop(); }
    data.push(voltage);

    Serial.print("Voltage: ");
    Serial.println(voltage);
    Serial.print("Queue size: ");
    Serial.println(data.size());
    Serial.println();

    delay(500);
}
