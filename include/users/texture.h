#ifndef TEXTURE_H
#define TEXTURE_H
#define TEXTURE_PATH_ROOT "./textures/"
#include "glad/glad.h"
#include <string>
#include <iostream>
#include <cstdarg>
#define STB_IMAGE_IMPLEMENTATION

class texture
{
private:
    static int count;
    int width;
    int height;
    int number_OfChannels;
    unsigned int TXO;
public:
    texture(const char* texture_FileName, GLenum color_Mode, bool isChecked, bool isMipmap);
    ~texture();
    void set_TextureMode_2D();
    static void set_BoundTextures_2D(texture& tex, ...);
};

#endif

