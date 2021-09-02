/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-02 00:00:21
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-03 01:57:14
 */
/*************************************************************************
 ******* File Name: main.cpp
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Tue 30 Jul 2019 01:00:37 AM CST
 ************************************************************************/

#include <iostream>
#include "GTree.h"
#include "BTree.h"

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

	for ( gt.begin(); !gt.end(); gt.next() ) {
		cout << gt.current() << endl;
	}

	cout << "count is " << gt.count() << endl;
	cout << "height is " << gt.height() << endl;
	cout << "degree is " << gt.degree() << endl;
	cout << "###############" << endl;

	BTree<int> bt;
	BTreeNode<int>* n;

	bt.insert(1, NULL);

	n = bt.find(1);
	bt.insert(2, n);
	bt.insert(3, n);

	n = bt.find(2);
	bt.insert(4, n);
	bt.insert(5, n);

	n = bt.find(4);
	bt.insert(8, n);
	bt.insert(9, n);

	n = bt.find(5);
	bt.insert(10, n);

	n = bt.find(3);
	bt.insert(6, n);
	bt.insert(7, n);

	SharedPointer< BTree<int> > sbt = bt.clone();
	
	cout << "original" << endl;
	for ( bt.begin(); !bt.end(); bt.next() ) {
		cout << bt.current() << endl;
	}
	cout << endl;

	cout << "clone:" << endl;
	for ( sbt->begin(); !sbt->end(); sbt->next() ) {
		cout << sbt->current() << endl;
	}
	cout << endl;

	cout << "bt == *sbt : " << (bt == *sbt) << endl; 

	cout << "count is " << bt.count() << endl;
	cout << "height is " << bt.height() << endl;
	cout << "degree is " << bt.degree() << endl;

	BTree<int> bt1;
	SharedPointer< BTree<int> > sbt1;

	bt1.insert(0, NULL);

	n = bt1.find(0);
	bt1.insert(6, n);
	bt1.insert(2, n);

	n = bt1.find(2);
	bt1.insert(7, n);
	bt1.insert(8, n);

	sbt1 = bt.add(bt1);

	n = bt.thread(LevelOrder);

	while ( n != NULL ) {
		cout << n->value << " ";
		n = n->right;
	}
	cout << endl;

	SharedPointer< Array<int> > sp = NULL;

	// sp = sbt1->traversal(PreOrder);
	sp = sbt1->traversal(LevelOrder);

	for( int i = 0; i < sp->length(); i++ )
	{
		cout << (*sp)[i] << " ";
	}
	cout << endl;

    return 0;
}
