#include "users/material.h"

std::vector<material*> material::current_Materials;

material::material(shaderV2 shader_Program)
{
    shader = &shader_Program;
    current_Materials.push_back(this);
}

material::~material()
{
}

void material::active() const
{
    shader->use_Program();
    //shader->set_Matrix("mvp", mvp);
}

void material::set_MVP(glm::mat4& mvp) const
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

void material::set_Texture(const char* texture_ChannelName, texture& texture)
{
    texture.texture_ChannelName = texture_ChannelName;
    textures.push_back(texture);
}

void material::use_Textures() const
{
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].get_TXO());
        shader->set_Int(textures[i].texture_ChannelName.c_str(), i);
    }
}

void material::release_Textures() const
{
    //std::cout << textures.size() << " textures set" << std::endl;
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

