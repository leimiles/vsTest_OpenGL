#include "users/texture.h"
#include "users/stb_image.h"

unsigned int texture::count = 0;

texture::texture(const char* texture_FileName, bool isChecked)
{
    std::string texture_FileName_String = texture_FileName;
    texture_FileName_String = TEXTURE_PATH_ROOT + texture_FileName_String;
    unsigned char* data = stbi_load(texture_FileName_String.c_str(), &width, &height, &number_OfChannels, 0);
    std::cout << width << std::endl;
    std::cout << height << std::endl;
    std::cout << number_OfChannels << std::endl;

}

texture::~texture()
{

}
