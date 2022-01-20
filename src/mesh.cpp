#include "users/mesh.h"

mesh::mesh(std::vector<vertexAttri_Pattern> vertex_Attributes, std::vector<unsigned int> vertex_Elements)
{
    this->vertex_Attributes = vertex_Attributes;
    this->vertex_Elements = vertex_Elements;
    setup_Mesh();
}

mesh::~mesh()
{
}

void mesh::setup_Mesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_Attributes.size() * sizeof(vertexAttri_Pattern), &vertex_Attributes[0], GL_STATIC_DRAW);

    if (vertex_Elements.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_Elements.size() * sizeof(unsigned int), &vertex_Elements[0], GL_STATIC_DRAW);
    }

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern), (void*)0);
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern), (void*)offsetof(vertexAttri_Pattern, normal_Obj));
    // texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern), (void*)offsetof(vertexAttri_Pattern, texcoords));
    // tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern), (void*)offsetof(vertexAttri_Pattern, tangent_Obj));
    // bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern), (void*)offsetof(vertexAttri_Pattern, bitangent_Obj));
    // color
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern), (void*)offsetof(vertexAttri_Pattern, color));
    // m_BoneIDs
    glEnableVertexAttribArray(6);
    glVertexAttribIPointer(6, 4, GL_INT, sizeof(vertexAttri_Pattern), (void*)offsetof(vertexAttri_Pattern, m_BoneIDs));
    // m_Weights
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern), (void*)offsetof(vertexAttri_Pattern, m_Weights));

    // make it free
    glBindVertexArray(0);

}

