#ifndef MRP_H
#define MRP_H
#include <glad/glad.h>
#include <users/geometry.h>
#include <users/shader.h>
#include <cmath>

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
    void set_DrawMode(GLenum draw_Mode);
    int get_MaxVertex_Attributes();
    void draw_Shape();
};

#endif
