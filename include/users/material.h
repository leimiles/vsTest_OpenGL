#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector>
#include <string>
#include "users/shaderV2.h"
#include "users/texture.h"

class material
{
private:
    static unsigned int material_Count;
    unsigned int material_ID;
    shaderV2* shader;
    std::vector<texture> textures;
    void set_Textures(unsigned int texture_Count, ...);
public:
    material(shaderV2 shader_Program);
    ~material();
    void set_MVP(glm::mat4& mvp);
    unsigned int get_Material_ID();
    void active();
    void set_Texture(const char* texture_ChannelName, texture& texture);
    void use_Textures();
    void release_Textures();
};

#endif