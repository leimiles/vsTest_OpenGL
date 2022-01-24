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
    float lastFrameTime;
public:
    float E;
    float T;
    float T_Speed;
    unsigned int drawMode;
    float deltaTime;
    float zoom;
    float zoomSpeed;
    float targetHeight;
    float targetHeightSpeed;
    interactive();
    ~interactive();
    void set_AutoTurningEnergy();
    void set_BothAngles(float pos_Current_X, float pos_Current_Y, float time);
    float get_TurningAngle();
    float get_ElevationAngle();
    void reset();
    void set_DeltaTime(float time);
    void set_DrawMode();
    void set_ET(float pos_Current_X, float pos_Current_Y, float time);
    void set_AutoT();
};


#endif