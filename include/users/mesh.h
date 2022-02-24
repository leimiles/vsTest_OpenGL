#ifndef MESH_H
#define MESH_H
#define MAX_BONE_INFLUENCE 4
#include <vector>
#include "users/material.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct vertexAttri_Pattern_FBX
{
    glm::vec3 position_Obj;
    glm::vec3 normal_Obj;
    glm::vec2 texcoords;
    glm::vec3 tangent_Obj;
    glm::vec3 bitangent_Obj;
    glm::vec4 color;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct vertexAttri_Pattern_Simple
{
    glm::vec3 position_Obj;
    glm::vec3 normal_Obj;
    glm::vec2 texcoords;
};

class mesh
{
private:
    unsigned int vbo;        // vertex buffer object
    unsigned int ebo;        // vertex element object
    void setup_Mesh_FBX();
    void setup_Mesh_Simple();
public:
    std::string mesh_Name;
    unsigned int material_ID;
    glm::mat4 matrix_LocalToWorld;
    unsigned int vao;        // vertex attribute object
    material* material;
    std::vector<vertexAttri_Pattern_FBX> vertex_Attributes_FBX;
    std::vector<vertexAttri_Pattern_Simple> vertex_Attributes_Simple;
    std::vector<unsigned int> vertex_Elements;
    mesh(std::vector<vertexAttri_Pattern_FBX> vertex_Attributes, std::vector<unsigned int> vertex_Elements);
    mesh(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size = 0, unsigned int* elements = nullptr);
    ~mesh();
};

#endif