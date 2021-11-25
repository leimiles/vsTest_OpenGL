#include "users\shader.h"

unsigned int shader::current_VSO = 0;

// this is test shader
const char* shader::test_VertexShader = "#version 330\n"
"layout (location = 0) in vec3 pos_NDC;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(pos_NDC.x, pos_NDC.y, pos_NDC.z, 1.0);\n"
"}\n";

const char* shader::test_FragmentShader = "#version 330\n"
"out vec4 final_Color;\n"
"uniform vec4 myColor;"
"void main()\n"
"{\n"
"final_Color = vec4(0.35f, myColor.g, 0.12f, 1.0f);\n"
"}\n";

const char* shader::test_VertexShader2 = "#version 330\n"
"layout (location = 0) in vec3 pos_NDC;\n"
"layout (location = 1) in vec4 color;\n"
"out vec4 vertex_Color;\n"
"void main()\n"
"{\n"
"vertex_Color = color;\n"
"gl_Position = vec4(pos_NDC.x, pos_NDC.y, pos_NDC.z, 1.0);\n"
"}\n";

const char* shader::test_FragmentShader2 = "#version 330\n"
"out vec4 final_Color;\n"
"in vec4 vertex_Color;\n"
"void main()\n"
"{\n"
"final_Color = vec4(vertex_Color.r, vertex_Color.g, vertex_Color.b, vertex_Color.a);\n"
"}\n";


shader::shader(/* args */)
{
}

shader::shader(const char* vertex_Shader_FileName, const char* fragment_Shader_FileName, bool isChecked, bool isValidated)
{
    std::string vertex_Shader_String = shader::shader_FileReader(vertex_Shader_FileName, isValidated);
    const char* vertex_Shader_Pointer = vertex_Shader_String.c_str();


    /*
    std::string vertex_Shader_Path = vertex_Shader_FileName;
    std::ifstream vertex_Shader_File;
    vertex_Shader_File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    vertex_Shader_File.open(SHADER_PATH_ROOT + vertex_Shader_Path);
    if (isValidated)
    {
        if (!vertex_Shader_File.is_open() || !vertex_Shader_File.good())
        {
            std::cout << "ERROR::VERTEX_SHADER::READ::FAILED" << std::endl;
            return;
        }
        else
        {
            std::cout << "VERTEX_SHADER::READ::DONE" << std::endl;
        }
    }
    std::stringstream vertex_Shader_Stream;
    vertex_Shader_Stream << vertex_Shader_File.rdbuf();
    vertex_Shader_File.close();
    std::string vertex_Shader_Code = vertex_Shader_Stream.str();
    const char* vertex_Shader_Pointer = vertex_Shader_Code.c_str();
    std::cout << vertex_Shader_Pointer << std::endl;
    */

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
            std::cout << "ERROR::VERTEX_SHADER::READ::FAILED" << std::endl;
            return NULL;
        }
        else
        {
            std::cout << "VERTEX_SHADER::READ::DONE" << std::endl;
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
        std::cout << "SHADER::STATUS::LOOKS::GREAT!\n" << std::endl;
    }
}
