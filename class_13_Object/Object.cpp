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
    cout << "operator new : " << size << endl;

    return malloc(size);
}

void Object::operator delete (void* p)
{
    cout << "operator delete : " << p << endl;

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

