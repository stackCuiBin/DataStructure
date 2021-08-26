/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-27 00:12:41
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-08-27 00:19:06
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
};

}


#endif // GTREENODE_H