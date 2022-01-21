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
    frameCount = 0;
    previousTime = 0.0f;
    second = 1.0f;
    deltatime = 1.0f;
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
    turningAngle += get_TurningSpeed();
    return turningAngle;
}

float interactive::get_TurningAngle(float time)
{
    set_TurningAcceleration(time);
    return turningAngle += acceleration;
}

float interactive::get_TurningSpeed()
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
    return acceleration;
}

void interactive::set_TurningAcceleration(float time)
{
    // once time interval longer than 0.1 second
    if (time - previousTime > 0.001f)
    {
        if (acceleration > 0.01f)
        {
            acceleration -= 0.01f;
        }
        else if (acceleration < -0.01f)
        {
            acceleration += 0.01f;
        }
        else
        {
            acceleration = 0.0f;
        }

        previousTime = time;
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

int interactive::get_FPS(float time)
{
    frameCount++;
    if ((time - previousTime) > second)
    {
        std::cout << frameCount << std::endl;
        frameCount = 0;
        previousTime = time;
    }
    return 0;

}