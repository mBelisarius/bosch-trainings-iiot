/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include "DHT.h"
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t PIN_DHT = 26;

/*--- Constants ---*/
#define DHTTYPE DHT11

/*--- Variables ---*/
DHT dht(PIN_DHT, DHTTYPE);
float humidity = 0;
float temperature = 0;

/*--- Setup ---*/
void setup()
{
    // Initialization of dht object
    dht.begin();

    // Serial communication
    Serial.begin(115200);
}

/*--- Loop ---*/
void loop()
{
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor \n");
        return;
    }

    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.println();

    delay(2000);
}
