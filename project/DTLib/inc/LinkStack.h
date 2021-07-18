/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-18 17:00:34
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-18 17:08:22
 */
#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"

namespace DTLib
{

template < typename T >
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> m_list;

public:
    void push(const T& e)
    {
        m_list.insert(0, e);
    }

    void pop()
    {
        if ( m_list.length() > 0 )
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const
    {
        if ( m_list.length() > 0 )
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear()
    {
        m_list.clear();
    }

    int size() const
    {
        return m_list.length();
    }

};

}

#endif  // LINKSTACK_h