#ifndef SHADER_V2_H
#define SHADER_V2_H
#define VERTEX_SHADER_PATH_ROOT "resources/shaders/vertex/"
#define FRAGMENT_SHADER_PATH_ROOT "resources/shaders/fragment/"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "glad/glad.h"
#include "users/transform.h"

class shaderV2
{
private:
    /* data */
    unsigned int ID;
    static std::string shader_FileReader(const char* file_Name, bool isValidate, std::string shaderPathRoot);
    unsigned int current_VSO;
    unsigned int current_FSO;
    unsigned int current_Program;
public:
    std::string shader_Name;
    static std::string install_Path;
    shaderV2(const char* vertex_Shader_FileName, const char* fragment_Shader_FileName, bool isChecked, bool isValidated);
    shaderV2(std::string vertex_Shader_String, std::string fragment_Shader_String, bool isChecked);
    ~shaderV2();
    void check_ShaderCompileInfo(unsigned int shaderID);
    void check_ShaderLinkInfo(unsigned int programID);
    void delete_Program();
    void use_Program();
    void set_Float(const char* parameter_Name, float value);
    void set_Int(const char* parameter_Name, int value);
    void set_Matrix(const char* paramter_Name, glm::mat4 mat);
    unsigned int get_ParameterLocation(const char* parameter_Name);
    unsigned int get_ShaderProgram();
};

#endif
