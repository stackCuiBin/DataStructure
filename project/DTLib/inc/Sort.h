/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-23 22:15:31
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-08-23 23:21:58
 */

#ifndef SORT_H
#define SORT_H

#include "Object.h"

namespace DTLib
{

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);

    template < typename T >
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

public:
    // 不稳定排序
    template < typename T >
    static void Select(T array[], int len, bool min2max = true)
    {
        for( int i = 0; i < len-1; i++ )
        {
            int min = i;

            for( int j = i+1; j < len; j++ )
            {
                if ( min2max ? (array[min] > array[j]) : (array[min] < array[j]) )
                {
                    min = j;
                }
            }

            if ( min != i )
            {
                Swap(array[min], array[i]);
            }
        }
    }

    template < typename T >
    static void Insert(T array[], int len, bool min2max = true)
    {
        for( int i = 1; i < len; i++ )
        {
            int k = i;
            T e = array[i];

            for( int j = i-1; (j >= 0) && (min2max ? (array[j]>e) : (array[j]<e)); j-- )
            {
                array[j+1] = array[j];
                k = j;
            }

            if ( k != i )
            {
                array[k] = e;
            }
        }
    }

};

}

#endif // SORT_H

