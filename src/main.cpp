/**
 * @file main.cpp
 * @author Elvandry Ghiffary (elvandry13@gmail.com)
 * @brief Gate Alarm
 * @version 0.1
 * @date 2020-04-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <Arduino.h>
#include "encoder.h"

#define ALARM 7 // Alarm pin on D7
#define SW 4 // Button pin on D4

unsigned long lastButtonPress = 0;

void setup()
{
    // Serial communication for debugging purposes
    Serial.begin(115200);

    // Rotary encoder setup
    encoder_setup();

    // Alarm pin set as output
    pinMode(ALARM, OUTPUT);
    digitalWrite(ALARM, LOW);

    // Button pin set as input
    pinMode(SW, INPUT_PULLUP);
}

void loop()
{
    // Gate movement
    int gate_mv = encoder_pulse();
    Serial.println(gate_mv);

    // Turn ON alarm if gate opened
    if (gate_mv > 20 || gate_mv < -20)
    {
        Serial.println("OPEN");
        digitalWrite(ALARM, HIGH);
    }
    else
    {
        // Read the button state
        int btnState = digitalRead(SW);

        //If we detect LOW signal, button is pressed
        if (btnState == LOW)
        {
            // Turn OFF alarm if button pressed
            if (millis() - lastButtonPress > 50)
            {
                Serial.println("Turn OFF Alarm");
                digitalWrite(ALARM, LOW);
            }

            // Remember last button press event
            lastButtonPress = millis();
        }
    }
}
