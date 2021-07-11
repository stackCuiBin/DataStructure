/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-08 00:45:23
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-08 23:03:34
 */
#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DTLib 
{

template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node
    {
        void* operator new(unsigned long size, void* location)
        {
            return location;
        }
    };
    
    unsigned char m_space[sizeof(SNode) * N];
    int m_used[N];

    Node* create()
    {
        SNode* ret = NULL;

        for(int i = 0; i < N; i++)
        {
            if ( !m_used[i] )
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret) SNode();
                m_used[i] = 1;
                break;
            }
        }
        
        return ret;
    }

    void destroy(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        SNode* psn = dynamic_cast<SNode*>(pn);

        for(int i = 0; i < N; i++)
        {
            if ( psn == (space + i) )
            {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }
    }

public:
    using LinkList<T>::clear;

    StaticLinkList()
    {
        for(int i = 0; i < N; i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }

    // 构造和析构函数中不会发生多态，调用的都是类中实现的方法
    ~StaticLinkList()
    {
        // 如果不使用using声明clear，使用this->clear()也可
        clear();
    }
};

}

#endif