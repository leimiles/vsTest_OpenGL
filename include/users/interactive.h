#pragma once
#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <iostream>

class interactive
{
private:
    float energy;
    double interval;
    float turningAngle;
    float elevationAngle;
    float acceleration;
    /*
    void set_TurningAcceleration();
    */
    double lastFrameTime;
    unsigned int frameCount;
    double frameInterval;
public:
    double updating_X;
    double updating_Y;
    double cursorPos_X;
    double cursorPos_Y;
    float E;
    float T;
    float ET_Speed;
    unsigned int drawMode;
    double deltaTime;
    float zoom;
    float zoomSpeed;
    float targetHeight;
    float targetHeightSpeed;
    interactive();
    ~interactive();
    void reset();
    void set_DeltaTime(double time);
    void set_DrawMode();
    void set_ET(float pos_Current_X, float pos_Current_Y, float time);
    void set_ET(double time);
    void set_Acceleration();
    void set_Zoom(float offset);
    void show_FPS(double time);
    void set_TargetHeight(int direction);
    void fade_T(double time);
};


#endif