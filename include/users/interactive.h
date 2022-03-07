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
    double lastFrameTime;
    unsigned int frameCount;
    double frameInterval;
    short sign(double number);
public:
    double updating_X;
    double updating_Y;
    double cursorPos_X;
    double cursorPos_Y;
    float E;
    float T;
    float ET_Speed;
    int draw_Mode;
    int draw_Mode_Press_Times;
    //int model_View_Mode;
    //int quad_View_Mode;
    double deltaTime;
    float zoom;
    float zoomSpeed;
    float targetHeight;
    float targetHeightSpeed;
    interactive();
    ~interactive();
    void reset_View();
    void set_DeltaTime(double time);
    //void set_DrawMode(int mode);
    void set_ET(double time);
    void set_Acceleration();
    void set_Zoom(float offset);
    void show_FPS(double time);
    void set_TargetHeightOffset(double time);
    void fade_T();
};


#endif