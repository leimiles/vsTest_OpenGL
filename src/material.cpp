#include "users/material.h"

unsigned int material::material_Count = 0;

material::material(shaderV2 shader_Program)
{
    shader = &shader_Program;
    material_Count++;
    material_ID = material_Count;
}

material::~material()
{
}

unsigned int material::get_Material_ID()
{
    return material_ID;
}

void material::active()
{
    shader->use_Program();
    //shader->set_Matrix("mvp", mvp);
}

void material::set_MVP(glm::mat4& mvp)
{
    shader->set_Matrix("mvp", mvp);
}