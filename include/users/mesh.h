#ifndef MESH_H
#define MESH_H
#define MAX_BONE_INFLUENCE 4
#include <vector>
#include "users/material.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct vertexAttri_Pattern
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


class mesh
{
private:
    unsigned int vbo;        // vertex buffer object
    unsigned int ebo;        // vertex element object
    void setup_Mesh();
public:
    unsigned int vao;        // vertex attribute object
    std::vector<vertexAttri_Pattern> vertex_Attributes;
    std::vector<unsigned int> vertex_Elements;
    mesh(std::vector<vertexAttri_Pattern> vertex_Attributes, std::vector<unsigned int> vertex_Elements);
    mesh(std::vector<vertexAttri_Pattern> vertex_Attributes, std::vector<unsigned int> vertex_Elements, material material);
    ~mesh();
};

#endif