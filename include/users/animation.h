#ifndef ANIMATION_H
#define ANIMATION_H
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct boneInfo
{
    // bone matrix id
    int id;
    // matrix from model space to bone space
    glm::mat4 offset;

};

class animation
{
private:
    /* data */
public:
    animation(/* args */);
    ~animation();
};

#endif