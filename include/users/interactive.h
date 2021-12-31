#pragma once
#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <iostream>

struct interactive
{
    float turning_Energy;
    float turningAngle_Offset;
public:
    float press_Start_Time;
    float press_End_Time;
    float zoom;
    float turningAngle;
    float elevationAngle;
    double pos_Start_X;
    double pos_End_X;
    double pos_Start_Y;
    double pos_End_Y;
    interactive();
    float get_Druation();
    float get_HorizontalOffset();
    void set_TurningEnergy();
    void print_MouseOffset(float pos_Current_X);
};


#endif