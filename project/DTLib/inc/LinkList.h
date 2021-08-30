/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-06 00:42:47
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-08-28 02:05:31
 */
#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    // mutable Node m_header;
    // 为防止m_header中的泛型T构建过程中抛出异常，
    // 采用下边的方法规避T的构建过程
    // 不加 public Object 将会段错误，原因是内存布局与Node有差异,
    // 在position中强制类型转换会发生异常
    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
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
    LinkList()
    {
        m_header.next = NULL;
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

                node->value = e;
                node->next = current->next;
                current->next = node;

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

            if ( m_current == toDel )
            {
                m_current = toDel->next;
            }

            current->next = toDel->next;

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
            THROW_EXCEPTION(InvalidParameterException, "LinkList:: Invalid parameter");
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
        while( m_header.next )
        {
            Node* toDel = m_header.next;

            m_header.next = toDel->next;

            m_length--;

            destroy(toDel);
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

    ~LinkList()
    {
        clear();
    }

};

}

#endif // LINKLIST_H