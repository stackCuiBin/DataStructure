/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-02 00:00:21
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-01 00:28:29
 */
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
#include "StaticQueue.h"
#include "LinkQueue.h"
#include "DTString.h"
#include "Sort.h"
#include "GTree.h"

using namespace std;
using namespace DTLib;

int main(int argc, const char* argv[])
{
	GTree<char> gt;
	GTreeNode<char>* node = NULL;

	gt.insert('A', NULL);

	node = gt.find('A');
	gt.insert('B', node);
	gt.insert('C', node);
	gt.insert('D', node);

	node = gt.find('B');
	gt.insert('E', node);
	gt.insert('F', node);

	node = gt.find('E');
	gt.insert('K', node);
	gt.insert('L', node);

	node = gt.find('C');
	gt.insert('G', node);

	node = gt.find('D');
	gt.insert('H', node);
	gt.insert('I', node);
	gt.insert('J', node);

	node = gt.find('H');
	gt.insert('M', node);

	// gt.remove('D');
	
	// const char* cstr = "KLFGMIJ";
	// for ( int i = 0; i < 7; i++ ) {
	// 	TreeNode<char>* nodePrint = gt.find(cstr[i]);

	// 	while ( nodePrint != NULL ) {
	// 		cout << nodePrint->value << " ";
	// 		nodePrint = nodePrint->parent;
	// 	}

	// 	cout << endl;
	// }

	for ( gt.begin(); !gt.end(); gt.next() ) {
		cout << gt.current() << endl;
	}

	cout << "count is " << gt.count() << endl;
	cout << "height is " << gt.height() << endl;
	cout << "degree is " << gt.degree() << endl;

    return 0;
}
