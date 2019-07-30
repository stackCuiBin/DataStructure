/*************************************************************************
 ******* File Name: main.cpp
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Mon 29 Jul 2019 11:47:00 PM CST
 ************************************************************************/

#include <iostream>
#include "Object.h"

using namespace std;
using namespace DTLib;

class Test : public Object
{
public:
    int i;
    int j;
};

class Child : public Test
{
public:
    int k;
};

int main(int argc, const char* argv[])
{
    Object* obj1 = new Test();
    Object* obj2 = new Child();

    cout << "obj1 = " << obj1 << endl;
    cout << "obj2 = " << obj2 << endl;

    delete obj1;
    delete obj2;

    return 0;
}
