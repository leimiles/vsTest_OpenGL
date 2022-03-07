#ifndef MODEL_H
#define MODEL_H
#define DEFAULT_MODEL_DIR "resources/models/"
#define DEFAULT_MODEL_NAME "Sausage_33.fbx"
#define DEFAULT_TEXTURE_DIR "./resources/textures/"
#include <vector>
#include <regex>
#include <filesystem>
#include "users/object.h"
#include "users/material.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "users/mesh.h"

struct model_Info
{
    std::string fbx_Version;    // property: SourceAsset_Generator
    std::string model_Name; // fbx name

    short upAxis;     // 0 means x, 1 means y, 2 means z, property UpAxis
    short upAxis_Sign;  // 0 means +, 1 means -, property UpAxisSign
    short frontAxis;    // p
    short frontAxis_Sign;
    float scaleFactor;
    float frameRate;
    long timeSpan_Start;
    long timeSpan_Stop;

    unsigned int has_Material;
    unsigned int has_Textures;
    unsigned int has_Animation;
    unsigned int has_Mesh;
    std::vector<mesh_Info> mesh_Infos;

    unsigned int has_Camera;
    unsigned int has_Light;

    /*
        std::vector<std::string> mesh_Names;
        std::vector<std::string> material_Names;
        std::vector<std::string> texture_Name;
        std::vector<std::string> light_Names;
        std::vector<std::string> camera_Names;
        std::vector<std::string> animation_Names;
    */
};

class model : public object
{
private:
    shaderV2* preview_Shader;
    std::string model_Path;
    aiMatrix4x4 final_Transform;
    std::vector<material*> preview_Materials;
    void load_Model();
    void process_Node(aiNode* node, const aiScene* sceneNode);
    mesh get_Processed_Mesh(aiMesh* meshNode, const aiScene* sceneNode, const aiMatrix4x4* matrix);
    void extract_Materials(const aiScene* sceneNode);
    void bind_Material(mesh& mesh, unsigned int preview_Material_ID);
    void fill_Matrix(mesh& mesh, const aiMatrix4x4* matrix);
    void fill_Textures_Chicken01(material* material, std::string& meshName);
    void calculate_FinalTransform(aiNode* node);
    void reset_FinalTransform();
    void fill_Model_Info(const aiScene* sceneNode);
    void show_Model_Info();
    void extract_BoneWeightForVertices(std::vector<vertexAttri_Pattern_FBX>& vertex_Attributes, aiMesh* mesh, const aiScene* scene);
    static void print_AiMatrix(aiMatrix4x4& matrix);
    static void print_SceneNode_Keys(const aiScene* sceneNode);
public:
    model_Info model_Info;
    std::string current_Model_Directory;
    std::string model_Name;
    std::vector<mesh> submeshes;
    model(std::string model_Full_Path, shaderV2& shader);
    ~model();
    void set_Material_ForSubMesh(unsigned int submesh_id, material& material);
    glm::mat4 get_Matrix_LocalToWorld(const mesh& mesh) const;
};

#endif