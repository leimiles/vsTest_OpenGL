#pragma once
#ifndef OBJECT_H
#define OBJECT_H
#include "users/transform.h"


class object
{
protected:
    transform self_Transform;
public:
    object();
    ~object();
};

#endif