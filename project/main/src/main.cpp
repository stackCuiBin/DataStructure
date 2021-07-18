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
#include "StaticLinkList.h"
#include "SharedPointer.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "DualStaticLinkList.h"
#include "DualCircleList.h"
#include "StaticStack.h"
#include "LinkStack.h"

using namespace std;
using namespace DTLib;

// #define SmartPointer_TEST 1
// #define SharedPointer_TEST 1
// #define Exception_TEST    1
// #define StaticList_TEST   1
// #define DynamicList_TEST  1
// #define StaticArray_TEST  1
// #define DynamicArray_TEST 1
// #define LinkList_TEST     1
// #define StaticLinkList_TEST 1
// #define CircleList_TEST   1
// #define DualLinkList_TEST   1
// #define DualStaticLinkList_TEST   1
// #define DualCircleList_TEST   1
// #define StaticStack_TEST 1
#define LinkStack_TEST 1

#ifdef LinkStack_TEST
bool is_left(char c)
{
	return (c == '(') || (c == '{') || (c == '[') || (c == '<');
}

bool is_rigth(char c)
{
	return (c == ')') || (c == '}') || (c == ']') || (c == '>');
}

bool is_quot(char c)
{
	return (c == '\'') || (c == '\"');
}

bool is_match(char left, char right)
{
	return ( ((left == '(') && (right == ')')) ||
			 ((left == '[') && (right == ']')) ||
			 ((left == '{') && (right == '}')) ||
			 ((left == '<') && (right == '>')) ||
			 ((left == '\'') && (right == '\'')) ||
			 ((left == '\"') && (right == '\"')) );
}

bool scanf(const char* code)
{
	int ret = true;
	int i = 0;
	LinkStack<char> lstack;

	code = (code == NULL) ? "" : code;

	while( ret && code[i] != '\0' )
	{
		if ( is_left(code[i]) )
		{
			lstack.push(code[i]);
		}
		else if ( is_rigth(code[i]) )
		{
			if ( (lstack.size() > 0) && is_match(lstack.top(), code[i]) )
			{
				lstack.pop();
			}
			else
			{
				ret = false;
			}
		}
		else if ( is_quot(code[i]) )
		{
			if ( (lstack.size() == 0) || !is_match(lstack.top(), code[i]) )
			{
				lstack.push(code[i]);
			}
			else if ( is_match(lstack.top(), code[i]) )
			{
				lstack.pop();
			}
			else
			{
				ret = false;
			}
		}

		i++;
	}

	return ret && (lstack.size() == 0);
}
#endif

#ifdef CircleList_TEST
// 约瑟夫问题，
void josehus(int Total, int StartNum, int Step)
{
	CircleList<int> cl;

	for(int i = 0; i < Total; i++)
	{
		cl.insert(i);
	}

	cl.move(StartNum, Step-1);

	while(cl.length() > 0)
	{
		cl.next();

		cout << cl.current() << endl;

		cl.remove(cl.find(cl.current()));
	}
}
#endif

class Test : public Object
{
public:
	int m_value;
	Test(int value) : m_value(value)
	{ 
		cout << "Test " << m_value << endl; 
	}

	~Test() 
	{ 
		cout << "~Test " << m_value << endl;
	}
};

int main(int argc, const char* argv[])
{
#ifdef SmartPointer_TEST
    SmartPointer<Test> sp1 = new Test(1);
	SmartPointer<Test> sp2 = new Test(2);

	// sp2指向的Test2销毁, sp1指针指向NULL
	sp2 = sp1;
	cout << "sp1 " << sp1.get() << endl;
	cout << "sp2 " << sp2.get() << endl;

	cout << "&sp1 " << &sp1<< endl;
	cout << "&sp2 " << &sp2 << endl;
	//sp2先析构，Test2销毁，sp1后析构
#endif

#ifdef SharedPointer_TEST
	SharedPointer<Test> sp1 = new Test(1);
	SharedPointer<Test> sp2(sp1);
	SharedPointer<Test> sp3;

	sp3 = sp2;
	sp3->m_value = 100;

	cout << sp1->m_value << endl;
	cout << sp2->m_value << endl;
	cout << sp3->m_value << endl;

	cout << (sp1 == sp2) << endl;
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
	for(int i = 0; i < ll.length(); i++)   // O(n*n)
	{
		cout << ll.get(i) << endl;
	}
	for(ll.move(0); !ll.end(); ll.next())	// O(n)
	{
		cout << ll.current() << endl;
	}
#endif

#ifdef StaticLinkList_TEST
	StaticLinkList<int, 5> sll;

	for(int i = 0; i < 5; i++)
	{
		sll.insert(i, i);
	}
	for(sll.move(0); !sll.end(); sll.next())	// O(n)
	{
		cout << sll.current() << endl;
	}
#endif

#ifdef CircleList_TEST
	josehus(41, 1, 3);

	CircleList<int> cl;

	for(int i = 0; i < 5; i++)
	{
		cl.insert(i, i);
	}
	for(cl.move(0, 1); !cl.end(); cl.next())	// O(n)
	{
		cout << cl.current() << endl;
	}
#endif

#ifdef DualLinkList_TEST
	DualLinkList<int> dl;
	for(int i = 0; i < 5; i++)
	{
		dl.insert(0, i);
		dl.insert(0, 5);
	}
	for(dl.move(0); !dl.end(); dl.next())
	{
		cout << dl.current() << endl;
	}

	cout << "begin" << endl;

	dl.move(0);
	while( !dl.end() )
	{
		if ( dl.current() == 5 )
		{
			cout << dl.current() << endl;
			dl.remove(dl.find(dl.current()));
		}
		else
		{
			dl.next();
		}
	}

	cout << "end" << endl;

	for(dl.move(0); !dl.end(); dl.next())
	{
		cout << dl.current() << endl;
	}
#endif

#ifdef DualStaticLinkList_TEST
	DualStaticLinkList<int, 5> dsll;

	for(int i = 0; i < 5; i++)
	{
		dsll.insert(i, i);
	}
	for(dsll.move(0); !dsll.end(); dsll.next())	// O(n)
	{
		cout << dsll.current() << endl;
	}
#endif

#ifdef DualCircleList_TEST
	DualCircleList<int> dcl;

	for(int i = 0; i < 5; i++)
	{
		dcl.insert(i, i);
	}

	// 因为是循环双向链表，所以end()不会遍历结束，会无限循环
	// for(dcl.move(0, 1); !dcl.end(); dcl.next())
	// {
	// 	cout << dcl.current() << endl;
	// }
	int ret = dcl.find(10);
	cout << "ret = " << ret << endl;
	dcl.move(0);
#endif

#ifdef StaticStack_TEST
	StaticStack<int, 5> sstack;

	for(int i = 0; i < sstack.capacity(); i++)
	{
		sstack.push(i);
	}

	while( sstack.size() > 0 )
	{
		cout << sstack.top() << endl;

		sstack.pop();
	}
#endif

#ifdef LinkStack_TEST
	cout << scanf("({<>})") << endl;
	cout << scanf("<(})>") << endl;
#endif

    return 0;
}
