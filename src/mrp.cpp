#include "users/mrp.h"

unsigned int mrp::current_VSO = 0;
unsigned int mrp::current_FSO = 0;
unsigned int mrp::current_Program = 0;

mrp::mrp(/* args */)
{
}

mrp::~mrp()
{
}

// set(clear) color buffer with specified color
void mrp::clear_ColorBuffer()
{
    // set clear color  value
    glClearColor(0.12f, 0.35f, 0.3f, 1.0f);
    // clear color buffer with the set of clear color
    glClear(GL_COLOR_BUFFER_BIT);
}

// test tirangle would not be changed frequently, so we can bind vao before the render loop
void mrp::set_TestTriangleData() {
    // prepare vbo
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry::triangle_Example), geometry::triangle_Example, GL_STATIC_DRAW);
    // prepare vao
    //unsigned int VAO;
    glGenVertexArrays(1, &current_VAO);
    glBindVertexArray(current_VAO);
    // set attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

}

void mrp::set_TestTriangleShader(bool isChecked)
{
    // prepare vertex shader
    mrp::current_VSO = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mrp::current_VSO, 1, &shader::test_VertexShader, NULL);
    glCompileShader(mrp::current_VSO);
    if (isChecked)
    {
        check_ShaderCompileInfo(mrp::current_VSO);
    }

    // prepare fragment shader
    mrp::current_FSO = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mrp::current_FSO, 1, &shader::test_FragmentShader, NULL);
    glCompileShader(mrp::current_FSO);
    if (isChecked)
    {
        check_ShaderCompileInfo(mrp::current_FSO);
    }

    // prepare and link shader
    mrp::current_Program = glCreateProgram();
    glAttachShader(mrp::current_Program, mrp::current_VSO);
    glAttachShader(mrp::current_Program, mrp::current_FSO);
    glLinkProgram(mrp::current_Program);
    if (isChecked)
    {
        check_ShaderLinkInfo(mrp::current_Program);
    }
}

void mrp::draw_TestTriangle()
{
    glUseProgram(mrp::current_Program);
    glBindVertexArray(current_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDeleteShader(current_VSO);
    glDeleteShader(current_FSO);
    //std::cout << mrp::current_Program << std::endl;
    //check_ShaderLinkInfo(*mrp::current_Program);
}

// just a test
void mrp::test()
{
    // use VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // generate VBO buffer object name
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // bind buffer to gl , from here gl_array_buffer is under control by VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // fill buffer with our data
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry::triangle_Example), geometry::triangle_Example, GL_STATIC_DRAW);

    // use attribute pointer to tell gl how to read vbo
    // 0, means where we want to pass the data to in vertex shader, shader said (location = 0), so ...
    // 3, size of this attribute, 3 means 3 values
    // gl_float, type of the value
    // gl_false, meanse we don't need normalized value for now
    // how long between each vertex attribute, 0 mean let opengl decide, only works when tighly packed
    // where vbo starts
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    // 0 means
    glEnableVertexAttribArray(0);

    // generate vertex shader object name
    unsigned int VSO;    // means vertex shader object
    // create vertex shader object and return id
    VSO = glCreateShader(GL_VERTEX_SHADER);
    // fill shader source code
    glShaderSource(VSO, 1, &shader::test_VertexShader, NULL);
    // compile shader
    glCompileShader(VSO);
    // check if shader compiled successfully
    //check_ShaderCompileInfo(VSO);

    // generate fragment shader object name, similar to vertex shader
    unsigned int FSO;
    FSO = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FSO, 1, &shader::test_FragmentShader, NULL);
    glCompileShader(FSO);
    // check compilation error if needed
    //check_ShaderCompileInfo(FSO);

    // create shader program
    unsigned int shader_Program;
    shader_Program = glCreateProgram();
    // link the compiled shaders to this shader program
    glAttachShader(shader_Program, VSO);
    glAttachShader(shader_Program, FSO);
    glLinkProgram(shader_Program);
    // check if shader program linking error
    //check_ShaderLinkInfo(shader_Program);
    glUseProgram(shader_Program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // delete shader after linking
    glDeleteShader(VSO);
    glDeleteShader(FSO);


}


void mrp::check_ShaderLinkInfo(unsigned int programID)
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
        std::cout << "PROGRAM::LINK::LOOKS::GREAT!\n" << std::endl;
    }

}


void mrp::check_ShaderCompileInfo(unsigned int shaderID)
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
