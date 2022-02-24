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

    fill_Model_Info(sceneNode);

    extract_Materials(sceneNode);

    process_Node(sceneNode->mRootNode, sceneNode);

    show_Model_Info();
}

void model::show_Model_Info()
{
    std::cout << "\nFBX File Info:\n";
    std::cout << "fbx_Version:    \t" << info.fbx_Version << std::endl;
    std::cout << "model_Name:     \t" << info.model_Name << std::endl;
    std::cout << "upAxis:         \t" << info.upAxis << std::endl;
    std::cout << "upAxis_Sign:    \t" << info.upAxis_Sign << std::endl;
    std::cout << "frontAxis:      \t" << info.frontAxis << std::endl;
    std::cout << "frontAxis_Sign: \t" << info.frontAxis_Sign << std::endl;
    std::cout << "scaleFactor:    \t" << info.scaleFactor << std::endl;
    std::cout << "frameRate:      \t" << info.frameRate << std::endl;
    std::cout << "timeSpan_Start: \t" << info.timeSpan_Start << std::endl;
    std::cout << "timeSpan_Stop:  \t" << info.timeSpan_Stop << std::endl;

    std::cout << "has_Material:   \t" << info.has_Material << std::endl;
    //std::cout << "material_Names: \t" << info.material_Names.size() << std::endl;

    std::cout << "has_Textures:   \t" << info.has_Textures << std::endl;
    //std::cout << "texture_Name:   \t" << info.texture_Name.size() << std::endl;

    std::cout << "has_Animation:  \t" << info.has_Animation << std::endl;
    //std::cout << "animation_Names:\t" << info.animation_Names.size() << std::endl;

    std::cout << "has_Mesh:       \t" << info.has_Mesh << std::endl;
    //std::cout << "mesh_Names:     \t" << info.mesh_Names.size() << std::endl;

    std::cout << "has_Camera:     \t" << info.has_Camera << std::endl;
    //std::cout << "camera_Names:   \t" << info.camera_Names.size() << std::endl;

    std::cout << "has_Light:      \t" << info.has_Light << std::endl;
    //std::cout << "light_Names:    \t" << info.light_Names.size() << std::endl;

}

void model::fill_Model_Info(const aiScene* sceneNode)
{
    info.model_Name = this->model_Name;
    if (sceneNode->mMetaData->mNumProperties > 0)
    {
        for (int i = 0; i < sceneNode->mMetaData->mNumProperties; i++)
        {
            aiString type_String;
            aiVector3D type_Vector3D;
            ai_int32 type_Int32;
            ai_int type_Int;
            ai_real type_real;
            // no conversion
            uint64_t type_Unit64;

            std::string property_Name = (sceneNode->mMetaData->mKeys + i)->C_Str();
            if (sceneNode->mMetaData->Get(i, type_String))
            {
                if (property_Name == "SourceAsset_Generator")
                {
                    info.fbx_Version = type_String.C_Str();
                }
            }
            else if (sceneNode->mMetaData->Get(i, type_Vector3D))
            {

            }
            else if (sceneNode->mMetaData->Get(i, type_Int32))
            {
                if (property_Name == "UpAxis")
                {
                    info.upAxis = type_Int32;
                }
                if (property_Name == "UpAxisSign")
                {
                    info.upAxis_Sign = type_Int32;
                }
                if (property_Name == "FrontAxis")
                {
                    info.frontAxis = type_Int32;
                }
                if (property_Name == "FrontAxisSign")
                {
                    info.frontAxis_Sign = type_Int32;
                }
                if (property_Name == "FrameRate")
                {
                    info.frameRate = type_Int32;
                }
            }
            else if (sceneNode->mMetaData->Get(i, type_Int))
            {

            }
            else if (sceneNode->mMetaData->Get(i, type_Unit64))
            {
                if (property_Name == "TimeSpanStart")
                {
                    info.timeSpan_Start = type_Unit64;
                }
                if (property_Name == "TimeSpanStop")
                {
                    info.timeSpan_Stop = type_Unit64;
                }
            }
            else if (sceneNode->mMetaData->Get(i, type_real))
            {
                if (property_Name == "UnitScaleFactor")
                {
                    info.scaleFactor = type_real;
                }
            }

        }
    }
    info.has_Animation = sceneNode->mNumAnimations;
    info.has_Textures = sceneNode->mNumTextures;
    info.has_Material = sceneNode->mNumMaterials;
    info.has_Mesh = sceneNode->mNumMeshes;
    info.has_Camera = sceneNode->mNumCameras;
    info.has_Light = sceneNode->mNumLights;
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
            // no conversion
            uint64_t type_Unit64;

            std::cout << "\tproperty key:[" << (sceneNode->mMetaData->mKeys + i)->C_Str() << "]\t|\tproperty value:[";
            if (sceneNode->mMetaData->Get(i, type_String))
            {
                std::cout << type_String.C_Str() << "]" << " | " << "string" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_Vector3D))
            {
                std::cout << type_Vector3D.x << ", " << type_Vector3D.y << ", " << type_Vector3D.z << "]" << " | " << "vec3" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_Int32))
            {
                std::cout << type_Int32 << "]" << " | " << "int32" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_Int))
            {
                std::cout << type_Int << "]" << " | " << "int" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_Unit64))
            {
                std::cout << type_Unit64 << "]" << " | " << "uint64" << std::endl;
            }
            else if (sceneNode->mMetaData->Get(i, type_real))
            {
                std::cout << type_real << "]" << " | " << "real" << std::endl;
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
    final_Transform = node->mTransformation * final_Transform;
    //std::cout << "Transform after multiplied by : " << node->mName.C_Str() << "\n";
    //print_AiMatrix(final_Transform);
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
        mat->id = i;
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
    mesh.mesh_Name = meshNode->mName.C_Str();
    mesh.material_ID = meshNode->mMaterialIndex;

    fill_Material(mesh);

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


void model::fill_Textures_Chicken01(material* material, std::string& meshName)
{

    texture::textures_Directory = current_Model_Directory;
    // find diffuse map
    std::string diffuse_Regex_String = "^" + meshName + "_[D,d]\\.(jpg|png|tga|psd)$";
    std::regex diffuseMap_Regex(diffuse_Regex_String);
    std::string normal_Regex_String = "^" + meshName + "_[N,n]\\.(jpg|png|tga|psd)$";
    std::regex normalMap_Regex(normal_Regex_String);
    std::string metallic_Regex_String = "^" + meshName + "_[M,m]\\.(jpg|png|tga|psd)$";
    std::regex metallicMap_Regex(metallic_Regex_String);
    std::string roughness_Regex_String = "^" + meshName + "_[R,r]\\.(jpg|png|tga|psd)$";
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

void model::fill_Material(mesh& mesh)
{
    if (shaderV2::current_Shader != nullptr)
    {
        if (mesh.material == nullptr)
        {
            mesh.material = material::current_Materials[mesh.material_ID];
            std::cout << "mesh [" << mesh.mesh_Name << "] using material_" << mesh.material_ID << " [" << mesh.material->material_Name << "]" << std::endl;
            if (mesh.material->get_TexturesCount() == 0)
            {
                fill_Textures_Chicken01(mesh.material, mesh.mesh_Name);
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
