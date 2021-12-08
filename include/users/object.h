#pragma once
#ifndef OBJECT_H
#define OBJECT_H
#include "users/transform.h"


class object
{
public:
    transform self_Transform;
public:
    object(transform& trans);
    ~object();
};


#endif