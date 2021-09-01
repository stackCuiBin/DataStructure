/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-09-01 01:47:14
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-01 22:52:52
 */

#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace DTLib
{

enum BTNodePos {
    ANY,
    LEFT,
    RIGHT
};

template < typename T >
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }
    
    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if ( ret != NULL ) {
            ret->m_flag = true;
        }

        return ret;
    }
};

}

#endif // BTREENODE_H