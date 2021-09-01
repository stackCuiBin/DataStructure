/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-26 23:49:03
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-01 01:57:15
 */

#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class TreeNode : public Object
{
protected:
    bool m_flag;

    TreeNode(const TreeNode<T>&);
    TreeNode& operator = (const TreeNode<T>&);

    void* operator new (std::size_t size) throw()
    {
        return Object::operator new(size);
    }

public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template < typename T >
TreeNode<T>::~TreeNode() {}

}

#endif // TREENODE_H