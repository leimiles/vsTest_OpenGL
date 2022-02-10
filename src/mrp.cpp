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

void mrp::set_RenderingData(vao_Mode mode, const geometry& geo)
{
    mrp::current_VAO = 0;
    glGenVertexArrays(1, &mrp::current_VAO);
    glBindVertexArray(mrp::current_VAO);

    mrp::current_VBO = 0;
    glGenBuffers(1, &mrp::current_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mrp::current_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * geo.VERTEX_ATTRIBUTES_SIZE, geo.VERTEX_ATTRIBUTES, GL_STATIC_DRAW);

    if (geo.VERTEX_ELEMENTS_SIZE > 0) {
        mrp::current_EBO = 0;
        glGenBuffers(1, &mrp::current_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mrp::current_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * geo.VERTEX_ELEMENTS_SIZE, geo.VERTEX_ELEMENTS, GL_STATIC_DRAW);
    }

    switch (mode)
    {
    case vao_0Pos3:
        break;
    case vao_0Pos3_1Col3_2Texcoord2:
        mrp::set_VAO_0Pos3_1Col3_2Texcoord2(geo);
        break;
    case vao_0Pos3_2Texcoord2:
        mrp::set_VAO_0Pos3_2Texcoord2(geo);
        break;
    case vao_0Pos3_1Normal3_2Texcoord2:
        mrp::set_VAO_0Pos3_1Normal3_2Texcoord2(geo);
        break;
    default:
        break;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void mrp::draw_Geometry(const geometry& geo, bool isDepth_Test)
{
    if (geo.VERTEX_ATTRIBUTES_SIZE == 0)
    {
        std::cout << "nothing to draw\n" << std::endl;
        return;
    }
    if (geo.VERTEX_ELEMENTS_SIZE > 0)
    {
        glBindVertexArray(mrp::current_VAO);
        glDrawElements(GL_TRIANGLES, geo.VERTEX_ELEMENTS_SIZE, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glBindVertexArray(mrp::current_VAO);
        glDrawArrays(GL_TRIANGLES, 0, geo.VERTEX_ATTRIBUTES_SIZE / geo.VERTEX_ATTRIBUTES_STRIDE);
    }

    if (isDepth_Test)
    {
        glEnable(GL_DEPTH_TEST);
    }
}

void mrp::set_RenderingData(const model& mdl)
{

}

void mrp::draw_Model(const model& mdl, bool isDepth_Test)
{
    if (mdl.submeshes.size() == 0) {
        //std::cout << "no mesh to draw" << std::endl;
        return;
    }
    if (isDepth_Test)
    {
        glEnable(GL_DEPTH_TEST);
    }
    for (unsigned int i = 0; i < mdl.submeshes.size(); i++)
    {
        //std::cout << "draw a mesh" << std::endl;
        // how to draw submeshes?
        glBindVertexArray(mdl.submeshes[i].vao);
        glDrawElements(GL_TRIANGLES, mdl.submeshes[i].vertex_Elements.size(), GL_UNSIGNED_INT, 0);

    }

}

void mrp::draw_Model_WithMaterial(const model& mdl, bool isDepth_Test)
{
    if (mdl.submeshes.size() == 0) {
        //std::cout << "no mesh to draw" << std::endl;
        return;
    }
    if (isDepth_Test)
    {
        glEnable(GL_DEPTH_TEST);
    }
    for (unsigned int i = 0; i < mdl.submeshes.size(); i++)
    {
        //std::cout << "draw a mesh" << std::endl;
        // how to draw submeshes?
        if (mdl.submeshes[i].material == nullptr)
        {
            //std::cout << "submesh index " << i << " has no material assigned, skip." << std::endl;
            continue;
        }
        mdl.submeshes[i].material->active();
        glm::mat4 mvp = camera->get_Matrix_PerspectiveProjection() * camera->get_Matrix_Eye_Improved() * mdl.get_Matrix_LocalToWorld();
        mdl.submeshes[i].material->set_MVP(mvp);
        if (this->drawMode != 1)
        {
            mdl.submeshes[i].material->release_Textures();
        }
        else
        {
            mdl.submeshes[i].material->use_Textures();
        }
        glBindVertexArray(mdl.submeshes[i].vao);
        glDrawElements(GL_TRIANGLES, mdl.submeshes[i].vertex_Elements.size(), GL_UNSIGNED_INT, 0);
        mdl.submeshes[i].material->release_Textures();
    }

}

// 3 floats for position, 3 floats for color, 2 floats for texcoord
void mrp::set_VAO_0Pos3_1Col3_2Texcoord2(const geometry& geo)
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * geo.VERTEX_ATTRIBUTES_STRIDE, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * geo.VERTEX_ATTRIBUTES_STRIDE, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * geo.VERTEX_ATTRIBUTES_STRIDE, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
}

void mrp::set_VAO_0Pos3_2Texcoord2(const geometry& geo)
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * geo.VERTEX_ATTRIBUTES_STRIDE, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * geo.VERTEX_ATTRIBUTES_STRIDE, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(2);
}

void mrp::set_VAO_0Pos3_1Normal3_2Texcoord2(const geometry& geo)
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * geo.VERTEX_ATTRIBUTES_STRIDE, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * geo.VERTEX_ATTRIBUTES_STRIDE, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * geo.VERTEX_ATTRIBUTES_STRIDE, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
}
