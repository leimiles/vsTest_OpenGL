#include "users/interactive.h"


interactive::interactive()
{
    float turning_Energy = 0.0f;
    zoom = 3.0f;
    press_Start_Time = 0.0f;
    press_End_Time = 0.0f;
    elevationAngle = 90.0f;
    turningAngle = 0.0f;
    pos_Start_X = 0.0;
    pos_End_X = 0.0;
    pos_Start_Y = 0.0;
    pos_End_Y = 0.0;
    updating_X = 0.0f;
    interval = 0.0f;
}


float interactive::get_Druation()
{
    return press_End_Time - press_Start_Time;
}

float interactive::get_HorizontalOffset()
{
    return (float)(pos_End_X - pos_Start_X);
}

void interactive::set_TurningEnergy()
{
    float duration = get_Druation();
    if (duration == 0.0f) {
        turning_Energy = 0.0f;
    }
    else
    {
        turning_Energy = get_HorizontalOffset() / duration;
    }
    //std::cout << "energy: " << turning_Energy << std::endl;
}


void interactive::update_TurningAngle(float pos_Current_X, float time)
{

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
        }
        else
        {
            turningAngle -= offset;
        }
    }

}
