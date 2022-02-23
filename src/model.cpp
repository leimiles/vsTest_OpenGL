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

    //sceneNode_Info(sceneNode);

    extract_Materials(sceneNode);

    process_Node(sceneNode->mRootNode, sceneNode);
}

void model::print_SceneNode_Keys(const aiScene* sceneNode)
{
    // print all scenenode keys
    if (sceneNode->mMetaData->mNumProperties > 0)
    {
        std::cout << "sceneNode Info:" << std::endl;
        for (int i = 0; i < sceneNode->mMetaData->mNumProperties; i++)
        {
            aiString type_String;
            aiVector3D type_Vector3D;
            ai_int32 type_Int32;
            ai_int type_Int;
            ai_real type_real;
            std::cout << "\tproperty key:[" << (sceneNode->mMetaData->mKeys + i)->C_Str() << "]\t|\tproperty value:[";
            if (sceneNode->mMetaData->Get(i, type_String))
            {
                std::cout << type_String.C_Str() << "]" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_Vector3D))
            {
                std::cout << type_Vector3D.x << ", " << type_Vector3D.y << ", " << type_Vector3D.z << "]" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_Int32))
            {
                std::cout << type_Int32 << "]" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_Int))
            {
                std::cout << type_Int << "]" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_real))
            {
                std::cout << type_real << "]" << std::endl;
            }
            else
            {
                std::cout << "no type match] " << std::endl;
            }

        }
        std::cout << "\n";
    }
}


void model::print_AiMatrix(aiMatrix4x4& mat)
{
    std::cout << " ---- \n";

    std::cout << mat.a1 << "\t" << mat.a2 << "\t" << mat.a3 << "\t" << mat.a4 << std::endl;
    std::cout << mat.b1 << "\t" << mat.b2 << "\t" << mat.b3 << "\t" << mat.b4 << std::endl;
    std::cout << mat.c1 << "\t" << mat.c2 << "\t" << mat.c3 << "\t" << mat.c4 << std::endl;
    std::cout << mat.d1 << "\t" << mat.d2 << "\t" << mat.d3 << "\t" << mat.d4 << std::endl;

    std::cout << " ---- \n";
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

void model::extract_Materials(const aiScene* sceneNode)
{
    for (unsigned int i = 0; i < sceneNode->mNumMaterials; i++)
    {
        std::cout << "extract material_" << i << " [" << sceneNode->mMaterials[i]->GetName().C_Str() << "] from fbx file" << std::endl;
        material* mat = new material(*shaderV2::current_Shader);
        mat->material_Name = sceneNode->mMaterials[i]->GetName().C_Str();
    }

    std::cout << "\n";
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
    //std::cout << "mesh [" << meshNode->mName.C_Str() << "] has material_" << meshNode->mMaterialIndex << std::endl;

    return mesh;
}


void model::fill_Textures_Chicken01(material* material, const char* meshName)
{

    texture::textures_Directory = current_Model_Directory;
    std::cout << "mesh [" << meshName << "] looking for textures: " << std::endl;
    std::string main_Name = (std::string)meshName;
    // find diffuse map
    std::string diffuse_Regex_String = "^" + main_Name + "_[D,d]\\.(jpg|png|tga|psd)$";
    std::regex diffuseMap_Regex(diffuse_Regex_String);
    std::string normal_Regex_String = "^" + main_Name + "_[N,n]\\.(jpg|png|tga|psd)$";
    std::regex normalMap_Regex(normal_Regex_String);
    std::string metallic_Regex_String = "^" + main_Name + "_[M,m]\\.(jpg|png|tga|psd)$";
    std::regex metallicMap_Regex(metallic_Regex_String);
    std::string roughness_Regex_String = "^" + main_Name + "_[R,r]\\.(jpg|png|tga|psd)$";
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

    if (material->get_TexturesCount() == 0)
    {
        std::cout << "\t material [" << material->material_Name << "] has no textures." << std::endl;
    }

    std::cout << "\n";

}

void model::fill_Material(mesh& mesh, aiMesh* meshNode)
{
    if (shaderV2::current_Shader != nullptr)
    {
        if (mesh.material == nullptr)
        {
            mesh.material = material::current_Materials[meshNode->mMaterialIndex];
            fill_Textures_Chicken01(mesh.material, meshNode->mName.C_Str());
            /*
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
                //fill_Textures_Chicken01(mesh.material);
            }
            */
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
