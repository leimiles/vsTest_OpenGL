#ifndef MRP_H
#define MRP_H
#include <cmath>
#include "users/geometry.h"
#include "users/shader.h"
#include "users/texture.h"
#include "glad/glad.h"

// this is the render pipeline
class mrp
{
private:
    static unsigned int current_VAO;       // vertex attribute object
    static unsigned int current_VBO;
    static unsigned int current_EBO;
public:
    mrp(/* args */);
    ~mrp();
    void clear_ColorBuffer();
    void release_Resource();
    int get_MaxVertex_Attributes();
    void set_DrawMode(GLenum draw_Mode);
    void set_RenderingData();
    void draw_Geometry_Elements();
};

#endif
