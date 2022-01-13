#pragma once
#ifndef SHADER_H
#define SHADER_H
#define VERTEX_SHADER_PATH_ROOT "./resources/shaders/vertex/"
#define FRAGMENT_SHADER_PATH_ROOT "./resources/shaders/fragment/"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "glad/glad.h"
#include "users/transform.h"

class shader
{
private:
    /* data */
    unsigned int ID;
    static std::string shader_FileReader(const char* file_Name, bool isValidate, std::string shaderPathRoot);
    static unsigned int current_VSO;
    static unsigned int current_FSO;
    static unsigned int current_Program;
public:
    shader(const char* vertex_Shader_FileName, const char* fragment_Shader_FileName, bool isChecked, bool isValidated);
    ~shader();
    static void check_ShaderCompileInfo(unsigned int shaderID);
    static void check_ShaderLinkInfo(unsigned int programID);
    static void delete_Program();
    static void use_Program();
    static void set_Float(const char* parameter_Name, float value);
    static void set_Int(const char* parameter_Name, int value);
    static void set_Matrix(const char* paramter_Name, glm::mat4 mat);
    static int get_ParameterLocation(const char* parameter_Name);
};

#endif
