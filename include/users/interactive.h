#pragma once
#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <iostream>

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
    void set_TurningAcceleration();
    float deltaTime;
    float lastFrameTime;
public:
    float deltatime;
    float zoom;
    float targetHeight;
    interactive();
    ~interactive();
    void set_AutoTurningEnergy();
    void set_BothAngles(float pos_Current_X, float pos_Current_Y, float time);
    float get_TurningAngle();
    float get_ElevationAngle();
    void reset();
    float get_DeltaTime(float time);
};


#endif