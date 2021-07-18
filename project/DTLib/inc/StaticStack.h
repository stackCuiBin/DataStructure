/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-18 16:10:59
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-18 16:57:31
 */
#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DTLib
{

template < typename T, int N >
class StaticStack : public Stack<T>
{
protected:
    /* 当 T 为类模板时，会调用N次的T的构造函数 */
    T m_space[N];
    int m_top;
    int m_size;

public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity() const
    {
        return N;
    }
    
    void push(const T& e)
    {
        if ( m_size < N )
        {
            m_space[m_top + 1] = e;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
        }
    }

    void pop()
    {
        if ( m_size > 0 )
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const
    {
        if ( m_size > 0 )
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const
    {
        return m_size;
    }


};

}

#endif  // STATICSTACK_H