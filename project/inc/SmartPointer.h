/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-07-30 01:00:26
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-06 00:48:44
 */
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class SmartPointer : public Object
{
protected:
    T* m_pointer;

public:
    SmartPointer(T* p = NULL)
    {
        m_pointer = p;
    }

    SmartPointer(const SmartPointer<T>& obj)
    {
        m_pointer = obj.m_pointer;

        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    SmartPointer<T>& operator = (const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            delete m_pointer;

            m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
        }

        return *this;
    }

    T* operator -> ()
    {
        return m_pointer;
    }

    T& operator * ()
    {
        return *this;
    }

    bool isNull()
    {
        return (m_pointer == NULL);
    }

    T* get()
    {
        return m_pointer;
    }

    ~SmartPointer()
    {
        delete m_pointer;
    }
};

}

#endif // SMARTPOINTER_H
