/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-21 23:51:01
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-25 23:18:32
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

    static int* make_pmt(const char* p);
    static int kmp(const char* s, const char* p);

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
    int indexOf(const char* s) const;
    int indexOf(const String& s) const;
    String& remove(int index, int len);
    String& remove(const char* s);
    String& remove(const String& s);
    String& replace(const char* t, const char* s);
    String& replace(const String& t, const char* s);
    String& replace(const char* t, const String& s);
    String& replace(const String& t, const String& s);
    // 从字符串中提取子串
    String sub(int index, int len) const;

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

    String operator - (const String& s) const;
    String operator - (const char* s) const;
    String& operator -= (const String& s);
    String& operator -= (const char* s);

    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    ~String();
};

}

#endif // DTSTRING_H