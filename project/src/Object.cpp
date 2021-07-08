/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-07-30 00:59:08
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-09 01:01:11
 */
#include "Object.h"
#include <cstdlib>

namespace DTLib
{

void* Object::operator new (std::size_t size) throw()
{
    return malloc(size);
}

void Object::operator delete (void* p)
{
    free(p);
}

void* Object::operator new[] (std::size_t size) throw()
{
    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

bool Object::operator == (const Object& obj)
{
    return (this == &obj);
}

bool Object::operator != (const Object& obj)
{
    return (this != &obj);
}

Object::~Object()
{
}

}

