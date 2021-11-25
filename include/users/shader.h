#ifndef SHADER_H
#define SHADER_H
#define SHADER_PATH_ROOT "./src/shaders/"

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class shader
{
private:
    /* data */
    unsigned int ID;
    static std::string shader_FileReader(const char* file_Name, bool isValidate);
    static unsigned int current_VSO;
    static unsigned int current_FSO;
    static unsigned int current_Program;
public:
    shader(const char* vertex_Shader_FileName, const char* fragment_Shader_FileName, bool isChecked, bool isValidated);
    ~shader();
    static const char* test_VertexShader;
    static const char* test_VertexShader2;
    static const char* test_FragmentShader;
    static const char* test_FragmentShader2;
    static void check_ShaderCompileInfo(unsigned int shaderID);
    static void check_ShaderLinkInfo(unsigned int programID);
    static void delete_Program();
};

#endif
