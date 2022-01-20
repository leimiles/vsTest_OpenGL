#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "users/object.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class model : public object
{
private:
    /* data */
public:
    model(/* args */);
    ~model();
};

#endif