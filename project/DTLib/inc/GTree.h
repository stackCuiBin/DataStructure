/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-27 00:19:57
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-01 00:27:17
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

    GTree(const GTree<T>&);
    GTree& operator = (const GTree<T>&);

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

    int count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if ( node != NULL ) {
            /* 不为空，说明至少有一个结点 */
            ret = 1;

            for ( node->child.move(0); !node->child.end(); node->child.next() ) {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if ( node != NULL ) {
            for ( node->child.move(0); !node->child.end(); node->child.next() ) {
                int h = height(node->child.current());

                if ( ret < h ) {
                    ret = h;
                }
            }

            ret = ret + 1;
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if ( node != NULL ) {
            ret = node->child.length();

            for ( node->child.move(0); !node->child.end(); node->child.next() ) {
                int d = degree(node->child.current());

                if ( ret < d ) {
                    ret = d;
                }
            }
        }

        return ret;
    }

public:
    GTree() {}
    
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
            m_queue.clear();
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
            m_queue.clear();
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
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());
        
        this->m_root = NULL;

        m_queue.clear();
    }

    bool begin()
    {
        bool ret = (root() != NULL);

        if ( ret ) {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return m_queue.length() == 0;
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if ( ret ) {
            GTreeNode<T>* node = m_queue.front();

            m_queue.remove();
            for ( node->child.move(0); !node->child.end(); node->child.next() ) {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }

    T current()
    {
        if ( !end() ) {
            return m_queue.front()->value;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No value in current position...");
        }
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H