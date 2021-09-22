/*
 * @Descripttion: Dynamic array 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-05 22:49:31
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-22 17:15:59
 */

#ifndef DYNAMICARRAY_h
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    T* copy(T* array, int len, int newlen)
    {
        T* ret = new T[newlen];

        if ( ret != NULL && array != NULL)
        {
            int size = (len < newlen) ? len : newlen;

            for(int i = 0; i < size; i++)
            {
                ret[i] = array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray object ...");
        }

        return ret;
    }

    void update(T* array, int len)
    {
        if ( array != NULL)
        {
            T* temp = this->m_array;

            this->m_array = array;
            this->m_length = len;

            delete[] temp;
        }
        else
        {
             THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicArray object ...");
        }
    }
    void init(T* array, int length)
    {
        if ( array != NULL )
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
        }
    }

public:
    DynamicArray(int length = 0)
    {
        init(new T[length], length);
        // this->m_array = new T[length];

        // if ( this->m_array != NULL )
        // {
        //     this->m_length = length;
        // }
        // else
        // {
        //     THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
        // }
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        init( copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length );
        // this->m_array = new T[obj.m_length];

        // if ( this->m_array != NULL )
        // {
        //     this->m_length = obj.m_length;

        //     for(int i= 0; i < obj.m_length; i++)
        //     {
        //         this->m_array[i] = obj.m_array[i];
        //     }
        // }
        // else
        // {
        //     THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray object ...");
        // }
    }

    DynamicArray<T>& operator= (const DynamicArray<T>& obj)
    {
        if ( this != &obj )
        {
            update( copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length );
            // T* array = new T[obj.m_length];

            // if ( array != NULL )
            // {
            //     for(int i = 0; i < obj.m_length; i++ )
            //     {
            //         array[i] = obj.m_array[i];
            //     }

            //     T* temp = this->m_array;
                
            //     this->m_array = array;
            //     this->m_length = obj.m_length;

            //     delete[] temp;
            // }
            // else
            // {
            //     THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray object ...");
            // }
        }

        return *this;
    }

    int length() const
    {
        return m_length;
    }

    void resize(int length)
    {
        if ( length != m_length )
        {
            update( copy(this->m_array, m_length, length), length );
            // T* array = new T[length];

            // if ( array != NULL )
            // {
            //     int size = length < m_length ? length : m_length;

            //     for(int i = 0; i < size; i++)
            //     {
            //         array[i] = this->m_array[i];
            //     }

            //     T* temp = this->m_array;

            //     this->m_array = array;
            //     this->m_length = length;

            //     delete[] temp;
            // }
            // else
            // {
            //     THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize object ...");
            // }
        }
    }

};

}

#endif // DYNAMICARRAY_H
