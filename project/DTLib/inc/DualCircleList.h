/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-15 00:40:35
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-18 14:58:44
 */
#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "LinuxList.h"
#include "DualLinkList.h"

namespace DTLib
{

template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T         value;
    };

    list_head  m_header;
    list_head* m_current;

    list_head* position(int pos) const
    {
        list_head* ret = const_cast<list_head*>(&m_header);
        
        for(int i = 0; i < pos; i++)
        {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

public:
    DualCircleList()
    {
        this->m_length = 0;
        this->m_step = 1;

        m_current = NULL;

        INIT_LIST_HEAD(&m_header);
    }

    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int pos, const T& e)
    {
        bool ret = true;
        Node* node = new Node();

        if ( this->m_length > 0 )
        {
            pos = pos % (this->m_length * 2);
        }
        pos = pos % (this->m_length + 1);

        if ( node != NULL )
        {
            node->value = e;
            list_add_tail(&node->head, position(pos)->next);
            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element...");
        }

        return ret;
    }

    bool remove(int pos)
    {
        bool ret = true;

        pos = mod(pos);
        ret = ((0 <= pos) && (pos < this->m_length));

        if ( ret )
        {
            list_head* toDel = position(pos)->next;

            if ( m_current == toDel )
            {
                m_current = toDel->next;
            }

            list_del(toDel);

            this->m_length--;

            if ( this->m_length == 0 )
            {
                m_current = NULL;
            }

            delete list_entry(toDel, Node, head);
        }

        return ret;
    }

    bool set(int pos, const T& e)
    {
        bool ret = true;

        pos = mod(pos);
        ret = ( (0 <= pos) && (pos < this->m_length) );

        if ( ret )
        {
            list_entry(position(pos)->next, Node, head)->value = e;
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
            THROW_EXCEPTION(InvalidParameterException, "DuaCircleList:: Invalid parameter");
        }

        return ret;
    }

    bool get(int pos, T& e) const
    {
        bool ret = true;

        pos = mod(pos);
        ret = ( (0 <= pos) && (pos < this->m_length) );

        if ( ret )
        {
            e = list_entry(position(pos)->next, Node, head)->value;
        }

        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int pos = 0;
        list_head* slider = NULL;

        list_for_each(slider, &m_header)
        {
            if ( list_entry(slider, Node, head)->value == e )
            {
                ret = pos;
                break;
            }
            pos++;
        }

        return ret;
    }

    int length() const
    {
        return this->m_length;
    }

    void clear()
    {
        while( this->m_length > 0 )
        {
            remove(0);
        }
    }

    bool move(int pos, int step = 1)
    {
        bool ret = (step > 0);

        pos = mod(pos);
        ret = ret && (0 <= pos) && (pos < this->m_length);

        if ( ret )
        {
            m_current = position(pos)->next;

            this->m_step = step;
        }

        return ret;
    }

    /* 此结束实现有问题 */
    bool end()
    {
        return (this->m_length == 0) || (m_current == NULL);
    }

    T current()
    {
        if ( !end() )
        {
            return list_entry(m_current, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value in current position ...");
        }
    }

    bool next()
    {
        int step = 0;

        while( (step < this->m_step) && !end() )
        {
            if ( m_current != &m_header )
            {
                m_current = m_current->next;
                step++;   
            }
            else
            {
                m_current = m_current->next;
            }
        }

        if ( m_current == &m_header )
        {
            m_current = m_current->next;
        }

        return (step == this->m_step);
    }

    bool pre()
    {
        int step = 0;

        while( (step < this->m_step) && !end() )
        {
            if ( m_current != &m_header )
            {
                m_current = m_current->prev;
                step++;   
            }
            else
            {
                m_current = m_current->prev;
            }
        }

        if ( m_current == &m_header )
        {
            m_current = m_current->prev;
        }

        return (step == this->m_step);
    }

    ~DualCircleList()
    {
        clear();
    }
};

}

#endif  // DUALCIRCLELIST_H