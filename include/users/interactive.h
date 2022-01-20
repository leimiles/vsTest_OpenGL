#pragma once
#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <iostream>

class interactive
{
    float autoTurningEnergy;
    float acceleration;
    float updating_X;
    float updating_Y;
    float interval;
    float turningAngle;
    float elevationAngle;
    float get_TurningSpeed();
public:
    float zoom;
    float targetHeight;
    interactive();
    ~interactive();
    void set_AutoTurningEnergy();
    void set_BothAngles(float pos_Current_X, float pos_Current_Y, float time);
    float get_TurningAngle();
    float get_ElevationAngle();
};


#endif