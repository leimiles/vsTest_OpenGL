#ifndef MODEL_H
#define MODEL_H
#define MODEL_PATH_ROOT "resources/models/"
#include <vector>
#include "users/object.h"
#include "users/material.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "mesh.h"

class model : public object
{
private:
    std::string model_Path;
    void load_Model();
    void process_Node(aiNode* node, const aiScene* sceneNode);
    mesh get_Processed_Mesh(aiMesh* meshNode, const aiScene* sceneNode);
public:
    std::vector<mesh> submeshes;
    model(std::string model_Path);
    ~model();
    void set_Material_ForSubMesh(unsigned int submesh_id, material& material);
};

#endif