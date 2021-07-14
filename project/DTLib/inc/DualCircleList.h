/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-15 00:40:35
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-15 01:43:22
 */
#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "DualLinkList.h"

namespace DTLib
{

template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    typedef typename DualLinkList<T>::Node Node;

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

    Node* last() const
    {
        return this->position(this->m_length);
    }

    void last_to_first() const
    {
        Node* tail = last();

        tail->next = this->m_header.next;
        this->m_header.next->pre = tail;
    }

public:
    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int pos, const T& e)
    {
        bool ret = false;

        if ( this->m_length != 0 )
        {
            pos = pos % (this->m_length * 2);
        }
        pos = pos % (this->m_length + 1);
        ret = DualLinkList<T>::insert(pos, e);
        if ( ret && (pos == 0) )
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int pos)
    {
        bool ret = true;

        pos = mod(pos);
        if ( pos == 0 )
        {
            Node* toDel = this->m_header.next;

            if ( toDel != NULL )
            {
                this->m_header.next = toDel->next;
                this->m_length--;

                if ( this->m_length > 0 )
                {
                    last_to_first();

                    if ( this->m_current == toDel )
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }

                this->destroy(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = DualLinkList<T>::remove(pos);
        }

        return ret;
    }

    bool set(int pos, const T& e)
    {
        return DualLinkList<T>::set(mod(pos), e);
    }

    T get(int pos) const
    {
        return DualLinkList<T>::get(mod(pos));
    }

    bool get(int pos, const T& e) const
    {
        return DualLinkList<T>::get(mod(pos), e);
    }

    int find(const T& e) const
    {
        int ret = -1;
        Node* slider = this->m_header.next;

        for (int i = 0; i < this->m_length; i++)
        {
            if ( slider->value == e )
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void clear()
    {
        while( this->m_length > 1 )
        {
            remove(1);
        }

        if ( this->m_length == 1 )
        {
            Node* toDel = this->m_header.next;

            this->m_header.next = NULL;
            this->m_current = NULL;
            this->m_length = 0;

            this->destroy(toDel);
        }
    }

    bool move(int pos, int step)
    {
        return DualLinkList<T>::move(mod(pos), step);
    }

    /* 此结束实现有问题 */
    bool end()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~DualCircleList()
    {
        clear();
    }
};

}

#endif  // DUALCIRCLELIST_H