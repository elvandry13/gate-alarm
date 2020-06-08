/**
 * @file encoder.cpp
 * @author Elvandry Ghiffary (elvandry13@gmail.com)
 * @brief Read the encoder pulses
 * @version 0.1
 * @date 2020-06-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "encoder.h"

int degree, counter = 0;
int aState, aLastState;

void encoder_setup()
{
    pinMode(outputA, INPUT);
    pinMode(outputB, INPUT);

    // Reads the initial state of the outputA
    aLastState = digitalRead(outputA);
}

int encoder_pulse()
{
    aState = digitalRead(outputA); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState != aLastState)
    {
        // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
        if (digitalRead(outputB) != aState)
        {
            counter++;
        }
        else
        {
            counter--;
        }
    }
    aLastState = aState; // Updates the previous state of the outputA with the current state
    return counter;
}
