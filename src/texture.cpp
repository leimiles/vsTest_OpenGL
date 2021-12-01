#include "users/texture.h"
#include "users/stb_image.h"

int texture::count = 0;

texture::texture(const char* texture_FileName, GLenum color_Mode, bool isChecked, bool isMipmap)
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
    set_TextureMode_2D();
    glTexImage2D(GL_TEXTURE_2D, 0, color_Mode, width, height, 0, color_Mode, GL_UNSIGNED_BYTE, texture_Data);
    if (isMipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // free memory after setting texutre data on gpu side
    stbi_image_free(texture_Data);
    texture::count++;
}

void texture::set_TextureMode_2D()
{
    // wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // mipmap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void texture::set_BoundTextures_2D(texture& tex, ...)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.TXO);
    if (--texture::count <= 0)
    {
        std::cout << "nothing" << std::endl;
        return;
    }
    va_list texture_Pointer;
    va_start(texture_Pointer, tex);

    while (texture::count)
    {
        //std::cout << texture::count << std::endl;
        texture::count--;
    }
    /*
    std::cout << "binding texture" << std::endl;
    std::cout << &(tex.TXO) << std::endl;
    std::cout << &(va_arg(texture_Pointer, texture).TXO) << std::endl;
    std::cout << &(va_arg(texture_Pointer, texture).TXO) << std::endl;
    std::cout << &(va_arg(texture_Pointer, texture).TXO) << std::endl;
    std::cout << &(va_arg(texture_Pointer, texture).TXO) << std::endl;
    */

    va_end(texture_Pointer);
}

texture::~texture()
{

}


