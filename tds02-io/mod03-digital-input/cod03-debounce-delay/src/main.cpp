/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware  ---*/
const uint8_t BUTTON = 13;
const uint8_t LED = 26;

/*--- Constants ---*/
const uint32_t DEBOUNCE = 50;

/*--- Variables ---*/
bool button_state = false;
bool last_button_state = false;
bool led_state = false;

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(BUTTON, INPUT);
    pinMode(LED, OUTPUT);
}

/*--- Loop ---*/
void loop()
{
    last_button_state = button_state;
    button_state = digitalRead(BUTTON);

    if (button_state == HIGH && last_button_state == LOW)
    {
        led_state = !led_state;
        digitalWrite(LED, led_state);
    }

    delay(DEBOUNCE);
}
