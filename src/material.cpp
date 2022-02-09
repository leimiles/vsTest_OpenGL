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

void material::set_Textures(unsigned int texture_Count, ...)
{
    va_list texture_Pointer;
    va_start(texture_Pointer, texture_Count);
    for (int i = 0; i < texture_Count; i++) {
        /*
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, va_arg(texture_Pointer, texture).get_TXO());
        */
        textures.push_back(va_arg(texture_Pointer, texture));
    }
    va_end(texture_Pointer);
}

void material::use_Textures()
{
    //std::cout << textures.size() << " textures set" << std::endl;
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].get_TXO());
    }
}

void material::release_Textures()
{
    //std::cout << textures.size() << " textures set" << std::endl;
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

