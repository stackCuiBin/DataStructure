/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-26 23:49:03
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-08-26 23:52:28
 */

#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class TreeNode : public Object
{
public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        parent = NULL;
    }

    virtual ~TreeNode() = 0;
};

template < typename T >
TreeNode<T>::~TreeNode() {}

}

#endif // TREENODE_H