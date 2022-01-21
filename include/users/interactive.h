#pragma once
#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <iostream>
#define TARGET_FRAME_RATE 60

class interactive
{
private:
    float autoTurningEnergy;
    float acceleration;
    float updating_X;
    float updating_Y;
    float interval;
    float turningAngle;
    float elevationAngle;
    float get_TurningSpeed();
    void set_TurningAcceleration(float time);
    unsigned int frameCount;
    float previousTime;
    float second;
public:
    float zoom;
    float targetHeight;
    interactive();
    ~interactive();
    void set_AutoTurningEnergy();
    void set_BothAngles(float pos_Current_X, float pos_Current_Y, float time);
    float get_TurningAngle();
    float get_TurningAngle(float time);
    float get_ElevationAngle();
    void reset();
    int get_FPS(float time);
};


#endif