#include "users/material.h"

material::material(shaderV2& shader_Program)
{
    shader = &shader_Program;
    this->material_Name = "";
    this->id = -1;
}

material::~material()
{
}

void material::active() const
{
    shader->use_Program();
}

void material::set_Matrix_MVP(glm::mat4& mvp) const
{
    shader->set_Matrix("matrix_MVP", mvp);
}

void material::set_Matrix_LocalToWorld(glm::mat4& localToWorld) const
{
    shader->set_Matrix("matrix_LocalToWorld", localToWorld);
}

void material::set_Matrix_WorldToView(glm::mat4& worldToView) const
{
    shader->set_Matrix("matrix_WorldToView", worldToView);
}

void material::set_Matrix_ViewToPerspectiveProjection(glm::mat4& viewToPerspectiveProjection) const
{
    shader->set_Matrix("matrix_ViewToPerspectiveProjection", viewToPerspectiveProjection);
}

void material::set_Matrix_Eye(glm::mat4& eye) const
{
    shader->set_Matrix("matrix_Eye", eye);
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
        textures.push_back(va_arg(texture_Pointer, texture*));
    }
    va_end(texture_Pointer);
}

void material::set_Texture(const char* texture_VariableName, texture& texture)
{
    texture.texture_VariableName = texture_VariableName;
    textures.push_back(&texture);
}

unsigned int material::get_TexturesCount()
{
    return this->textures.size();
}

void material::use_Textures() const
{
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]->get_TXO());
        shader->set_Int(textures[i]->texture_VariableName.c_str(), i);
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

