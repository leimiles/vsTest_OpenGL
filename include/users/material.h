#ifndef MATERIAL_H
#define MATERIAL_H
#include <vector>
#include <string>
#include "users/shader.h"
#include "users/texture.h"

class material
{
private:
public:
    material(shader shader_Program);
    ~material();
};

#endif