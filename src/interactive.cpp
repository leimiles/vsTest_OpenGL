#include "users/interactive.h"


interactive::interactive()
{
    zoom = 3.0f;
    elevationAngle = 90.0f;
    turningAngle = 0.0f;
    updating_X = 0.0f;
    interval = 0.0f;
    autoTurningEnergy = 0.0f;
    acceleration = 0.0f;
}

interactive::~interactive()
{

}

void interactive::update_TurningAngle(float pos_Current_X, float time)
{
    acceleration = 0.0f;

    if (time - interval > 0.05f) {
        interval = time;
        updating_X = pos_Current_X;
    }
    if (updating_X != pos_Current_X)
    {
        float offset = abs(updating_X - pos_Current_X) * 0.5f;
        if (updating_X > pos_Current_X)
        {
            turningAngle += offset;
            autoTurningEnergy = offset;
        }
        else
        {
            turningAngle -= offset;
            autoTurningEnergy = offset * -1.0f;
        }

    }

}

void interactive::set_AutoTurningEnergy()
{
    acceleration = autoTurningEnergy * 0.1f;
    //std::cout << "autoTurningEnergy:" << autoTurningEnergy << " | " << "acceleration: " << acceleration << std::endl;
}

float interactive::get_TurningAngle()
{
    turningAngle += get_TurningSpeed();
}

float interactive::get_TurningSpeed()
{

    if (acceleration > 0.1f)
    {
        acceleration -= 0.1f;
        //std::cout << "turning left" << std::endl;
    }
    else if (acceleration < -0.1f)
    {
        acceleration += 0.1f;
        //std::cout << "turning right" << std::endl;
    }
    else
    {
        acceleration = 0.0f;
        //std::cout << "stop" << std::endl;
    }

    return acceleration;

}
