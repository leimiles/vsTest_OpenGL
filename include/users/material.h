#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector>
#include <string>
#include "users/shaderV2.h"
#include "users/texture.h"

class material
{
private:
    shaderV2* shader;
    void set_Textures(unsigned int texture_Count, ...);
public:
    unsigned int id;
    std::vector<texture*> textures;
    std::string material_Name;
    material(shaderV2& shader_Program);
    ~material();
    void set_Vector4(const char* vec4_VariableName, float x, float y, float z, float w) const;
    void set_Matrix_MVP(glm::mat4& mvp) const;
    void set_Matrix_LocalToWorld(glm::mat4& localToWorld) const;
    void set_Matrix_WorldToView(glm::mat4& worldToView) const;
    void set_Matrix_Eye(glm::mat4& eye) const;
    void set_Matrix_ViewToPerspectiveProjection(glm::mat4& viewToPerspectiveProjection) const;
    void active() const;
    void set_Texture(const char* texture_VariableName, texture& texture);
    void use_Textures() const;
    void release_Textures() const;
};

#endif