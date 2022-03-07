#pragma once
#ifndef DATA_H
#define DATA_H
#include "glm/glm.hpp"
#include <string>

class data
{
private:
    /* data */
public:
    static float help_Quad_Attributes[32];
    static unsigned int help_Quad_Indices[6];
    static float cube_Example_Attributes[180];
    static glm::vec3 some_Positions[10];
    static std::string shader_Chicken01_Vert;
    static std::string shader_Chicken01_Frag;
    static std::string shader_Preview_Vert;
    static std::string shader_Preview_Frag;
    data();
    ~data();
};

#endif