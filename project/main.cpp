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
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"

using namespace std;
using namespace DTLib;

// #define SmartPointer_TEST 1
// #define Exception_TEST    1
// #define StaticList_TEST   1
// #define DynamicList_TEST  1
// #define StaticArray_TEST  1
// #define DynamicArray_TEST 1
#define LinkList_TEST     1

int main(int argc, const char* argv[])
{
#ifdef SmartPointer_TEST
	cout << "SmartPointer test begin ..." << endl;
    SmartPointer<int>* sp = new SmartPointer<int>();

    delete sp;
	cout << "SmartPointer test end" << endl << endl;
#endif
#ifdef Exception_TEST
	cout << "Exception test begin ..." << endl;
    InvalidOperationException* e = new InvalidOperationException(0);

    delete e;
	cout << "Exception test end" << endl << endl;
#endif

#ifdef StaticList_TEST
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
#endif

#ifdef DynamicList_TEST
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
#endif

#ifdef StaticArray_TEST
	StaticArray<int, 5> s1;
	for(int i = 0; i < s1.length(); i++)
	{
		s1[i] = i * i;
	}

	for(int i = 0; i < s1.length(); i++)
	{
		cout << s1[i] << endl;
	}

	StaticArray<int, 5> s2;
	s2 = s1;

	for(int i = 0; i < s2.length(); i++)
	{
		cout << s2[i] << endl;
	}
#endif

#ifdef DynamicArray_TEST
	DynamicArray<int> da(5);

	for(int i = 0; i < da.length(); i++)
	{
		da[i] = i*i;
	}
	for(int i = 0; i < da.length(); i++)
	{
		cout << da[i] << endl;
	}

	DynamicArray<int> da2(4);
	da2 = da;
	for(int i = 0; i < da2.length(); i++)
	{
		cout << da2[i] << endl;
	}
	da2.resize(3);
	for(int i = 0; i < da2.length(); i++)
	{
		cout << da2[i] << endl;
	}
#endif

#ifdef LinkList_TEST
	LinkList<int> ll;
	for(int i = 0; i < 5; i++)
	{
		ll.insert(i, i);
	}
	for(int i = 0; i < ll.length(); i++)
	{
		cout << ll.get(i) << endl;
	}
	ll.remove(2);
	for(int i = 0; i < ll.length(); i++) // O(n*n)
	{
		cout << ll.get(i) << endl;
	}
	for(ll.move(0); !ll.end(); ll.next())
	{
		cout << ll.current() << endl;
	}
#endif
    return 0;
}
