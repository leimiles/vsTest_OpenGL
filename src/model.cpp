#include "users/model.h"

std::string model::current_Model_Directory = "";
std::string model::remote_Model_Directory;

model::model(std::string model_Name) : model_Name(model_Name)
{
    if (current_Model_Directory == "")
    {
        current_Model_Directory = MODEL_PATH_ROOT;
    }
    this->model_Path = current_Model_Directory + model_Name;
    load_Model();
}

model::~model()
{
}

void model::load_Model()
{
    Assimp::Importer fbxImporter;
    const aiScene* sceneNode = fbxImporter.ReadFile(model_Path, aiProcess_Triangulate);
    if (!sceneNode || sceneNode->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !sceneNode->mRootNode)
    {
        std::cout << "MODEL::" << model_Path << "::NOT LOADED!\n" << fbxImporter.GetErrorString() << std::endl;
        return;
    }
    else
    {
        std::cout << "MODEL::" << model_Path << "::LOAD SUCCESSFULLY\n" << std::endl;
    }

    process_Node(sceneNode->mRootNode, sceneNode);
}

void model::process_Node(aiNode* node, const aiScene* sceneNode)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = sceneNode->mMeshes[node->mMeshes[i]];
        submeshes.push_back(get_Processed_Mesh(mesh, sceneNode));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_Node(node->mChildren[i], sceneNode);
    }
}

mesh model::get_Processed_Mesh(aiMesh* meshNode, const aiScene* sceneNode)
{
    std::vector<vertexAttri_Pattern_FBX> vertex_Attributes;
    std::vector<unsigned int> vertex_Elements;
    //std::cout << "vertices: " << meshNode->mNumVertices << std::endl;

    for (unsigned int i = 0; i < meshNode->mNumVertices; i++)
    {
        vertexAttri_Pattern_FBX vtx_Attri;
        vtx_Attri.position_Obj.x = meshNode->mVertices[i].x;
        vtx_Attri.position_Obj.y = meshNode->mVertices[i].y;
        vtx_Attri.position_Obj.z = meshNode->mVertices[i].z;

        if (meshNode->HasNormals())
        {
            vtx_Attri.normal_Obj.x = meshNode->mNormals[i].x;
            vtx_Attri.normal_Obj.y = meshNode->mNormals[i].y;
            vtx_Attri.normal_Obj.z = meshNode->mNormals[i].z;
        }

        if (meshNode->mTextureCoords[0])
        {
            vtx_Attri.texcoords.x = meshNode->mTextureCoords[0][i].x;
            vtx_Attri.texcoords.y = meshNode->mTextureCoords[0][i].y;
        }
        else
        {
            vtx_Attri.texcoords.x = 0.0f;
            vtx_Attri.texcoords.y = 0.0f;
        }

        if (meshNode->HasTangentsAndBitangents())
        {
            vtx_Attri.tangent_Obj.x = meshNode->mTangents[i].x;
            vtx_Attri.tangent_Obj.y = meshNode->mTangents[i].y;
            vtx_Attri.tangent_Obj.z = meshNode->mTangents[i].z;

            vtx_Attri.bitangent_Obj.x = meshNode->mBitangents[i].x;
            vtx_Attri.bitangent_Obj.y = meshNode->mBitangents[i].y;
            vtx_Attri.bitangent_Obj.z = meshNode->mBitangents[i].z;

        }
        vertex_Attributes.push_back(vtx_Attri);
    }

    for (unsigned int i = 0; i < meshNode->mNumFaces; i++)
    {
        aiFace face = meshNode->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            vertex_Elements.push_back(face.mIndices[j]);
        }
    }

    return mesh(vertex_Attributes, vertex_Elements);
}

void model::set_Material_ForSubMesh(unsigned int submesh_id, material& material)
{
    if (submesh_id < this->submeshes.size() && submesh_id >= 0)
    {
        this->submeshes[submesh_id].material = &material;
    }
    else
    {
        std::cout << "can't find submesh[" << submesh_id << "] to assign material. " << std::endl;
        return;
    }
}
