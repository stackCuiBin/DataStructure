/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-08 23:49:56
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-09 02:37:57
 */
#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class Pointer : public Object
{
protected:
    T* m_pointer;

public:
    Pointer(T* p = NULL)
    {
        m_pointer = p;
    }

    T* operator-> ()
    {
        return m_pointer;
    }
    
    T& operator* ()
    {
        return *m_pointer;
    }

    const T* operator-> () const
    {
        return m_pointer;
    }
    
    const T& operator* () const
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return ( m_pointer == NULL );
    }
    
    T* get() const
    {
        return m_pointer;
    }

};

}

#endif  // POINTER_H