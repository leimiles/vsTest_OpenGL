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
    std::vector<texture> textures;
    void set_Textures(unsigned int texture_Count, ...);
public:
    static std::vector<material*> current_Materials;
    material(shaderV2 shader_Program);
    ~material();
    void set_Matrix_MVP(glm::mat4& mvp) const;
    void set_Matrix_LocalToWorld(glm::mat4& localToWorld) const;
    void set_Matrix_WorldToView(glm::mat4& worldToView) const;
    void set_Matrix_Eye(glm::mat4& eye) const;
    void set_Matrix_ViewToPerspectiveProjection(glm::mat4& viewToPerspectiveProjection) const;
    void active() const;
    void set_Texture(const char* texture_ChannelName, texture& texture);
    void use_Textures() const;
    void release_Textures() const;
};

#endif