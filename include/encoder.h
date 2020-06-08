/**
 * @file encoder.h
 * @author Elvandry Ghiffary (elvandry13@gmail.com)
 * @brief encoder.cpp header file
 * @version 0.1
 * @date 2020-06-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <Arduino.h>
#define outputA 2 // CLK pin on D2
#define outputB 3 // DT pin on D3

/**
 * @brief Rotary Encoder Setup Pin
 * 
 */
void encoder_setup();

/**
 * @brief Total of pulse generated, increased when CW, decreased when CCW
 * 
 * @return int 
 */
int encoder_pulse();
