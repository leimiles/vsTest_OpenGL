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

    std::cout << "energy: " << turning_Energy << std::endl;
}

void interactive::print_MouseOffset(float pos_Current_X)
{
    //std::cout << "current mouse: " << pos_Current_X << " | " << "start mouse: " << pos_Start_X << std::endl;
    std::cout << "mouse_Offset_X: " << pos_Current_X - pos_Start_X << std::endl;
    turningAngle = (pos_Current_X - pos_Start_X) * -1.0f;
}