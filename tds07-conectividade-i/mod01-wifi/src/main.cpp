/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>
#include <WiFi.h>

/*--- Constants ---*/
const char WIFI_SSID[] = "WIFI_SSID";
const char WIFI_PASSWORD[] = "WIFI_PASSWORD";

/*--- Functions ---*/
void connectWifi(const char ssid[], const char pass[])
{
    WiFi.begin(ssid, pass);

    if (Serial) { Serial.print("Connecting"); }
    while (WiFiClass::status() != WL_CONNECTED)
    {
        if (Serial)
        {
            Serial.write('.');
            delay(500);
        }
    }

    if (Serial)
    {
        Serial.print("Connected with IP: ");
        Serial.println(WiFi.localIP());
    }
}

/*--- Setup ---*/
void setup()
{
    // Serial communication
    Serial.begin(115200);

    // WiFi
    connectWifi(WIFI_SSID, WIFI_PASSWORD);
}

/*--- Loop ---*/
void loop() {}
