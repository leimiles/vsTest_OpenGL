#pragma once
#ifndef MRP_H
#define MRP_H
#include <cmath>
#include "users/model.h"
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
    int model_View_Mode;
    int quad_View_Mode;
public:
    mrp(cam& camera);
    ~mrp();
    glm::mat4 mvp;
    void clear_Buffer();
    void release_Resource();
    int get_MaxVertex_Attributes();
    void set_Draw_Mode(unsigned int draw_Mode);
    void set_Model_View_Mode(unsigned int mode);
    void set_Quad_View_Mode(unsigned int mode);
    void draw_Model_WithMaterial(const model& mdl, bool isDepth_Test);
    void draw_Mesh(const mesh& mesh, const material* material, bool isDepth_Test, glm::mat4 localToWorld) const;
    void draw_Mesh(const mesh& mesh, std::vector<material*> materials, bool isDepth_Test, glm::mat4 localToWorld) const;
};

#endif
