/*---------------------------------------------------------------------------*\

    E ngineering | Bosch ETS: Engineering Technical School
    T echnical   | IIoT Training: Industrial Internet of Things
    S chool      | Powertrain Solutions @ Bosch Brazil

\*---------------------------------------------------------------------------*/

/*--- Includes ---*/
#include <Arduino.h>

/*--- Hardware mapping ---*/
const uint8_t OUTPUT1 = 32;
const uint8_t OUTPUT2 = 33;
const uint8_t OUTPUT3 = 25;
const uint8_t OUTPUT4 = 26;

/*--- Constants ---*/
const uint32_t DELAY_TIME = 1000;

/*--- Functions ---*/
void usingModulo()
{
    for (uint8_t i = 0; i < 16; i++)
    {
        digitalWrite(OUTPUT1, (i % 2 > 0));
        digitalWrite(OUTPUT2, (i % 4 > i % 2));
        digitalWrite(OUTPUT3, (i % 8 > i % 4));
        digitalWrite(OUTPUT4, (i % 16 > i % 8));

        delay(DELAY_TIME);
    }
}

void usingBitWise()
{
    for (uint8_t i = 0; i < 16; i++)
    {
        digitalWrite(OUTPUT1, (i & 0b0001));
        digitalWrite(OUTPUT2, (i & 0b0010));
        digitalWrite(OUTPUT3, (i & 0b0100));
        digitalWrite(OUTPUT4, (i & 0b1000));

        delay(DELAY_TIME);
    }
}

void usingBitRead()
{
    for (uint8_t i = 0; i < 16; i++)
    {
        digitalWrite(OUTPUT1, (bitRead(i, 0)));
        digitalWrite(OUTPUT2, (bitRead(i, 1)));
        digitalWrite(OUTPUT3, (bitRead(i, 2)));
        digitalWrite(OUTPUT4, (bitRead(i, 3)));

        delay(DELAY_TIME);
    }
}

/*--- Setup ---*/
void setup()
{
    // Hardware mapping
    pinMode(OUTPUT1, OUTPUT);
    pinMode(OUTPUT2, OUTPUT);
    pinMode(OUTPUT3, OUTPUT);
    pinMode(OUTPUT4, OUTPUT);
}

/*--- Loop ---*/
void loop()
{
    // usingModulo();
    // usingBitWise();
    usingBitWise();
}
