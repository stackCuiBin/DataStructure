/*************************************************************************
 ******* File Name: main.cpp
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Tue 30 Jul 2019 01:00:37 AM CST
 ************************************************************************/

#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "StaticList.h"
#include "DynamicList.h"

using namespace std;
using namespace DTLib;

int main(int argc, const char* argv[])
{
	cout << "SmartPointer test begin ..." << endl;
    SmartPointer<int>* sp = new SmartPointer<int>();

    delete sp;
	cout << "SmartPointer test end" << endl << endl;

	cout << "Exception test begin ..." << endl;
    InvalidOperationException* e = new InvalidOperationException(0);

    delete e;
	cout << "Exception test end" << endl << endl;

	cout << "StaticList test begin ..." << endl;
	StaticList<int, 5> sl;
	for(int i = 0; i < sl.capacity(); i++)
	{
		sl.insert(0, i);
	}
	for(int i = 0; i < sl.length(); i++)
	{
		cout << sl[i] << endl;
	}
	try
	{
		sl[5] = 5;
	}
	catch(const Exception& e)
	{
		cout << e.message() << endl;
		cout << e.location() << endl;
	}
	cout << "StaticList test end" << endl << endl;

	cout << "DynamicList test begin ..." << endl;
	DynamicList<int> dl(5);
	for(int i = 0; i < dl.capacity(); i++)
	{
		dl.insert(0, i);
	}
	for(int i = 0; i < dl.length(); i++)
	{
		cout << dl[i] << endl; 
	}
	try
	{
		dl[5] = 5;
	}
	catch(const Exception& e)
	{
		cout << e.message() << endl;
		cout << e.location() << endl;

		dl.resize(10);
		dl.insert(5, 10);
	}
	dl[5] = 5;
	for(int i = 0; i < dl.length(); i++)
	{
		cout << dl[i] << endl;
	}
	cout << "DynamicList test end" << endl << endl;

    return 0;
}
