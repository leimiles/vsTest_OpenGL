#include "users/mrp.h"

// init static members
unsigned int mrp::current_VAO;
unsigned int mrp::current_VBO;
unsigned int mrp::current_EBO;

mrp::mrp(/* args */)
{
}

mrp::~mrp()
{
}

// set(clear) color buffer with specified color
void mrp::clear_ColorBuffer()
{
    // set clear color  value
    glClearColor(0.12f, 0.35f, 0.3f, 1.0f);
    // clear color buffer with the set of clear color
    glClear(GL_COLOR_BUFFER_BIT);
}

// release everything
void mrp::release_Resource()
{
    glDeleteVertexArrays(1, &mrp::current_VAO);
    glDeleteBuffers(1, &mrp::current_VBO);
    glDeleteBuffers(1, &mrp::current_EBO);
    shader::delete_Program();
}

// set draw mode
void mrp::set_DrawMode(GLenum draw_Mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, draw_Mode);
}

// get max supported attribute
int mrp::get_MaxVertex_Attributes()
{
    int numberOfAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);
    return numberOfAttributes;
}

void mrp::set_RenderingData()
{
    // bind vao
    glGenVertexArrays(1, &mrp::current_VAO);
    glBindVertexArray(mrp::current_VAO);

    // bind vbo
    glGenBuffers(1, &mrp::current_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mrp::current_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry::quad_Example_Attributes), geometry::quad_Example_Attributes, GL_STATIC_DRAW);

    // bind ebo
    glGenBuffers(1, &mrp::current_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mrp::current_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(geometry::quad_Example_Indices), geometry::quad_Example_Indices, GL_STATIC_DRAW);

    // configure vao
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    // vao bound is no longer needed
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mrp::draw_Geometry_Elements()
{
    glBindVertexArray(mrp::current_VAO);
    glDrawElements(GL_TRIANGLES, sizeof(geometry::quad_Example_Indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

void mrp::draw_Geometry_Elements(texture& tex)
{
    glBindTexture(GL_TEXTURE_2D, tex.TXO);
    glBindVertexArray(mrp::current_VAO);
    glDrawElements(GL_TRIANGLES, sizeof(geometry::quad_Example_Indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}