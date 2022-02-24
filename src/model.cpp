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

    //print_SceneNode_Keys(sceneNode);

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


void model::print_AiMatrix(aiMatrix4x4& matrix)
{
    std::cout << "\t" << matrix.a1 << "\t" << matrix.a2 << "\t" << matrix.a3 << "\t" << matrix.a4 << std::endl;
    std::cout << "\t" << matrix.b1 << "\t" << matrix.b2 << "\t" << matrix.b3 << "\t" << matrix.b4 << std::endl;
    std::cout << "\t" << matrix.c1 << "\t" << matrix.c2 << "\t" << matrix.c3 << "\t" << matrix.c4 << std::endl;
    std::cout << "\t" << matrix.d1 << "\t" << matrix.d2 << "\t" << matrix.d3 << "\t" << matrix.d4 << std::endl;
    std::cout << "\n";
}



void model::process_Node(aiNode* node, const aiScene* sceneNode)
{
    //std::cout << "processing node: " << node->mName.C_Str() << std::endl;
    //print_AiMatrix(node->mTransformation * );

    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = sceneNode->mMeshes[node->mMeshes[i]];
        calculate_FinalTransform(node);
        mesh->mName = node->mName;
        submeshes.push_back(get_Processed_Mesh(mesh, sceneNode, &final_Transform));
        reset_FinalTransform();
        //std::cout << "mesh [" << mesh->mName.C_Str() << "] has local tranformation:" << std::endl;
        //print_AiMatrix(final_Transform);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        process_Node(node->mChildren[i], sceneNode);
    }
}

void model::reset_FinalTransform()
{
    aiMatrix4x4 temp;
    this->final_Transform = temp;
}

void model::calculate_FinalTransform(aiNode* node)
{
    std::cout << "node transform after multiplied by : " << node->mName.C_Str() << "\n";
    final_Transform = node->mTransformation * final_Transform;
    print_AiMatrix(final_Transform);
    if (node->mParent)
    {
        calculate_FinalTransform(node->mParent);
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

mesh model::get_Processed_Mesh(aiMesh* meshNode, const aiScene* sceneNode, const aiMatrix4x4* matrix)
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

    fill_Matrix(mesh, matrix);

    return mesh;
}

void model::fill_Matrix(mesh& mesh, const aiMatrix4x4* matrix)
{
    // asign by column 0
    mesh.matrix_LocalToWorld[0][0] = matrix->a1;
    mesh.matrix_LocalToWorld[1][0] = matrix->a2;
    mesh.matrix_LocalToWorld[2][0] = matrix->a3;
    mesh.matrix_LocalToWorld[3][0] = matrix->a4;
    // asign by column 1
    mesh.matrix_LocalToWorld[0][1] = matrix->b1;
    mesh.matrix_LocalToWorld[1][1] = matrix->b2;
    mesh.matrix_LocalToWorld[2][1] = matrix->b3;
    mesh.matrix_LocalToWorld[3][1] = matrix->b4;
    // asign by column 2
    mesh.matrix_LocalToWorld[0][2] = matrix->c1;
    mesh.matrix_LocalToWorld[1][2] = matrix->c2;
    mesh.matrix_LocalToWorld[2][2] = matrix->c3;
    mesh.matrix_LocalToWorld[3][2] = matrix->c4;
    // asign by column 3
    mesh.matrix_LocalToWorld[0][3] = matrix->d1;
    mesh.matrix_LocalToWorld[1][3] = matrix->d2;
    mesh.matrix_LocalToWorld[2][3] = matrix->d3;
    mesh.matrix_LocalToWorld[3][3] = matrix->d4;
}

glm::mat4 model::get_Matrix_LocalToWorld(const mesh& mesh) const
{
    return this->object::get_Matrix_LocalToWorld() * mesh.matrix_LocalToWorld;
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
