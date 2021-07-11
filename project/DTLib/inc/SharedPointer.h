/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-09 01:50:11
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-09 02:41:13
 */
#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include <cstdlib>
#include "Pointer.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;

    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;

        if ( this->m_ref )
        {
            (*this->m_ref)++;
        }
    }

public:
    SharedPointer(T* p = NULL) : m_ref(NULL)
    {
        if ( p )
        {
            this->m_ref = static_cast<int*>(malloc(sizeof(int)));

            if ( this->m_ref )
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory for SharedPointer ...");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
    {
        assign(obj);
    }

    SharedPointer<T>& operator= (const SharedPointer<T>& obj)
    {
        if ( this != &obj )
        {
            clear();
            assign(obj);
        }

        return *this;
    }

    void clear()
    {
        int* ref = this->m_ref;
        T* toDel = this->m_pointer;

        this->m_ref = NULL;
        this->m_pointer = NULL;

        if ( ref )
        {
            (*ref)--;

            if ( *ref == 0 )
            {
                free(ref);
                delete toDel;
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }

};

template < typename T >
bool operator== (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template < typename T >
bool operator!= (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
    return !(l == r);
}

}


#endif // SHAREDPOINTER_H