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
    cam* camera;
    mesh_NDC* screen_Mesh;
    shaderV2* shader_NDC;
    material* material_NDC;
    void init();
public:
    material* overide_Material;
    material* wireframe_Material;
    mrp(cam& camera);
    ~mrp();
    void clear_Buffer() const;
    void release_Resource();
    int get_MaxVertex_Attributes();
    void draw_Model(const model& mdl, bool isDepth_Test, unsigned int fill_Mode = 0);
    void draw_Mesh(const mesh* mesh, const material* material, bool isDepth_Test, glm::mat4 localToWorld) const;
    void draw_ScreenMesh() const;
    //void draw_Mesh(const mesh& mesh, std::vector<material*> materials, bool isDepth_Test, glm::mat4 localToWorld) const;
};

#endif
