/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-05 22:58:47
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-07 22:58:33
 */
#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class List : public Object
{
protected:
	List(const List& e);
	List& operator=(const List& e);
public:
	List() {};
	virtual bool insert(const T& e) = 0;
	virtual bool insert(int pos, const T& e) = 0;
	virtual bool remove(int pos) = 0;
	virtual bool set(int pos, const T& e) = 0;
	virtual bool get(int pos, T& e) const = 0;
	virtual int find(const T& e) const = 0;
	virtual int length() const = 0;
	virtual void clear() = 0;
};

}

#endif
