#pragma once
#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <iostream>

class interactive
{
    float autoTurningEnergy;
    float acceleration;
    float updating_X;
    float interval;
    float turningAngle;
    float get_TurningSpeed();
public:
    float zoom;
    float elevationAngle;
    interactive();
    ~interactive();
    void update_TurningAngle(float pos_Current_X, float time);
    float get_TurningAngle();
    void set_AutoTurningEnergy();
};


#endif