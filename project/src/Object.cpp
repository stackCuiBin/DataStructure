/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-07-30 00:59:08
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-06 01:26:28
 */
/*************************************************************************
 ******* File Name: Object.cpp
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Mon 29 Jul 2019 11:31:01 PM CST
 ************************************************************************/

#include "Object.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace DTLib
{

void* Object::operator new (unsigned long size) throw()
{
    return malloc(size);
}

void Object::operator delete (void* p)
{
    free(p);
}

void* Object::operator new[] (unsigned long size) throw()
{
    return malloc(size);
}

void Object::operator delete[] (void* p)
{
    free(p);
}

Object::~Object()
{
}

}

