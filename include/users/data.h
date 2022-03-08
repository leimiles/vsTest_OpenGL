#pragma once
#ifndef DATA_H
#define DATA_H
#include "glm/glm.hpp"
#include <string>

struct data
{
    static float help_SplitLine_Attributes[24];
    static unsigned int help_SplitLine_Indices[6];

    static float help_Quad_Attributes[32];
    static unsigned int help_Quad_Indices[6];

    static float cube_Example_Attributes[180];

    static glm::vec3 some_Positions[10];

    static std::string shader_Chicken01_Vert;
    static std::string shader_Chicken01_Frag;

    static std::string shader_Wireframe_Vert;
    static std::string shader_Wireframe_Frag;

    static std::string shader_NDC_Vert;
    static std::string shader_NDC_Frag;
};

#endif