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
    vao_Pos3,
    vao_Pos3_Col3_Texcoord2
};

// this is the render pipeline
class mrp
{
private:
    static unsigned int current_VAO;       // vertex attribute object
    static unsigned int current_VBO;
    static unsigned int current_EBO;
public:
    mrp(/* args */);
    ~mrp();
    void clear_ColorBuffer();
    void release_Resource();
    int get_MaxVertex_Attributes();
    void set_DrawMode(GLenum draw_Mode);
    void set_RenderingData_Element();
    void set_RenderingData_Element(vao_Mode mode, const geometry& geo);
    void draw_Geometry_Elements();
    void draw_Geometry_Elements(const geometry& geo);
    static void set_VAO_Pos3_Col3_Texcoord2();
};

#endif
