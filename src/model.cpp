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
    const aiScene* sceneNode = fbxImporter.ReadFile(model_Path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
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

void model::extract_BoneWeightForVertices(std::vector<vertexAttri_Pattern_FBX>& vertex_Attributes, aiMesh* mesh, const aiScene* scene)
{
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

    extract_BoneWeightForVertices(vertex_Attributes, meshNode, sceneNode);

    mesh mesh(vertex_Attributes, vertex_Elements);

    fill_Material(mesh, meshNode);

    return mesh;
}


void model::fill_Textures_Chicken01(material* material)
{

    texture::textures_Directory = current_Model_Directory;
    std::cout << "new material [" << material->material_Name << "] looking for textures: " << std::endl;
    // find diffuse map
    std::string diffuse_Regex_String = "^" + material->material_Name + "_[D,d]\\.(jpg|png|tga|psd)$";
    std::regex diffuseMap_Regex(diffuse_Regex_String);
    std::string normal_Regex_String = "^" + material->material_Name + "_[N,n]\\.(jpg|png|tga|psd)$";
    std::regex normalMap_Regex(normal_Regex_String);
    std::string metallic_Regex_String = "^" + material->material_Name + "_[M,m]\\.(jpg|png|tga|psd)$";
    std::regex metallicMap_Regex(metallic_Regex_String);
    std::string roughness_Regex_String = "^" + material->material_Name + "_[R,r]\\.(jpg|png|tga|psd)$";
    std::regex roughtnessMap_Regex(roughness_Regex_String);

    for (const auto& entry : std::filesystem::directory_iterator(current_Model_Directory))
    {
        std::string file_Name = entry.path().filename().string();
        if (std::regex_match(file_Name, diffuseMap_Regex))
        {
            std::cout << "\t material [" << material->material_Name << "] found diffuse texture: " << file_Name << std::endl;
            texture* tex_Diffuse = new texture(file_Name.c_str(), true, true, true);
            material->set_Texture("surf.diffuse", *tex_Diffuse);
            continue;
        }
        if (std::regex_match(file_Name, normalMap_Regex))
        {
            std::cout << "\t material [" << material->material_Name << "] found normal texture: " << file_Name << std::endl;
            continue;
        }
        if (std::regex_match(file_Name, metallicMap_Regex))
        {
            std::cout << "\t material [" << material->material_Name << "] found metallic texture: " << file_Name << std::endl;
            continue;
        }
        if (std::regex_match(file_Name, roughtnessMap_Regex))
        {
            std::cout << "\t material [" << material->material_Name << "] found roughness texture: " << file_Name << std::endl;
            continue;
        }
    }

}

void model::fill_Material(mesh& mesh, aiMesh* meshNode)
{
    if (shaderV2::current_Shader != nullptr)
    {
        if (mesh.material == nullptr)
        {
            if (meshNode->mMaterialIndex < material::current_Materials.size())
            {
                mesh.material = material::current_Materials[meshNode->mMaterialIndex];
            }
            else
            {
                // where can i delete this heap?
                material* mat = new material(*shaderV2::current_Shader);
                mat->material_Name = meshNode->mName.C_Str();
                mesh.material = mat;
                fill_Textures_Chicken01(mesh.material);
            }
        }


    }

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
