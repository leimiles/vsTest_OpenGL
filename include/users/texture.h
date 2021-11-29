#ifndef TEXTURE_H
#define TEXTURE_H
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define TEXTURE_PATH_ROOT "./textures/"
#include <iostream>
#include <stdarg.h>
#include <string>
#include "glad/glad.h"

class texture
{
private:
    int width;
    int height;
    int number_OfChannels;
    static unsigned int texture01;
    static unsigned int texture02;
    static unsigned int texture03;
    static unsigned int texture04;
public:
    texture(const char* texture_FileName, unsigned int texture_Channel, bool isChecked);
    ~texture();
};

#endif

