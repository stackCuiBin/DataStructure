/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-07-30 00:59:08
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-08 22:26:57
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

namespace DTLib
{

class Object
{
public:
    void* operator new (std::size_t size) throw();
    void operator delete (void* p);
    void* operator new[] (std::size_t size) throw();
    void operator delete[] (void* p);
    bool operator == (const Object& obj);
    bool operator != (const Object& obj);
    virtual ~Object() = 0;
};

}

#endif
