#include "users/mrp.h"

// init static members
unsigned int mrp::current_VAO;
unsigned int mrp::current_VBO;
unsigned int mrp::current_EBO;

mrp::mrp(cam& camera)
{
    this->camera = &camera;
}

mrp::~mrp()
{
}

// set(clear) color buffer with specified color
void mrp::clear_Buffer()
{
    // set clear color  value
    glClearColor(0.21f, 0.35f, 0.35f, 1.0f);
    // clear color buffer with the set of clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// release everything
void mrp::release_Resource()
{
    glDeleteVertexArrays(1, &mrp::current_VAO);
    glDeleteBuffers(1, &mrp::current_VBO);
    glDeleteBuffers(1, &mrp::current_EBO);
}

// set draw mode, GL_TRIANGLES, GL_LINE
void mrp::set_DrawMode(unsigned int drawMode)
{
    this->drawMode = drawMode;
    switch (drawMode)
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

// get max supported attribute
int mrp::get_MaxVertex_Attributes()
{
    int numberOfAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);
    return numberOfAttributes;
}

void mrp::draw_Model_WithMaterial(const model& mdl, bool isDepth_Test)
{
    if (mdl.submeshes.size() == 0) {
        return;
    }
    for (unsigned int i = 0; i < mdl.submeshes.size(); i++)
    {

        draw_Mesh(mdl.submeshes[i], mdl.submeshes[i].material, isDepth_Test, mdl.get_Matrix_LocalToWorld());

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
    glm::mat4 mvp = camera->get_Matrix_PerspectiveProjection() * camera->get_Matrix_Eye_Improved() * localToWorld;
    material->set_MVP(mvp);
    if (this->drawMode != 1)
    {
        material->release_Textures();
    }
    else
    {
        material->use_Textures();
    }
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.vertex_Elements.size(), GL_UNSIGNED_INT, 0);
    material->release_Textures();

}

