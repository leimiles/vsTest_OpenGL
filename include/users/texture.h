#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#define TEXTURE_PATH_ROOT "./resources/textures/"
#include <string>
#include <iostream>
#include <cstdarg>
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION

struct texture_Pattern
{
    std::string texture_Main_Name;
    std::string texture_Prefix_Name;
    std::string texture_Postfix_Name;
    std::string texture_Extend_Name;
};

class texture
{
private:
    static int count;
    int width;
    int height;
    int number_OfChannels;
    unsigned int TXO;
public:
    std::string texture_VariableName;
    static std::string textures_Directory;
    texture(const char* texture_FileName, GLenum color_Mode, bool isFlipV, bool isChecked, bool isMipmap);
    texture(const char* texture_FileName, bool isFlipV, bool isChecked, bool isMipmap);
    ~texture();
    void set_TextureMode_2D();
    unsigned int get_TXO() const;
    static void set_BoundTextures_2D(int count, ...);
};

#endif

