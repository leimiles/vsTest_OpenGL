#include "users/texture.h"

static unsigned int texture01;
static unsigned int texture02;
static unsigned int texture03;
static unsigned int texture04;

texture::texture(const char* texture_FileName, unsigned int texture_Channel)
{
    switch (texture_Channel)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        std::cout << "texture channel must be 1, 2, 3, or 4" << std::endl;
        return;
    }
    std::string texture_FileName_String = texture_FileName;
    texture_FileName_String = TEXTURE_PATH_ROOT + texture_FileName_String;
}

texture::~texture()
{

}
