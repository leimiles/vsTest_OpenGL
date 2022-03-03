#include "users/model.h"

model::model(std::string model_Full_Path)
{
    if (model_Full_Path == "")
    {
        this->current_Model_Directory = DEFAULT_MODEL_DIR;
        this->model_Name = DEFAULT_MODEL_NAME;
        this->model_Path = this->current_Model_Directory + this->model_Name;
    }
    else
    {
        std::cout << model_Full_Path << std::endl;
        int index = model_Full_Path.find_last_of('\\') + 1;
        this->model_Name = model_Full_Path.substr(index, model_Full_Path.length() - 1);
        this->current_Model_Directory = model_Full_Path.substr(0, index);
        this->model_Path = this->current_Model_Directory + this->model_Name;
    }


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
    std::cout << "\tfbx_Version:    " << model_Info.fbx_Version << std::endl;
    std::cout << "\tmodel_Name:     " << model_Info.model_Name << std::endl;
    std::cout << "\tupAxis:         " << model_Info.upAxis << "\t(0 = x, 1 = y, 2 = z) " << std::endl;
    std::cout << "\tupAxis_Sign:    " << model_Info.upAxis_Sign << std::endl;
    std::cout << "\tfrontAxis:      " << model_Info.frontAxis << std::endl;
    std::cout << "\tfrontAxis_Sign: " << model_Info.frontAxis_Sign << std::endl;
    std::cout << "\tscaleFactor:    " << model_Info.scaleFactor << std::endl;
    std::cout << "\tframeRate:      " << model_Info.frameRate << std::endl;
    std::cout << "\ttimeSpan_Start: " << model_Info.timeSpan_Start << std::endl;
    std::cout << "\ttimeSpan_Stop:  " << model_Info.timeSpan_Stop << std::endl;

    std::cout << "\thas_Material:   " << model_Info.has_Material << std::endl;
    //std::cout << "material_Names: " << info.material_Names.size() << std::endl;

    std::cout << "\thas_Textures:   " << model_Info.has_Textures << std::endl;
    //std::cout << "texture_Name:   " << info.texture_Name.size() << std::endl;

    std::cout << "\thas_Animation:  " << model_Info.has_Animation << std::endl;
    //std::cout << "animation_Names:" << info.animation_Names.size() << std::endl;

    std::cout << "\thas_Mesh:       " << model_Info.has_Mesh << std::endl;
    //std::cout << "\tmesh_Infos:   " << model_Infos.mesh_Infos.size() << std::endl;
    for (int i = 0; i < model_Info.mesh_Infos.size(); i++)
    {
        std::cout << "\t\tmesh_Name: " << model_Info.mesh_Infos[i].mesh_Name << " | ";
        std::cout << "hard vertices: " << model_Info.mesh_Infos[i].vertices_Count << " | ";
        std::cout << "triangle faces: " << model_Info.mesh_Infos[i].faces_Count << " | ";
        std::cout << "has_Normal: " << model_Info.mesh_Infos[i].has_Normals << " | ";
        std::cout << "has_Tangent: " << model_Info.mesh_Infos[i].has_TangentsAndBitangents << " | ";
        std::cout << "has_UVSets: " << model_Info.mesh_Infos[i].has_UVSets << " | ";
        std::cout << "has_BoneWeights: " << model_Info.mesh_Infos[i].has_BoneWeights << " | ";
        std::cout << "has_VertexColor: " << model_Info.mesh_Infos[i].has_VertexColorSets << std::endl;
    }

    std::cout << "\thas_Camera:     " << model_Info.has_Camera << std::endl;
    //std::cout << "camera_Names:   " << info.camera_Names.size() << std::endl;

    std::cout << "\thas_Light:      " << model_Info.has_Light << std::endl;
    //std::cout << "light_Names:    " << info.light_Names.size() << std::endl;

}

void model::fill_Model_Info(const aiScene* sceneNode)
{
    this->model_Info.model_Name = this->model_Name;
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
                    this->model_Info.fbx_Version = type_String.C_Str();
                }
            }
            else if (sceneNode->mMetaData->Get(i, type_Vector3D))
            {

            }
            else if (sceneNode->mMetaData->Get(i, type_Int32))
            {
                if (property_Name == "UpAxis")
                {
                    this->model_Info.upAxis = type_Int32;
                }
                if (property_Name == "UpAxisSign")
                {
                    this->model_Info.upAxis_Sign = type_Int32;
                }
                if (property_Name == "FrontAxis")
                {
                    this->model_Info.frontAxis = type_Int32;
                }
                if (property_Name == "FrontAxisSign")
                {
                    this->model_Info.frontAxis_Sign = type_Int32;
                }
                if (property_Name == "FrameRate")
                {
                    this->model_Info.frameRate = type_Int32;
                }
            }
            else if (sceneNode->mMetaData->Get(i, type_Int))
            {

            }
            else if (sceneNode->mMetaData->Get(i, type_Unit64))
            {
                if (property_Name == "TimeSpanStart")
                {
                    this->model_Info.timeSpan_Start = type_Unit64;
                }
                if (property_Name == "TimeSpanStop")
                {
                    this->model_Info.timeSpan_Stop = type_Unit64;
                }
            }
            else if (sceneNode->mMetaData->Get(i, type_real))
            {
                if (property_Name == "UnitScaleFactor")
                {
                    this->model_Info.scaleFactor = type_real;
                }
            }

        }
    }
    this->model_Info.has_Animation = sceneNode->mNumAnimations;
    this->model_Info.has_Textures = sceneNode->mNumTextures;
    this->model_Info.has_Material = sceneNode->mNumMaterials;
    this->model_Info.has_Mesh = sceneNode->mNumMeshes;
    this->model_Info.has_Camera = sceneNode->mNumCameras;
    this->model_Info.has_Light = sceneNode->mNumLights;
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
    mesh_Info mesh_Info;
    mesh_Info.mesh_Name = meshNode->mName.C_Str();
    mesh_Info.has_BoneWeights = meshNode->mNumBones;
    mesh_Info.has_Normals = 0;
    mesh_Info.has_TangentsAndBitangents = 0;
    mesh_Info.has_UVSets = 0;
    mesh_Info.has_VertexColorSets = 0;

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
            mesh_Info.has_Normals = 1;
            vtx_Attri.normal_Obj.x = meshNode->mNormals[i].x;
            vtx_Attri.normal_Obj.y = meshNode->mNormals[i].y;
            vtx_Attri.normal_Obj.z = meshNode->mNormals[i].z;
        }

        if (meshNode->mTextureCoords[0])
        {
            mesh_Info.has_UVSets = meshNode->GetNumUVChannels();
            vtx_Attri.texcoords.x = meshNode->mTextureCoords[0][i].x;
            vtx_Attri.texcoords.y = meshNode->mTextureCoords[0][i].y;
        }
        else
        {
            vtx_Attri.texcoords.x = 0.0f;
            vtx_Attri.texcoords.y = 0.0f;
        }

        if (meshNode->HasVertexColors(0))
        {
            mesh_Info.has_VertexColorSets = meshNode->GetNumColorChannels();
        }

        if (meshNode->HasTangentsAndBitangents())
        {
            mesh_Info.has_TangentsAndBitangents = 1;
            vtx_Attri.tangent_Obj.x = meshNode->mTangents[i].x;
            vtx_Attri.tangent_Obj.y = meshNode->mTangents[i].y;
            vtx_Attri.tangent_Obj.z = meshNode->mTangents[i].z;

            vtx_Attri.bitangent_Obj.x = meshNode->mBitangents[i].x;
            vtx_Attri.bitangent_Obj.y = meshNode->mBitangents[i].y;
            vtx_Attri.bitangent_Obj.z = meshNode->mBitangents[i].z;

        }
        vertex_Attributes.push_back(vtx_Attri);
    }
    mesh_Info.vertices_Count = vertex_Attributes.size();

    for (unsigned int i = 0; i < meshNode->mNumFaces; i++)
    {
        aiFace face = meshNode->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            vertex_Elements.push_back(face.mIndices[j]);
        }

    }
    mesh_Info.faces_Count = meshNode->mNumFaces;

    extract_BoneWeightForVertices(vertex_Attributes, meshNode, sceneNode);

    mesh mesh(vertex_Attributes, vertex_Elements);
    mesh.mesh_Name = meshNode->mName.C_Str();
    mesh.material_ID = meshNode->mMaterialIndex;

    this->model_Info.mesh_Infos.push_back(mesh_Info);

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

    texture::textures_Directory = this->current_Model_Directory == DEFAULT_MODEL_DIR ? DEFAULT_TEXTURE_DIR : this->current_Model_Directory;
    // find diffuse map
    std::string diffuse_Regex_String = "^" + meshName + "_[D,d]\\.(jpg|png|tga|psd)$";
    std::regex diffuseMap_Regex(diffuse_Regex_String);
    std::string normal_Regex_String = "^" + meshName + "_[N,n]\\.(jpg|png|tga|psd)$";
    std::regex normalMap_Regex(normal_Regex_String);
    std::string metallic_Regex_String = "^" + meshName + "_[M,m]\\.(jpg|png|tga|psd)$";
    std::regex metallicMap_Regex(metallic_Regex_String);
    std::string roughness_Regex_String = "^" + meshName + "_[R,r]\\.(jpg|png|tga|psd)$";
    std::regex roughtnessMap_Regex(roughness_Regex_String);

    for (const auto& entry : std::filesystem::directory_iterator(texture::textures_Directory))
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
