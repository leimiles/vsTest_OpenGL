#include "users/interactive.h"


interactive::interactive()
{
    zoom = 240.0f;
    elevationAngle = 90.0f;
    turningAngle = 0.0f;
    updating_X = 0.0f;
    updating_Y = 0.0f;
    interval = 0.0f;
    autoTurningEnergy = 0.0f;
    acceleration = 0.0f;
    targetHeight = 80.0f;
    deltaTime = 1.0f;
    lastFrameTime = 0.0f;
    targetHeightSpeed = 10.0f;
}

interactive::~interactive()
{

}

void interactive::set_BothAngles(float pos_Current_X, float pos_Current_Y, float time)
{
    acceleration = 0.0f;
    if (time - interval > 0.05f) {
        interval = time;
        updating_X = pos_Current_X;
        updating_Y = pos_Current_Y;
    }
    if (updating_X != pos_Current_X)
    {
        float offset_X = abs(updating_X - pos_Current_X) * 0.5f;
        if (updating_X > pos_Current_X)
        {
            turningAngle += offset_X;
            autoTurningEnergy = offset_X;
        }
        else
        {
            turningAngle -= offset_X;
            autoTurningEnergy = offset_X * -1.0f;
        }
    }
    if (updating_Y != pos_Current_Y)
    {
        float offset_Y = abs(updating_Y - pos_Current_Y) * 0.25f;
        if (updating_Y > pos_Current_Y)
        {
            //std::cout << "down" << std::endl;
            elevationAngle += offset_Y;
            if (elevationAngle > 179.9f)
            {
                elevationAngle = 179.9f;
            }
        }
        else
        {
            //std::cout << "up" << std::endl;
            elevationAngle -= offset_Y;
            if (elevationAngle < 0.01f)
            {
                elevationAngle = 0.01f;
            }
        }
    }
}

void interactive::set_AutoTurningEnergy()
{
    acceleration = autoTurningEnergy * 0.05f;
    //std::cout << "autoTurningEnergy:" << autoTurningEnergy << " | " << "acceleration: " << acceleration << std::endl;
}

float interactive::get_TurningAngle()
{
    set_TurningAcceleration();
    return turningAngle += acceleration;
}

void interactive::set_TurningAcceleration()
{

    if (acceleration > 0.01f)
    {
        acceleration -= 0.01f;
        //std::cout << "turning left" << std::endl;
    }
    else if (acceleration < -0.01f)
    {
        acceleration += 0.01f;
        //std::cout << "turning right" << std::endl;
    }
    else
    {
        acceleration = 0.0f;
        //std::cout << "stop" << std::endl;
    }
}

float interactive::get_ElevationAngle()
{
    return elevationAngle;
}

void interactive::reset()
{
    zoom = 240.0f;
    elevationAngle = 90.0f;
    turningAngle = 0.0f;
    targetHeight = 80.0f;
}

void interactive::set_DeltaTime(float time)
{
    deltaTime = time - lastFrameTime;
    lastFrameTime = time;
}
