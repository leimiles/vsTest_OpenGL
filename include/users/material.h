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
public:
    material(shaderV2 shader_Program);
    ~material();
    void set_MVP(glm::mat4& mvp);
    unsigned int get_Material_ID();
    void active();
};

#endif