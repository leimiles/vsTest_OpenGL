#include "users/mesh.h"

mesh_FBX::mesh_FBX(std::vector<vertexAttri_Pattern_FBX> vertex_Attributes, std::vector<unsigned int> vertex_Elements)
{
    this->vertex_Attributes_FBX = vertex_Attributes;
    this->vertex_Elements = vertex_Elements;
    setup_Mesh();
    this->material = nullptr;
    this->matrix_LocalToWorld = transform::mat_Identity;
}

mesh_Simple::mesh_Simple(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size, unsigned int* elements)
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

    setup_Mesh();
    this->material = nullptr;
    this->matrix_LocalToWorld = transform::mat_Identity;

}

mesh_NDC::mesh_NDC(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size, unsigned int* elements)
{
    for (unsigned int i = 0; i < attributes_Size; i += stride)
    {
        vertexAttri_Pattern_NDC vertex_Attribute_NDC;
        vertex_Attribute_NDC.position_NDC.x = attributes[i];
        vertex_Attribute_NDC.position_NDC.y = attributes[i + 1];
        vertex_Attribute_NDC.position_NDC.z = attributes[i + 2];
        vertex_Attribute_NDC.color.x = attributes[i + 3];
        vertex_Attribute_NDC.color.y = attributes[i + 4];
        vertex_Attribute_NDC.color.z = attributes[i + 5];
        vertex_Attributes_NDC.push_back(vertex_Attribute_NDC);
    }

    for (unsigned int i = 0; i < elements_Size; i++)
    {
        vertex_Elements.push_back(elements[i]);
    }

    setup_Mesh();
    this->material = nullptr;
    this->matrix_LocalToWorld = transform::mat_Identity;
}

mesh::mesh()
{
}
mesh::~mesh()
{
}
mesh_Simple::~mesh_Simple()
{
}
mesh_FBX::~mesh_FBX()
{
}
mesh_NDC::~mesh_NDC()
{

}

void mesh_FBX::setup_Mesh()
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

void mesh_Simple::setup_Mesh()
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

void mesh_NDC::setup_Mesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_Attributes_NDC.size() * sizeof(vertexAttri_Pattern_NDC), &vertex_Attributes_NDC[0], GL_STATIC_DRAW);

    if (vertex_Elements.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_Elements.size() * sizeof(unsigned int), &vertex_Elements[0], GL_STATIC_DRAW);
    }

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_NDC), (void*)0);
    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexAttri_Pattern_NDC), (void*)offsetof(vertexAttri_Pattern_NDC, color));

    // make it free
    glBindVertexArray(0);
}