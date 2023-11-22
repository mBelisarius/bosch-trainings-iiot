/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

/*--- Hardware mapping ---*/
const uint8_t PIN_SENSOR = 26;

/*--- Constants ---*/
const float VREF = 3.3f;
const uint16_t ADC_MAX = (1 << 12) - 1;

const char WIFI_SSID[] = "WIFI_SSID";
const char WIFI_PASSWORD[] = "WIFI_PASSWORD";

const char FIREBASE_HOST[] = "https://<databaseName>.firebaseio.com";
const char FIREBASE_AUTH[] = "FIREBASE_AUTH";

/*--- Variables ---*/
uint16_t input_value = 0;
float voltage = 0.0f;

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

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(PIN_SENSOR, INPUT);

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
    input_value = analogRead(PIN_SENSOR);
    voltage = static_cast<float>(input_value) * VREF / static_cast<float>(ADC_MAX);

    Serial.println(voltage);

    bool status;

    // Send a single float value
    status = Firebase.setFloat(fbdo, "/iiot-test/sensor", voltage);

    // Send a JSON
    FirebaseJson json;
    json.set("/data", voltage);
    status = Firebase.updateNode(fbdo, "/iiot-test/sensor", json);

    if (!status) { Serial.println(fbdo.errorReason().c_str()); }

    delay(1000);
}
