/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-27 00:12:41
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-01 00:25:50
 */

#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "LinkList.h"

namespace DTLib
{

template < typename T >
class GTreeNode : public TreeNode<T>
{
protected:
    bool m_flag;

    GTreeNode(const GTreeNode<T>&);
    GTreeNode& operator = (const GTreeNode<T>&);

    void* operator new (std::size_t size) throw()
    {
        return Object::operator new(size);
    }

public:
    LinkList<GTreeNode<T>*> child;

    GTreeNode()
    {
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if ( ret != NULL ) {
            ret->m_flag = true;
        }

        return ret;
    }
};

}


#endif // GTREENODE_H