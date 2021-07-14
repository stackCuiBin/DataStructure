/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-13 23:41:59
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-15 01:46:22
 */
#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
        Node* pre;
    }m_header; 
    int m_length;
    Node* m_current;
    int m_step;

    // pos = 0，获取的是头结点
    // pos = m_length，获取的是尾结点
    Node* position(int pos) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int i = 0; i < pos; i++)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    DualLinkList()
    {
        m_header.next = NULL;
        m_header.pre  =NULL;
        m_length = 0;
        m_current = NULL;
        m_step = 1;
    }

    bool insert(const T& e)
    {
        return insert(m_length, e);
    }

	bool insert(int pos, const T& e)
    {
        bool ret = (0 <= pos) && (pos <= m_length);
        
        if ( ret )
        {
            Node* node = create();

            if ( node != NULL )
            {
                Node* current = position(pos);
                Node* next = current->next;

                node->value = e;

                node->next = next;
                current->next = node;
                if ( current != reinterpret_cast<Node*>(&m_header) )
                {
                    node->pre = current;
                }
                else
                {
                    node->pre = NULL;
                }
                if ( next != NULL )
                {
                    next->pre = node;
                }

                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
            }
        }

        return ret;
    }

	bool remove(int pos)
    {
        bool ret = (0 <= pos) && (pos < m_length);

        if ( ret )
        {
            Node* current = position(pos);
            Node* toDel = current->next;
            Node* next = toDel->next;

            if ( m_current == toDel )
            {
                m_current = next;
            }

            current->next = next;
            if ( next != NULL )
            {
                next->pre = toDel->pre;
            }

            // 先将长度减 1，防止destroy抛出异常导致链表状态异常
            m_length--;
            destroy(toDel);
        }

        return ret;
    }

	bool set(int pos, const T& e)
    {
        bool ret = (0 <= pos) && (pos < m_length);

        if ( ret )
        {
            position(pos)->next->value = e;
        }

        return ret;
    }

    virtual T get(int pos) const
    {
        T ret;

        if ( get(pos, ret) )
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "DualLinkList:: Invalid parameter");
        }

        return ret;
    }
    
	bool get(int pos, T& e) const
    {
        bool ret = (0 <= pos) && (pos < m_length);

        if ( ret )
        {
            e = position(pos)->next->value;
        }

        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int pos = 0;
        Node* node = m_header.next;

        while( node )
        {
            // 此处的比较操作符不一定适用于所有的泛指类型
            if ( node->value == e )
            {
                ret = pos;
                break;
            }
            else
            {
                node = node->next;
                pos++;
            }
        }

        return ret;
    }

	int length() const
    {
        return m_length;
    }

	void clear()
    {
        while( m_length > 0 )
        {
            remove(0);
        }
    }

    virtual bool move(int pos, int step = 1)
    {
        bool ret = (0 <= pos) && (pos < m_length) && (step > 0);

        if ( ret )
        {
            m_current = position(pos)->next;
            m_step = step;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid para in DualLinkList::move ...");
        }

        return ret;
    }

    virtual bool end()
    {
        return (m_current == NULL);
    }

    virtual T current()
    {
        if ( !end() )
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value in current position ...");
        }
    }

    virtual bool next()
    {
        int step = 0;

        while( (step < m_step) && !end() )
        {
            m_current = m_current->next;
            step++;
        }

        return (step == m_step);
    }

    virtual bool pre()
    {
        int step = 0;

        while( (step < m_step) && !end() )
        {
            m_current = m_current->pre;
            step++;
        }

        return (step == m_step);
    }

    ~DualLinkList()
    {
        clear();
    }

};

}


#endif  // DUALLINKLIST_H