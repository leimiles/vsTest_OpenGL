#include "users/object.h"

object::object()
{
}

object::~object()
{

}

void object::set_Translate(float x, float y, float z)
{
    self_Transform.set_Translate(x, y, z);
}

void object::set_Rotate(float degrees, float x, float y, float z)
{
    self_Transform.set_Rotate(degrees, x, y, z);
}

void object::set_Scale(float x, float y, float z)
{
    self_Transform.set_Scale(x, y, z);
}

glm::mat4 object::get_Matrix_LocalToWorld() const
{
    return self_Transform.get_Matrix_LocalToWorld();
}

glm::mat4 object::get_Matrix_WorldToLocal() const
{
    return self_Transform.get_Matrix_WorldToLocal();
}