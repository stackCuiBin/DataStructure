/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-11 23:33:37
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-12 02:05:31
 */
#ifndef CIRCLELIST_H
#define CIRCLRLIST_H

#include "LinkList.h"

namespace DTLib
{

template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

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
        last()->next = this->m_header.next;
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
        ret = LinkList<T>::insert(pos, e);
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
            ret = LinkList<T>::remove(pos);
        }
    }

    bool set(int pos, const T& e)
    {
        return LinkList<T>::set(mod(pos), e);
    }

    T get(int pos) const
    {
        return LinkList<T>::get(mod(pos));
    }

    bool get(int pos, const T& e) const
    {
        return LinkList<T>::get(mod(pos), e);
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
        return LinkList<T>::move(mod(pos), step);
    }

    bool end()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    

    ~CircleList()
    {
        clear();
    }
};

}

#endif  // CIRCLELIST_H