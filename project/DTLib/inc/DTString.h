/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-21 23:51:01
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-22 01:59:40
 */
#ifndef DTSTRING_H
#define DTSTRING_H

#include "Object.h"

namespace DTLib
{

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* l, const char* s, int len) const;
public:
    String();
    String(char c);
    String(const char* s);
    String(const String& s);

    int length() const;
    const char* str() const;

    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;

    String& insert(int index, const char* s);
    String& insert(int index, const String& s);

    /* 去掉字符串两端的空白字符 */
    String& trim();

    char& operator [] (int index);
    char operator [] (int index) const;
    bool operator == (const String& s) const;
    bool operator == (const char* s) const;
    bool operator != (const String& s) const;
    bool operator != (const char* s) const;
    bool operator > (const String& s) const;
    bool operator > (const char* s) const;
    bool operator < (const String& s) const;
    bool operator < (const char* s) const;
    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;

    String operator + (const String& s) const;
    String operator + (const char* s) const;
    String& operator += (const String& s);
    String& operator += (const char* s);

    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    ~String();
};

}

#endif // DTSTRING_H