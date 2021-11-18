#include "users/geometry.h"

const int array_Size = 200;
GLuint compute_ShaderID;

// a kind compute shader example
void fun2() {

    // define three arrays
    float array01[array_Size];
    float array02[array_Size];
    float array_sum[array_Size];

    // init all arrays
    for (size_t i = 0; i < array_Size; i++) {
        array01[i] = float(i);
        array02[i] = array_Size - i - 1.0f;
        array_sum[i] = 10000.0f;
    }

    // opengl buffer operation
    GLuint inA, inB, outC;      // three unsigned numbers;

    // set 1st buffer
    glGenBuffers(1, &inA);      // generate a buffer name via inA's address
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, inA);        // which opengl buffer will be bound to the specified name
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * array_Size, array01, GL_STATIC_DRAW);        // fill data in the specified buffer

    // set 2nd buffer
    glGenBuffers(1, &inB);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, inB);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * array_Size, array02, GL_STATIC_DRAW);

    // set 3rd buffer
    glGenBuffers(1, &outC);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, outC);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * array_Size, array_sum, GL_STATIC_DRAW);

    // bind buffer to the fixed points, so shader could use 
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, inA);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, inB);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, outC);

    // set compute shader
    glUseProgram(compute_ShaderID);
    glDispatchCompute(13, 1, 1);

    // avoid memo usage overlaping, reading must wait unitl the whole process are completed
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);

    // to read the result, bind again
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, outC);
    float* data = (float*)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

    // Copy data to CPU Memory
    memcpy(&array_sum[0], data, sizeof(float) * array_Size);

    // release GPU Pointer
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    // now array_sum is fully done
}

// triangle vertices test, in order to skip vertex transform, we could use NDC coords directly

float triangle_Example[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};



void fun3() {
    std::cout << "fun3" << std::endl;
}

void get_ExampleTriangle() {
    std::cout << sizeof(triangle_Example) << std::endl;
    //std::cout << "get_ExampleTriangle" << std::endl;

}