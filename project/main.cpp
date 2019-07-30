/*************************************************************************
 ******* File Name: main.cpp
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Tue 30 Jul 2019 01:00:37 AM CST
 ************************************************************************/

#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main(int argc, const char* argv[])
{
    SmartPointer<int>* sp = new SmartPointer<int>();

    delete sp;

    InvalidOperationException* e = new InvalidOperationException(0);

    delete e;

    return 0;
}
