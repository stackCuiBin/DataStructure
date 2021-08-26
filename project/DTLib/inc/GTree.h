/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-27 00:19:57
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-08-27 01:15:16
 */

#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "LinkQueue.h"

namespace DTLib
{

template < typename T >
class GTree : public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;

    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if ( node != NULL ) {
            if ( node->value == value ) {
                return node;
            } else {
                for ( node->child.move(0); (!node->child.end()) && (ret == NULL); node->child.next() ) {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, const GTreeNode<T>* obj ) const
    {
        GTreeNode<T>* ret = NULL;

        if ( node == obj ) {
            return node;
        } else {
            if ( node != NULL ) {
                for ( node->child.move(0); (!node->child.end()) && (ret == NULL); node->child.next() ) {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        return NULL;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        return NULL;
    }
    
    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return 0;
    }

    int count() const
    {
        return 0;
    }

    int height() const
    {
        return 0;
    }

    void clear()
    {
        this->m_root = NULL;
    }

    bool begin()
    {
        bool ret = true;

        return ret;
    }

    bool end()
    {
        bool ret = true;

        return ret;
    }

    bool next()
    {
        bool ret = true;

        return ret;
    }

    T current()
    {
        T ret;

        return ret;
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H