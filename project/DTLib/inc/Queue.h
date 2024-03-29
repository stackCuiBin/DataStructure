/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-18 23:19:10
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-18 23:49:29
 */
#ifndef QUEUE_H
#define QUEUE_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class Queue : public Object
{
public:
    virtual void add(const T& e) = 0;
    virtual void remove() = 0;
    virtual T front() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
};

}

#endif  // QUEUE_H