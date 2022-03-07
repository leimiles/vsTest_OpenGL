#include "users/interactive.h"
#include <cmath>


interactive::interactive()
{
    zoom = 240.0f;
    elevationAngle = 90.0f;
    turningAngle = 0.0f;
    updating_X = 0.0;
    updating_Y = 0.0;
    interval = 0.0;
    energy = 0.0f;
    deltaTime = 1.0f;
    lastFrameTime = 0.0f;
    targetHeight = 80.0f;
    targetHeightSpeed = 2.0f;
    zoomSpeed = 30.0f;
    ET_Speed = 15.0f;
    draw_Mode = 1;
    draw_Mode_Press_Times = 0;
    //model_View_Mode = 0;
    //quad_View_Mode = 0;
    E = 90.0f;
    T = 0.0f;
    frameCount = 0;
    frameInterval = 0.0f;
    acceleration = 0.0f;
    cursorPos_X = 0.0;
    cursorPos_Y = 0.0;
}

interactive::~interactive()
{

}

void interactive::set_ET(double time)
{
    if (time - interval > deltaTime * 0.5)
    {
        acceleration = 0.0f;

        float offset_X = (float)(abs(updating_X - cursorPos_X)) * deltaTime * ET_Speed;
        if (updating_X > cursorPos_X)
        {
            T += offset_X;
            energy = offset_X;
        }
        else
        {
            T -= offset_X;
            energy = offset_X * -1.0f;
        }
        //std::cout << "energy set: " << energy << std::endl;

        float offset_Y = (float)(abs(updating_Y - cursorPos_Y)) * deltaTime * ET_Speed;
        if (updating_Y > cursorPos_Y)
        {
            //std::cout << "down" << std::endl;
            E += offset_Y;
            if (E > 179.9f)
            {
                E = 179.9f;
            }
        }
        else
        {
            //std::cout << "up" << std::endl;
            E -= offset_Y;
            if (E < 0.01f)
            {
                E = 0.01f;
            }
        }

        interval = time;
        updating_X = cursorPos_X;
        updating_Y = cursorPos_Y;
    }

}

void interactive::set_Acceleration()
{
    acceleration = energy;
}


void interactive::reset_View()
{
    zoom = 240.0f;
    E = 90.0f;
    T = 0.0f;
    targetHeight = 80.0f;
}

void interactive::set_DeltaTime(double time)
{
    deltaTime = time - lastFrameTime;
    lastFrameTime = time;
}

/*
void interactive::set_DrawMode(int mode)
{
    draw_Mode = mode;
    switch (draw_Mode)
    {
    case 1:
        model_View_Mode++;
        break;
    case 2:
        quad_View_Mode++;
        break;

    default:
        break;
    }
}
*/

void interactive::show_FPS(double time)
{
    frameCount++;
    if (time - frameInterval > 0.2f)
    {
        std::cout << "FPS: " << frameCount << std::endl;
        frameCount = 0;
        frameInterval = time;
    }
}

void interactive::set_Zoom(float offset)
{
    float intensity = zoom * 0.5;
    if (offset < 0)
    {
        zoom += zoomSpeed * deltaTime * intensity;
    }
    if (offset > 0)
    {
        zoom -= zoomSpeed * deltaTime * intensity;
    }
    if (zoom < 0)
    {
        zoom = 0.001f;
    }
}

short interactive::sign(double number)
{
    if (number > 0)
    {
        return 1;
    }
    else if (number < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void interactive::set_TargetHeightOffset(double time)
{
    short int direction;
    if (time - interval > deltaTime * 0.5)
    {
        direction = sign(cursorPos_Y - updating_Y);
        interval = time;
        updating_Y = cursorPos_Y;
    }
    targetHeight += direction * targetHeightSpeed * deltaTime * zoom;
}

void interactive::fade_T()
{
    T += acceleration * ET_Speed * deltaTime;

    if (acceleration > 0.1f)
    {
        acceleration -= 0.1f;
    }
    else if (acceleration < -0.1f)
    {
        acceleration += 0.1f;
    }
    else
    {
        acceleration = 0.0f;
    }

}
