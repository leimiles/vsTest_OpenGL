#include "users/geometry.h"

geometry::geometry(unsigned int stride, unsigned int attributes_Size, float* attributes, unsigned int elements_Size, unsigned int* elements)
    : VERTEX_ATTRIBUTES_STRIDE(stride), VERTEX_ATTRIBUTES_SIZE(attributes_Size), VERTEX_ATTRIBUTES(attributes), VERTEX_ELEMENTS_SIZE(elements_Size), VERTEX_ELEMENTS(elements)
{
    geometry_Type = GL_TRIANGLES;
}

geometry::geometry(std::string model_Path)
{
    load_Model(model_Path);
    VERTEX_ATTRIBUTES_STRIDE = 0;
    VERTEX_ATTRIBUTES_SIZE = 0;
    VERTEX_ATTRIBUTES = nullptr;
    VERTEX_ELEMENTS_SIZE = 0;
    VERTEX_ELEMENTS = nullptr;
}

geometry::~geometry()
{
}

void geometry::load_Model(std::string model_Path)
{
    Assimp::Importer modelImporter;
    const aiScene* scenePtr = modelImporter.ReadFile(model_Path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scenePtr || scenePtr->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scenePtr->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::LOAD_MODEL::" << modelImporter.GetErrorString() << std::endl;
        return;
    }
    std::cout << "ASSIMP::MODEL_LOAD::SUCCESSFULLY\n" << std::endl;
    //model_Directory = model_Path.substr(0, model_Path.find_last_not_of('/'));
    //process_Node(scenePtr->mRootNode, scenePtr);
}

void geometry::process_Node(aiNode* node, const aiScene* scenePtr)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scenePtr->mMeshes[node->mMeshes[i]];
    }
}

void geometry::process_Mesh(aiMesh* mesh, const aiScene* scenePtr)
{

}

void geometry::set_Translate(float x, float y, float z)
{
    self_Transform.set_Translate(x, y, z);
}

void geometry::set_Rotate(float degrees, float x, float y, float z)
{
    self_Transform.set_Rotate(degrees, x, y, z);
}

void geometry::set_Scale(float x, float y, float z)
{
    self_Transform.set_Scale(x, y, z);
}

glm::mat4 geometry::get_Matrix_LocalToWorld()
{
    return self_Transform.get_Matrix_LocalToWorld();
}

glm::mat4 geometry::get_Matrix_WorldToLocal()
{
    return self_Transform.get_Matrix_WorldToLocal();
}
