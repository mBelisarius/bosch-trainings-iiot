/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include "ReadNTC10K.h"
#include <Arduino.h>
#include <FirebaseESP32.h>
#include <WiFi.h>

/*--- Hardware mapping ---*/
#define TEMP_00 33
#define TEMP_01 32
#define LUMINOS 35

/*--- Constants ---*/
#define VCC 3.3
#define ADC_MAX 4096
#define NTC_R1 100000

#define WIFI_SSID "belisarius"
#define WIFI_PASSWORD "senhasenha"

#define FIREBASE_HOST "https://iiot-test-ac322-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "FTForHPlEfGrBHp7urRMRge0H7YKQWtdSdldFaXY"

/*--- Variables ---*/
float temp[] = { 0, 0 };
float lum = 0;
FirebaseData firebaseData;
FirebaseJson json;

/*--- Functions ---*/
void connectWifi()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("Connecting");
        Serial.print(".");
        delay(1000);
    }

    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
}

float getAnalogVoltage(uint8_t pin, float vcc, int adcMaxValue)
{
    float inputValue = analogRead(pin);
    float voltage = vcc * inputValue / (adcMaxValue - 1);
    return voltage;
}

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(TEMP_00, INPUT);
    pinMode(TEMP_01, INPUT);
    pinMode(LUMINOS, INPUT);

    // Serial communication with terminal
    Serial.begin(115200);

    // WiFi settings
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    connectWifi();

    // RTDB settings
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    Firebase.setReadTimeout(firebaseData, 1000 * 60);
    Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

/*--- Loop ---*/
void loop()
{
    temp[0] = readNTC10K(TEMP_00, VCC, NTC_R1, ADC_MAX);
    temp[1] = readNTC10K(TEMP_01, VCC, NTC_R1, ADC_MAX);
    lum = getAnalogVoltage(LUMINOS, VCC, ADC_MAX);

    Serial.print("temp[0]: ");
    Serial.println(temp[0]);
    Serial.print("temp[1]: ");
    Serial.println(temp[1]);
    Serial.print("lum: ");
    Serial.println(lum);
    Serial.println();

    json.set("/temperature/temp_sensor_00", temp[0]);
    json.set("/temperature/temp_sensor_01", temp[1]);
    json.set("/luminosity", lum);
    Firebase.updateNode(firebaseData, "/iiot-test/subsys_00", json);

    // delay(1000);
}
