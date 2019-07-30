/*************************************************************************
 ******* File Name: main.cpp
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Tue 30 Jul 2019 12:36:15 AM CST
 ************************************************************************/

#include <iostream>
#include "SmartPointer.h"

using namespace std;
using namespace DTLib;

class Test
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }
};

int main(int argc, const char* argv[])
{
    SmartPointer<Test> sp = new Test();
    SmartPointer<Test> nsp;

    nsp = sp;

    cout << nsp.isNull() << endl;
    cout << sp.isNull() << endl;

    return 0;
}

/*
 * result:
 * Test()
 * 0
 * 1
 * ~Test()
 */
