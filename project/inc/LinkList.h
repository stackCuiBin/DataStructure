/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-06 00:42:47
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-06 02:04:19
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

    Node* position(int pos) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int i = 0; i < pos; i++)
        {
            ret = ret->next;
        }

        return ret;
    }

public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
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
            Node* node = new Node();

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

            current->next = toDel->next;

            delete toDel;
            m_length--;
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

    T get(int pos) const
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

            delete toDel;
        }
        m_length = 0;
    }

    ~LinkList()
    {
        clear();
    }

};

}

#endif // LINKLIST_H