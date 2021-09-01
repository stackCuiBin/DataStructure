/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-27 00:12:41
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-01 01:51:09
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
public:
    LinkList<GTreeNode<T>*> child;

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