#include "users/texture.h"
#include "stb_image.h"

int texture::count = 0;
std::string texture::textures_Directory = "";

texture::texture(const char* texture_FileName, GLenum color_Mode, bool isFlipV, bool isChecked, bool isMipmap)
{
    std::string texture_FileName_String = texture_FileName;
    if (textures_Directory == "")
    {
        texture_FileName_String = DEFAULT_TEXTURE_DIR + texture_FileName_String;
    }
    else
    {
        texture_FileName_String = textures_Directory + texture_FileName_String;
    }

    // this is for opengl which 0.0 is at bottom
    stbi_set_flip_vertically_on_load(isFlipV);
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

/*
...........................................................................
Base Internal Format	RGBA, Depth and Stencil Values	Internal Components
---------------------------------------------------------------------------
GL_DEPTH_COMPONENT	    Depth	                        D
GL_DEPTH_STENCIL	    Depth, Stencil	                D, S
GL_RED	                Red	                            R
GL_RG	                Red, Green	                    R, G
GL_RGB	                Red, Green, Blue	            R, G, B
GL_RGBA	                Red, Green, Blue, Alpha	        R, G, B, A
...........................................................................
*/

texture::texture(const char* texture_FileName, bool isFlipV, bool isChecked, bool isMipmap)
{
    std::string texture_FileName_String = texture_FileName;
    if (textures_Directory == "")
    {
        texture_FileName_String = DEFAULT_TEXTURE_DIR + texture_FileName_String;
    }
    else
    {
        texture_FileName_String = textures_Directory + texture_FileName_String;
    }
    // this is for opengl which 0.0 is at bottom
    stbi_set_flip_vertically_on_load(isFlipV);
    unsigned char* texture_Data = stbi_load(texture_FileName_String.c_str(), &width, &height, &number_OfChannels, 0);
    if (isChecked)
    {
        if (!texture_Data)
        {
            std::cout << "\t\tTEXTURE::" << texture_FileName_String << "::LOAD::FAILED !!!" << std::endl;
            return;
        }
        else
        {
            std::cout << "\t\tTEXTURE::" << texture_FileName_String << "::LOAD::SUCCESFULLY" << std::endl;
        }
    }
    glGenTextures(1, &TXO);
    glBindTexture(GL_TEXTURE_2D, TXO);
    set_TextureMode_2D();

    switch (number_OfChannels)
    {
    case 1:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture_Data);
        break;
    case 2:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, texture_Data);
        break;
    case 3:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_Data);
        break;
    case 4:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_Data);
        break;

    default:
        break;
    }

    if (isMipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // free memory after setting texutre data on gpu side
    stbi_image_free(texture_Data);
    texture::count++;
}

texture::texture(std::string texture_Absolute_Path, bool isFlipV, bool isChecked, bool isMipmap)
{
    // this is for opengl which 0.0 is at bottom
    stbi_set_flip_vertically_on_load(isFlipV);
    unsigned char* texture_Data = stbi_load(texture_Absolute_Path.c_str(), &width, &height, &number_OfChannels, 0);
    if (isChecked)
    {
        if (!texture_Data)
        {
            std::cout << "\t\tTEXTURE::" << texture_Absolute_Path << "::LOAD::FAILED !!!" << std::endl;
            return;
        }
        else
        {
            std::cout << "\t\tTEXTURE::" << texture_Absolute_Path << "::LOAD::SUCCESFULLY" << std::endl;
        }
    }
    glGenTextures(1, &TXO);
    glBindTexture(GL_TEXTURE_2D, TXO);
    set_TextureMode_2D();

    switch (number_OfChannels)
    {
    case 1:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texture_Data);
        break;
    case 2:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, texture_Data);
        break;
    case 3:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_Data);
        break;
    case 4:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_Data);
        break;

    default:
        break;
    }

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

void texture::set_BoundTextures_2D(int count, ...)
{
    va_list texture_Pointer;
    va_start(texture_Pointer, count);
    for (int i = 0; i < count; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, va_arg(texture_Pointer, texture).TXO);
    }
    va_end(texture_Pointer);
}

texture::~texture()
{

}

unsigned int texture::get_TXO() const
{
    return TXO;
}


