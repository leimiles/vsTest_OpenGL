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

void mrp::draw_Shape()
{

}