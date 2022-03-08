#include "users/mrp.h"

mrp::mrp(cam& camera)
{
    this->camera = &camera;
    this->init();
}

mrp::~mrp()
{
    delete this->screen_Mesh;
    delete this->shader_NDC;
    delete this->material_NDC;
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

// get max supported attribute
int mrp::get_MaxVertex_Attributes()
{
    int numberOfAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);
    return numberOfAttributes;
}

void mrp::draw_Model(const model& mdl, bool isDepth_Test, unsigned int fill_Mode)
{
    switch (fill_Mode)
    {
    case 0:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        for (unsigned int i = 0; i < mdl.submeshes.size(); i++)
        {

            draw_Mesh(mdl.submeshes[i], mdl.submeshes[i]->material, isDepth_Test, mdl.get_Matrix_LocalToWorld(mdl.submeshes[i]));

        }
        break;
    case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for (unsigned int i = 0; i < mdl.submeshes.size(); i++)
        {

            if (this->wireframe_Material)
            {
                draw_Mesh(mdl.submeshes[i], this->wireframe_Material, isDepth_Test, mdl.get_Matrix_LocalToWorld(mdl.submeshes[i]));
            }

        }
        break;
    case 2:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        for (unsigned int i = 0; i < mdl.submeshes.size(); i++)
        {

            draw_Mesh(mdl.submeshes[i], mdl.submeshes[i]->material, isDepth_Test, mdl.get_Matrix_LocalToWorld(mdl.submeshes[i]));

        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for (unsigned int i = 0; i < mdl.submeshes.size(); i++)
        {
            if (this->wireframe_Material)
            {
                draw_Mesh(mdl.submeshes[i], this->wireframe_Material, isDepth_Test, mdl.get_Matrix_LocalToWorld(mdl.submeshes[i]));
            }
        }
        break;
    default:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    }

}

void mrp::draw_Mesh(const mesh* mesh, const material* material, bool isDepth_Test, glm::mat4 localToWorld) const
{
    if (material == nullptr)
    {
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

    material->use_Textures();

    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->vertex_Elements.size(), GL_UNSIGNED_INT, 0);
    material->release_Textures();

}

void mrp::draw_SplitLine() const
{
    draw_Mesh(this->screen_Mesh, this->material_NDC, false, transform::mat_Identity);
}

void mrp::init()
{
    this->screen_Mesh = new mesh_NDC(6, 18, data::help_SplitLine_Attributes, 3, data::help_SplitLine_Indices);
    this->shader_NDC = new shaderV2(data::shader_NDC_Vert, data::shader_NDC_Frag, true, "ndc");
    this->material_NDC = new material(*this->shader_NDC);
}

