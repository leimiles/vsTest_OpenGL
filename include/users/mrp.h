#pragma once
#ifndef MRP_H
#define MRP_H
#include <cmath>
#include "users/geometry.h"
#include "users/shader.h"
#include "users/texture.h"
#include "users/cam.h"
#include "users/data.h"
#include "glad/glad.h"

enum vao_Mode {
    vao_0Pos3,
    vao_0Pos3_1Col3_2Texcoord2,
    vao_0Pos3_2Texcoord2
};

// this is the render pipeline
class mrp
{
private:
    static unsigned int current_VAO;        // vertex attribute object
    static unsigned int current_VBO;        // vertex buffer object
    static unsigned int current_EBO;        // vertex element object
public:
    mrp(/* args */);
    ~mrp();
    void clear_Buffer();
    void release_Resource();
    int get_MaxVertex_Attributes();
    void set_DrawMode(GLenum draw_Mode);
    void set_RenderingData(vao_Mode mode, const geometry& geo);
    void draw_Geometry(const geometry& geo, bool isDepth_Test);
    static void set_VAO_0Pos3_1Col3_2Texcoord2(const geometry& geo);
    static void set_VAO_0Pos3_2Texcoord2(const geometry& geo);
};

#endif
