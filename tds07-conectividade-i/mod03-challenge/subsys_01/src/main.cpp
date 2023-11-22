/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include "ReadNTC10K.h"

#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

/*--- Hardware mapping ---*/
const uint8_t PIN_TEMP_00 = 26;
const uint8_t PIN_TEMP_01 = 25;
const uint8_t PIN_LUMINOS = 33;

/*--- Constants ---*/
const float VREF = 3.3f;
const uint16_t ADC_MAX = (1 << 12) - 1;
const float NTC_R1 = 10e3f;

const char WIFI_SSID[] = "WIFI_SSID";
const char WIFI_PASSWORD[] = "WIFI_PASSWORD";

const char FIREBASE_HOST[] = "https://<databaseName>.firebaseio.com";
const char FIREBASE_AUTH[] = "FIREBASE_AUTH";

/*--- Variables ---*/
float temp[] = { 0, 0 };
float lum = 0;
FirebaseJson json;

FirebaseData fbdo;
FirebaseAuth fbauth;
FirebaseConfig fbconfig;

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

float getAnalogVoltage(uint8_t pin, float vcc, int adc_max)
{
    uint16_t input_value = analogRead(pin);
    float voltage = input_value * vcc / static_cast<float>(adc_max);
    return voltage;
}

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(PIN_TEMP_00, INPUT);
    pinMode(PIN_TEMP_01, INPUT);
    pinMode(PIN_LUMINOS, INPUT);

    // Serial communication
    Serial.begin(115200);

    // WiFi
    connectWifi(WIFI_SSID, WIFI_PASSWORD);

    // RTDB
    fbconfig.database_url = FIREBASE_HOST;
    fbconfig.signer.tokens.legacy_token = FIREBASE_HOST;
    fbdo.setBSSLBufferSize(4096, 1024);
    Firebase.reconnectWiFi(true);
    Firebase.begin(&fbconfig, &fbauth);
}

/*--- Loop ---*/
void loop()
{
    temp[0] = readNTC10K(PIN_TEMP_00, VREF, NTC_R1, ADC_MAX);
    temp[1] = readNTC10K(PIN_TEMP_01, VREF, NTC_R1, ADC_MAX);
    lum = getAnalogVoltage(PIN_LUMINOS, VREF, ADC_MAX);

    json.set("/temperature/temp_sensor_00", temp[0]);
    json.set("/temperature/temp_sensor_01", temp[1]);
    json.set("/luminosity", lum);
    Firebase.updateNode(fbdo, "/iiot-test/subsys_01", json);

    Serial.printf("temp0=%6.2f temp1=%6.2f lum=%6.2f", temp[0], temp[1], lum);
}
