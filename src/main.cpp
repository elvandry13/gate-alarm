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
#include "AntaresESP8266HTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "smart-gate"
#define deviceGateState "gate-state"
#define deviceSwitchStatus "switch-status"

#define ALARM D7 // Alarm pin on D7
#define SW D4 // Button pin on D4

AntaresESP8266HTTP antares(ACCESSKEY);

unsigned long lastDelay = 0;
unsigned long lastButtonPress = 0;
String gateState;
bool currentState = false;
bool lastState = false;

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

    // Antares connection setup
    antares.setDebug(true);
    antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop()
{
    // Gate movement
    int gate_mv = encoder_pulse();
    Serial.println(gate_mv);

    if (gate_mv > 20 || gate_mv < -20)
    {
        Serial.println("OPEN");
        gateState = "open";
        currentState = true;
    }
    else
    {
        Serial.println("CLOSED");
        gateState = "closed";
        currentState = false;
    }

    // Send data when gate state changed
    if (currentState != lastState)
    {
        // Send data to Antares
        antares.add("gateState", gateState);
        antares.send(projectName, deviceGateState);
        lastState = currentState;
    }

    // Get switch status from Antares
    antares.get(projectName, deviceSwitchStatus);
    if (antares.getSuccess())
    {
        int status = antares.getInt("status");

        // Alarm ON only when status = 1 and gate open
        if (status == 1 && gateState == "open")
        {
            digitalWrite(ALARM, HIGH);
        }

        // Alarm OFF when status = 0
        else if (status == 0)
        {
            digitalWrite(ALARM, LOW);
        }
    }

    // Turn OFF Alarm using shaft button
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

    while (millis() < lastDelay + 1000*5)
    {
        // Delay 5 seconds
    }
    // Remember last delay
    lastDelay = millis();
}
