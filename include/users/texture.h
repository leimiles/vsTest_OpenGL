#ifndef TEXTURE_H
#define TEXTURE_H
#define TEXTURE_PATH_ROOT "./textures/"
#include "glad/glad.h"
#include <string>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION

class texture
{
private:
    static unsigned int count;
    int width;
    int height;
    int number_OfChannels;
public:
    unsigned int TXO;
    texture(const char* texture_FileName, bool isChecked, bool isMipmap);
    ~texture();
    void set_TextureMode();
};

#endif

