#include "users\shader.h"

unsigned int shader::current_Program;
unsigned int shader::current_VSO;
unsigned int shader::current_FSO;

shader::shader(const char* vertex_Shader_FileName, const char* fragment_Shader_FileName, bool isChecked, bool isValidated)
{
    // read and compile vertex shader
    std::string vertex_Shader_String = shader::shader_FileReader(vertex_Shader_FileName, isValidated);
    const char* vertex_Shader_Pointer = vertex_Shader_String.c_str();
    shader::current_VSO = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader::current_VSO, 1, &vertex_Shader_Pointer, NULL);
    glCompileShader(shader::current_VSO);
    if (isChecked)
    {
        shader::check_ShaderCompileInfo(shader::current_VSO);
    }

    // read and compile fragment shader
    std::string fragment_Shader_String = shader::shader_FileReader(fragment_Shader_FileName, isValidated);
    const char* fragment_Shader_Pointer = fragment_Shader_String.c_str();
    shader::current_FSO = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader::current_FSO, 1, &fragment_Shader_Pointer, NULL);
    glCompileShader(shader::current_FSO);
    if (isChecked)
    {
        shader::check_ShaderCompileInfo(shader::current_FSO);
    }

    // link shaders
    shader::current_Program = glCreateProgram();
    glAttachShader(shader::current_Program, shader::current_VSO);
    glAttachShader(shader::current_Program, shader::current_FSO);
    glLinkProgram(shader::current_Program);
    if (isChecked) {
        shader::check_ShaderLinkInfo(shader::current_Program);
    }

}

std::string shader::shader_FileReader(const char* file_Name, bool isValidate)
{
    std::string file_Name_String = file_Name;
    std::fstream file_Stream;
    file_Stream.exceptions(std::fstream::failbit | std::fstream::badbit);
    file_Stream.open(SHADER_PATH_ROOT + file_Name_String);
    if (isValidate)
    {
        if (!file_Stream.good() || !file_Stream.is_open())
        {
            std::cout << file_Name << "::ERROR::VERTEX_SHADER::READ::FAILED" << std::endl;
            return NULL;
        }
        else
        {
            std::cout << file_Name << "::SHADER_FILE::READ::SUCCESFULLY" << std::endl;
        }
    }
    std::stringstream file_String_Stream;
    file_String_Stream << file_Stream.rdbuf();
    file_Stream.close();
    return file_String_Stream.str();
}

shader::~shader()
{
}

void shader::check_ShaderCompileInfo(unsigned int shaderID)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION::ERROR\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SHADER::COMPILATION::LOOKS::GREAT\n" << std::endl;
    }
}

void shader::check_ShaderLinkInfo(unsigned int programID)
{
    int success;
    char infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::ERROR\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SHADER::PROGRAM::LINK::LOOKS::GREAT!\n" << std::endl;
    }

}

void shader::delete_Program()
{
    glDeleteShader(shader::current_VSO);
    glDeleteShader(shader::current_FSO);
    glDeleteProgram(shader::current_Program);
}

void shader::use_Program()
{
    glUseProgram(shader::current_Program);
}

void shader::set_Float(int parameter_Location, float value)
{
    glUniform1f(parameter_Location, value);
}

int shader::get_ParameterLocation(const char* parameter_Name)
{
    return glGetUniformLocation(shader::current_Program, parameter_Name);
}