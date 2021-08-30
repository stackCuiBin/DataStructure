/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-27 00:19:57
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-08-31 00:29:17
 */

#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "LinkQueue.h"
#include "Exception.h"

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

    void free(GTreeNode<T>* node)
    {
        if ( node != NULL ) {
            for ( node->child.move(0); !node->child.end(); node->child.next() ) {
                free(node->child.current());
            }

            // std::cout << "delete " << node->value << std::endl;
            if ( node->flag() ) {
                delete node;
            } 
        }
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if ( ret != NULL ) {
            if ( root() != node ) {
                LinkList< GTreeNode<T>* >& child = (dynamic_cast<GTreeNode<T>*>(node->parent))->child;

                child.remove(child.find(node));
                node->parent = NULL;
            } else {
                this->m_root = NULL;
            }

            ret->m_root = node;
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to created a tree...");
        }
    }

public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if ( node != NULL ) {
            if ( this->m_root != NULL ) {
                GTreeNode<T>* np = find(node->parent);

                if ( np != NULL ) {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);

                    /* 检测是否存在该结点，防止重复插入 */
                    if ( np->child.find(n) < 0 ) {
                        np->child.insert(n);
                    }
                } else {
                    THROW_EXCEPTION(InvalidOperationException, "Invalid parent node...");
                }
            } else {
                node->parent = NULL;
                this->m_root = node;
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Invalid node parameter...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;
        GTreeNode<T>* node = NULL;

        node = GTreeNode<T>::NewNode();
        if ( node != NULL ) {
            node->value = value;
            node->parent = parent;
            insert(node);
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to new GTreeNode...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);

        if ( node != NULL ) {
            remove(node, ret);
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Node is invalid...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;

        node = find(node);

        if ( node != NULL ) {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Node is invalid...");
        }

        return ret;
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
        free(root());
        
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