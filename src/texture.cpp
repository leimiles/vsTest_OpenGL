#include "users/texture.h"
#include "users/stb_image.h"

unsigned int texture::count = 0;

texture::texture(const char* texture_FileName, bool isChecked, bool isMipmap)
{
    std::string texture_FileName_String = texture_FileName;
    texture_FileName_String = TEXTURE_PATH_ROOT + texture_FileName_String;
    unsigned char* texture_Data = stbi_load(texture_FileName_String.c_str(), &width, &height, &number_OfChannels, 0);
    if (isChecked)
    {
        if (!texture_Data)
        {
            std::cout << "TEXTURE::" << texture_FileName_String << "::LOAD::FAILED !!!\n" << std::endl;
            return;
        }
        else
        {
            std::cout << "TEXTURE::" << texture_FileName_String << "::LOAD::SUCCESFULLY\n" << std::endl;
        }
    }
    glGenTextures(1, &TXO);
    glBindTexture(GL_TEXTURE_2D, TXO);
    set_TextureMode();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_Data);
    if (isMipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // free memory after setting texutre data on gpu side
    stbi_image_free(texture_Data);
}

void texture::set_TextureMode()
{
    // wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // mipmap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

texture::~texture()
{

}
