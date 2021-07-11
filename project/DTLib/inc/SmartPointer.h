/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-07-30 01:00:26
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-09 00:42:48
 */
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace DTLib
{

template < typename T >
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p) { }
    
    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;

        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    SmartPointer<T>& operator = (const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* temp = this->m_pointer;

            this->m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

            delete temp;
        }

        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}

#endif // SMARTPOINTER_H
