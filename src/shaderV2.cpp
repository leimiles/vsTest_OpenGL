#include "users\shaderV2.h"

std::string shaderV2::install_Path = "";

shaderV2::shaderV2(const char* vertex_Shader_FileName, const char* fragment_Shader_FileName, bool isChecked, bool isValidated, std::string shader_Name)
{
    this->shader_Name = shader_Name;
    // read and compile vertex shader
    std::string vertex_Shader_String = shaderV2::shader_FileReader(vertex_Shader_FileName, isValidated, install_Path + VERTEX_SHADER_PATH_ROOT);
    const char* vertex_Shader_Pointer = vertex_Shader_String.c_str();
    current_VSO = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(current_VSO, 1, &vertex_Shader_Pointer, NULL);
    glCompileShader(current_VSO);
    if (isChecked)
    {
        check_ShaderCompileInfo(current_VSO);
    }

    // read and compile fragment shader
    std::string fragment_Shader_String = shaderV2::shader_FileReader(fragment_Shader_FileName, isValidated, install_Path + FRAGMENT_SHADER_PATH_ROOT);
    const char* fragment_Shader_Pointer = fragment_Shader_String.c_str();
    current_FSO = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(current_FSO, 1, &fragment_Shader_Pointer, NULL);
    glCompileShader(current_FSO);
    if (isChecked)
    {
        check_ShaderCompileInfo(current_FSO);
    }

    // link shaders
    current_Program = glCreateProgram();
    glAttachShader(current_Program, current_VSO);
    glAttachShader(current_Program, current_FSO);
    glLinkProgram(current_Program);
    if (isChecked) {
        check_ShaderLinkInfo(current_Program);
    }


}

shaderV2::shaderV2(std::string vertex_Shader_String, std::string fragment_Shader_String, bool isChecked, std::string shader_Name)
{
    this->shader_Name = shader_Name;
    // read and compile vertex shader
    const char* vertex_Shader_Pointer = vertex_Shader_String.c_str();
    current_VSO = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(current_VSO, 1, &vertex_Shader_Pointer, NULL);
    glCompileShader(current_VSO);
    if (isChecked)
    {
        check_ShaderCompileInfo(current_VSO);
    }

    // read and compile fragment shader
    const char* fragment_Shader_Pointer = fragment_Shader_String.c_str();
    current_FSO = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(current_FSO, 1, &fragment_Shader_Pointer, NULL);
    glCompileShader(current_FSO);
    if (isChecked)
    {
        check_ShaderCompileInfo(current_FSO);
    }

    // link shaders
    current_Program = glCreateProgram();
    glAttachShader(current_Program, current_VSO);
    glAttachShader(current_Program, current_FSO);
    glLinkProgram(current_Program);
    if (isChecked) {
        check_ShaderLinkInfo(current_Program);
    }

}

shaderV2::~shaderV2()
{

}

std::string shaderV2::shader_FileReader(const char* file_Name, bool isValidate, std::string shaderPathRoot)
{
    std::string file_Name_String = file_Name;
    std::fstream file_Stream;
    file_Stream.exceptions(std::fstream::failbit | std::fstream::badbit);
    try
    {
        file_Stream.open(shaderPathRoot + file_Name_String);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return "failed";
    }
    if (isValidate)
    {
        if (!file_Stream.good() || !file_Stream.is_open())
        {
            std::cout << "SHADER_FILE::" << file_Name << "::READ::FAILED !!!\n" << std::endl;
            return NULL;
        }
        else
        {
            std::cout << "SHADER_FILE::" << file_Name << "::READ::SUCCESFULLY" << std::endl;
        }
    }
    std::stringstream file_String_Stream;
    file_String_Stream << file_Stream.rdbuf();
    file_Stream.close();
    return file_String_Stream.str();
}

void shaderV2::check_ShaderCompileInfo(unsigned int shaderID)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "SHADER [" << this->shader_Name << "] COMPILATION FAILED!\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SHADER [" << this->shader_Name << "] COMPILATION SUCCESFULLY!\n" << std::endl;
    }
}

void shaderV2::check_ShaderLinkInfo(unsigned int programID)
{
    int success;
    char infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "SHADER [" << this->shader_Name << "] LINK FAILED!\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SHADER [" << this->shader_Name << "] LINK SUCCESFULLY!\n" << std::endl;
    }

}

void shaderV2::use_Program()
{
    glUseProgram(current_Program);
}

void shaderV2::set_Matrix(const char* parameter_Name, glm::mat4 mat)
{
    glUniformMatrix4fv(get_ParameterLocation(parameter_Name), 1, GL_FALSE, glm::value_ptr(mat));
}

unsigned int shaderV2::get_ParameterLocation(const char* parameter_Name)
{
    return glGetUniformLocation(current_Program, parameter_Name);
}

unsigned int shaderV2::get_ShaderProgram()
{
    return current_Program;
}

void shaderV2::delete_Program()
{
    glDeleteShader(current_VSO);
    glDeleteShader(current_FSO);
    glDeleteProgram(current_Program);
}

void shaderV2::set_Int(const char* parameter_Name, int value)
{
    glUniform1i(get_ParameterLocation(parameter_Name), value);
}

void shaderV2::set_Float(const char* parameter_Name, float value)
{
    glUniform1f(get_ParameterLocation(parameter_Name), value);
}

void shaderV2::set_Vector4(const char* parameter_Name, float x, float y, float z, float w)
{
    glUniform4f(get_ParameterLocation(parameter_Name), x, y, z, w);
}

void shaderV2::set_Vector3(const char* parameter_Name, float x, float y, float z)
{
    glUniform3f(get_ParameterLocation(parameter_Name), x, y, z);
}

void shaderV2::set_Vector2(const char* parameter_Name, float x, float y)
{
    glUniform2f(get_ParameterLocation(parameter_Name), x, y);
}