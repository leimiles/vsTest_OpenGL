#pragma once
#ifndef DATA_H
#define DATA_H
#include "glm/glm.hpp"

class data
{
private:
    /* data */
public:
    static float quad_Example_Attributes[32];
    static unsigned int quad_Example_Indices[6];
    static float cube_Example_Attributes[180];
    static glm::vec3 some_Positions[10];
    data();
    ~data();
};

#endif