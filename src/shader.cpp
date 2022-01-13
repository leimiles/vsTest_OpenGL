#include "users\shader.h"

unsigned int shader::current_Program;
unsigned int shader::current_VSO;
unsigned int shader::current_FSO;

shader::shader(const char* vertex_Shader_FileName, const char* fragment_Shader_FileName, bool isChecked, bool isValidated)
{
    // read and compile vertex shader
    std::string vertex_Shader_String = shader::shader_FileReader(vertex_Shader_FileName, isValidated, VERTEX_SHADER_PATH_ROOT);
    const char* vertex_Shader_Pointer = vertex_Shader_String.c_str();
    shader::current_VSO = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader::current_VSO, 1, &vertex_Shader_Pointer, NULL);
    glCompileShader(shader::current_VSO);
    if (isChecked)
    {
        shader::check_ShaderCompileInfo(shader::current_VSO);
    }

    // read and compile fragment shader
    std::string fragment_Shader_String = shader::shader_FileReader(fragment_Shader_FileName, isValidated, FRAGMENT_SHADER_PATH_ROOT);
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

std::string shader::shader_FileReader(const char* file_Name, bool isValidate, std::string shaderPathRoot)
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
        std::cout << "ERROR::SHADER::COMPILATION::FAILED !!!\n" << infoLog << std::endl;
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
        std::cout << "ERROR::SHADER::LINK::FAILED !!!\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "SHADER::PROGRAM::LINK::LOOKS::GREAT\n" << std::endl;
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

void shader::set_Float(const char* parameter_Name, float value)
{
    glUniform1f(get_ParameterLocation(parameter_Name), value);
}

void shader::set_Int(const char* parameter_Name, int value)
{
    glUniform1i(get_ParameterLocation(parameter_Name), value);
}

void shader::set_Matrix(const char* parameter_Name, glm::mat4 mat)
{
    glUniformMatrix4fv(get_ParameterLocation(parameter_Name), 1, GL_FALSE, glm::value_ptr(mat));
}

int shader::get_ParameterLocation(const char* parameter_Name)
{
    return glGetUniformLocation(shader::current_Program, parameter_Name);
}
