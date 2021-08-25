/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-05 01:04:02
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-08-25 23:31:50
 */
/*************************************************************************
 ******* File Name: Array.h
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Mon 05 Jul 2021 01:02:33 AM CST
 ************************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DTLib
{
template <typename T>
class Array : public Object
{
protected:
    T* m_array;

public:
    virtual bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < length()));

        if( ret )
        {
            m_array[i] = e;
        }

        return ret;
    }

    virtual bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i < length()));

        if ( ret )
        {
            e = m_array[i];
        }

        return ret;
    }

    T& operator[] (int i)
    {
        bool ret = ((0 <= i) && (i < length()));

        if ( ret )
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }

    T operator[] (int i) const
    {
        return (const_cast<Array<T>&>(*this))[i];
    }

    T* array() const
    {
        return m_array;
    }

    virtual int length() const = 0;

};

}

#endif // ARRAY_h
