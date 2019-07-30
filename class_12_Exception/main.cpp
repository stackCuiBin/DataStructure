/*************************************************************************
 ******* File Name: main.cpp
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Sun 28 Jul 2019 11:53:48 AM CST
 ************************************************************************/

#include <iostream>
#include "Exception.h"

using namespace std;
using namespace DTLib;

int main(int argc, const char* argv[])
{
    try
    {
        // throw Exception("test", __FILE__, __LINE__);
        
        THROW_EXCEPTION(ArithmeticException, "test");
    }
    catch(const ArithmeticException& e)
    {
        cout << "catch(const ArithmeticException& e)" << endl;

        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch(const Exception& e)
    {
        cout << "catch(const Exception& e)" << endl;

        cout << e.message() << endl;
        cout << e.location() << endl;
    }


    return 0;
}
