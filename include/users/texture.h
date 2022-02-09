#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#define TEXTURE_PATH_ROOT "./resources/textures/"
#include <string>
#include <iostream>
#include <cstdarg>
#include "glad/glad.h"
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
    unsigned int get_TXO();
    static void set_BoundTextures_2D(int count, ...);
};

#endif

