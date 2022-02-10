#pragma once
#ifndef MRP_H
#define MRP_H
#include <cmath>
#include "users/model.h"
#include "users/geometry.h"
#include "users/shaderV2.h"
#include "users/texture.h"
#include "users/cam.h"
#include "users/data.h"

enum vao_Mode {
    vao_0Pos3,
    vao_0Pos3_1Col3_2Texcoord2,
    vao_0Pos3_2Texcoord2,
    vao_0Pos3_1Normal3_2Texcoord2
};

// this is the render pipeline
class mrp
{
private:
    static unsigned int current_VAO;        // vertex attribute object
    static unsigned int current_VBO;        // vertex buffer object
    static unsigned int current_EBO;        // vertex element object
    cam* camera;
    unsigned int drawMode;
public:
    mrp(cam& camera);
    ~mrp();
    glm::mat4 mvp;
    void clear_Buffer();
    void release_Resource();
    int get_MaxVertex_Attributes();
    void set_DrawMode(GLenum draw_Mode);
    void set_RenderingData(vao_Mode mode, const geometry& geo);
    void set_RenderingData(const model& mdl);
    void draw_Geometry(const geometry& geo, bool isDepth_Test);
    void draw_Model(const model& mdl, bool isDepth_Test);
    void draw_Model_WithMaterial(const model& mdl, bool isDepth_Test);
    static void set_VAO_0Pos3_1Col3_2Texcoord2(const geometry& geo);
    static void set_VAO_0Pos3_2Texcoord2(const geometry& geo);
    static void set_VAO_0Pos3_1Normal3_2Texcoord2(const geometry& geo);
};

#endif
