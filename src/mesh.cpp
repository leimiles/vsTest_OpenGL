#include "users/mesh.h"

mesh::mesh(std::vector<vertexAttri_Pattern_FBX> vertex_Attributes, std::vector<unsigned int> vertex_Elements)
{
    this->vertex_Attributes_FBX = vertex_Attributes;
    this->vertex_Elements = vertex_Elements;
    setup_Mesh_FBX();
    this->material = nullptr;
}

mesh::mesh(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size, unsigned int* elements)
{
    for (unsigned int i = 0; i < attributes_Size; i += stride)
    {
        vertexAttri_Pattern_Simple vertex_Attribute_Simple;
        vertex_Attribute_Simple.position_Obj.x = attributes[i];
        vertex_Attribute_Simple.position_Obj.y = attributes[i + 1];
        vertex_Attribute_Simple.position_Obj.z = attributes[i + 2];
        vertex_Attribute_Simple.normal_Obj.x = attributes[i + 3];
        vertex_Attribute_Simple.normal_Obj.y = attributes[i + 4];
        vertex_Attribute_Simple.normal_Obj.z = attributes[i + 5];
        vertex_Attribute_Simple.texcoords.x = attributes[i + 6];
        vertex_Attribute_Simple.texcoords.y = attributes[i + 7];
        vertex_Attributes_Simple.push_back(vertex_Attribute_Simple);
    }

    for (unsigned int i = 0; i < elements_Size; i++)
    {
        vertex_Elements.push_back(elements[i]);
    }

    setup_Mesh_Simple();
    this->material = nullptr;

    /*
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * attributes_Size, attributes, GL_STATIC_DRAW);

        if (elements_Size > 0) {
            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elements_Size, elements, GL_STATIC_DRAW);
        }

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(sizeof(float) * 3));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(sizeof(float) * 6));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    */
}

mesh::~mesh()
{
}

void mesh::setup_Mesh_FBX()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_Attributes_FBX.size() * sizeof(vertexAttri_Pattern_FBX), &vertex_Attributes_FBX[0], GL_STATIC_DRAW);

    if (vertex_Elements.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_Elements.size() * sizeof(unsigned int), &vertex_Elements[0], GL_STATIC_DRAW);
    }

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_FBX), (void*)0);
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_FBX), (void*)offsetof(vertexAttri_Pattern_FBX, normal_Obj));
    // texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_FBX), (void*)offsetof(vertexAttri_Pattern_FBX, texcoords));
    // tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_FBX), (void*)offsetof(vertexAttri_Pattern_FBX, tangent_Obj));
    // bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_FBX), (void*)offsetof(vertexAttri_Pattern_FBX, bitangent_Obj));
    // color
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_FBX), (void*)offsetof(vertexAttri_Pattern_FBX, color));
    // m_BoneIDs
    glEnableVertexAttribArray(6);
    glVertexAttribIPointer(6, 4, GL_INT, sizeof(vertexAttri_Pattern_FBX), (void*)offsetof(vertexAttri_Pattern_FBX, m_BoneIDs));
    // m_Weights
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_FBX), (void*)offsetof(vertexAttri_Pattern_FBX, m_Weights));

    // make it free
    glBindVertexArray(0);

}

void mesh::setup_Mesh_Simple()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_Attributes_Simple.size() * sizeof(vertexAttri_Pattern_Simple), &vertex_Attributes_Simple[0], GL_STATIC_DRAW);

    if (vertex_Elements.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_Elements.size() * sizeof(unsigned int), &vertex_Elements[0], GL_STATIC_DRAW);
    }

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_Simple), (void*)0);
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_Simple), (void*)offsetof(vertexAttri_Pattern_Simple, normal_Obj));
    // texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_Simple), (void*)offsetof(vertexAttri_Pattern_Simple, texcoords));

    // make it free
    glBindVertexArray(0);

}
