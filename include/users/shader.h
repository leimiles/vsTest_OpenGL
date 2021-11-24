#ifndef SHADER_H
#define SHADER_H

class shader
{
private:
    /* data */
    unsigned int ID;
public:
    static const char* test_VertexShader;
    static const char* test_VertexShader2;
    static const char* test_FragmentShader;
    static const char* test_FragmentShader2;
    shader(const char* vertexShader_Path, const char* fragmentShader_Path);
    ~shader();
};

#endif
