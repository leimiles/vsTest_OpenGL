#ifndef MODEL_H
#define MODEL_H
#define MODEL_PATH_ROOT "resources/models/"
#include <vector>
#include <regex>
#include <filesystem>
#include "users/object.h"
#include "users/material.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "users/mesh.h"

class model : public object
{
private:
    std::string model_Path;
    aiMatrix4x4 final_Transform;
    void load_Model();
    void process_Node(aiNode* node, const aiScene* sceneNode);
    mesh get_Processed_Mesh(aiMesh* meshNode, const aiScene* sceneNode, const aiMatrix4x4* matrix);
    void extract_Materials(const aiScene* sceneNode);
    void fill_Material(mesh& mesh, aiMesh* meshNode);
    void fill_Matrix(mesh& mesh, const aiMatrix4x4* matrix);
    void fill_Textures_Chicken01(material* material, const char* meshName);
    void extract_BoneWeightForVertices(std::vector<vertexAttri_Pattern_FBX>& vertex_Attributes, aiMesh* mesh, const aiScene* scene);
    static void print_AiMatrix(aiMatrix4x4& matrix);
    static void print_SceneNode_Keys(const aiScene* sceneNode);
    static void reset_AiMatrix4x4(aiMatrix4x4& matrix);
public:
    static std::string current_Model_Directory;
    static std::string remote_Model_Directory;
    const std::string model_Name;
    std::vector<mesh> submeshes;
    model(std::string model_Name);
    ~model();
    void set_Material_ForSubMesh(unsigned int submesh_id, material& material);
    glm::mat4 get_Matrix_LocalToWorld(const mesh& mesh) const;
};

#endif