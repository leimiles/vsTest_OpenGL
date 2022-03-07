#include "users/mrp.h"

mrp::mrp(cam& camera)
{
    this->camera = &camera;
    this->model_View_Mode = 0;
    this->quad_View_Mode = 0;
}

mrp::~mrp()
{
}

// set(clear) color buffer with specified color
void mrp::clear_Buffer() const
{
    // set clear color  value
    glClearColor(0.21f, 0.35f, 0.35f, 1.0f);
    // clear color buffer with the set of clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// release everything
void mrp::release_Resource()
{
    //glDeleteVertexArrays(1, &mrp::current_VAO);
    //glDeleteBuffers(1, &mrp::current_VBO);
    //glDeleteBuffers(1, &mrp::current_EBO);
}

// set draw mode, GL_TRIANGLES, GL_LINE
void mrp::set_Draw_Mode(unsigned int draw_Mode)
{
    switch (draw_Mode)
    {
    case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case 3:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    default:
        break;
    }

}


void mrp::set_Model_View_Mode(unsigned int mode)
{
    this->model_View_Mode = (mode + 2) % 2;
}

void mrp::set_Quad_View_Mode(unsigned int mode)
{
    //this->quad_View_Mode = (mode + material::current_Materials.size()) % material::current_Materials.size();
}

// get max supported attribute
int mrp::get_MaxVertex_Attributes()
{
    int numberOfAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);
    return numberOfAttributes;
}

void mrp::draw_Model(const model& mdl, bool isDepth_Test)
{
    if (mdl.submeshes.size() == 0) {
        return;
    }
    for (unsigned int i = 0; i < mdl.submeshes.size(); i++)
    {

        draw_Mesh(mdl.submeshes[i], mdl.submeshes[i].material, isDepth_Test, mdl.get_Matrix_LocalToWorld(mdl.submeshes[i]));

    }

}

void mrp::draw_Mesh(const mesh& mesh, const material* material, bool isDepth_Test, glm::mat4 localToWorld) const
{
    if (material == nullptr)
    {
        //std::cout << "submesh index " << i << " has no material assigned, skip." << std::endl;
        return;
    }
    if (isDepth_Test)
    {
        glEnable(GL_DEPTH_TEST);
    }
    material->active();

    glm::mat4 matrix_Eye = camera->get_Matrix_Eye_Improved();
    glm::mat4 matrix_ViewToPerspectiveProjection = camera->get_Matrix_PerspectiveProjection();
    glm::mat4 mvp = matrix_ViewToPerspectiveProjection * matrix_Eye * localToWorld;

    // set shader global variables
    material->set_Matrix_MVP(mvp);
    material->set_Matrix_LocalToWorld(localToWorld);
    material->set_Matrix_Eye(matrix_Eye);
    material->set_Matrix_ViewToPerspectiveProjection(matrix_ViewToPerspectiveProjection);

    if (this->model_View_Mode == 0)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        material->use_Textures();
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        material->release_Textures();
    }
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.vertex_Elements.size(), GL_UNSIGNED_INT, 0);
    material->release_Textures();

}

void mrp::draw_Mesh(const mesh& mesh, std::vector<material*> materials, bool isDepth_Test, glm::mat4 localToWorld) const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    draw_Mesh(mesh, materials[this->quad_View_Mode], isDepth_Test, localToWorld);
}

