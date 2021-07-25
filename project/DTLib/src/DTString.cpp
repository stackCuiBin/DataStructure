/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-07-21 23:54:23
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-07-25 23:28:45
 */
#include <cstdlib>
#include <cstring>
#include "DTString.h"
#include "Exception.h"

namespace DTLib
{

// 求子字符的部分匹配表
int* String::make_pmt(const char* p)
{
	int len = strlen(p ? p : "");
	int* ret = static_cast<int*>(malloc(sizeof(int)*len));

	if ( ret != NULL )
	{
		int ll = 0;

		ret[0] = 0;

		for(int i = 1; i < len; i++)
		{
			while( (ll > 0) && (p[ll] != p[i]) )
			{
				// 下标为0时对应字符长度为1
				ll = ret[ll-1];
			}

			if ( p[ll] == p[i] )
			{
				ll++;
			}

			ret[i] = ll;
		}
	}

	return ret;
}

int String::kmp(const char* s, const char* p)
{
	int ret = -1;
	int sl = strlen(s ? s : "");
	int pl = strlen(p ? p : "");
	int* pmt = make_pmt(p);

	if ( (pmt != NULL) && (pl > 0) && (pl <= sl) )
	{
		for(int i = 0, j = 0; i < sl; i++)
		{
			while( (j > 0) && (s[i] != p[j]) )
			{
				j = pmt[j-1];
			}

			if ( s[i] == p[j] )
			{
				j++;
			}

			if ( j == pl )
			{
				ret = i + 1 - pl;
				break;
			}
		}
	}

	free(pmt);

	return ret;
}

void String::init(const char* s)
{
    m_str = strdup(s);

    if ( m_str != NULL )
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create String object ...");
    }
}

bool String::equal(const char* l, const char* s, int len) const
{
    bool ret = true;

    for(int i = 0; (i < len) && ret; i++)
    {
        ret = ret && (l[i] == s[i]);
    }

    return ret;
}

String::String()
{
    init("");
}

String::String(char c)
{
    char s[] = {c, '\0'};

    init(s);
}

String::String(const char* s)
{
    init(s ? s : "");
}

String::String(const String& s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);

    if ( ret )
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}

bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}

bool String::endOf(const char* s) const
{
    bool ret = (s != NULL);

    if ( ret )
    {
        int len = strlen(s);
        char* str = m_str + (m_length - len);

        ret = (len < m_length) && equal(str, s, len);
    }

    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int index, const char* s)
{
    if ( (0 <= index) && (index <= m_length) )
    {
        if ( (s != NULL) && (s[0] != '\0') )
        {
            int len = strlen(s);
            char* str = reinterpret_cast<char*>(malloc(m_length + len + 1));
            
            if ( str != NULL )
            {
                strncpy(str, m_str, index);
                strncpy(str+index, s, len);
                strncpy(str+index+len, m_str+index, m_length-index);
                str[m_length+len] = '\0';

                free(m_str);

                m_str = str;
                m_length += len; 
            } 
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert String value ...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "Invalid parameter in String::insert ...");
    }

    return *this;
}

String& String::insert(int index, const String& s)
{
    return insert(index, s.m_str);
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;

    while(m_str[b] == ' ')b++;
    while(m_str[e] == ' ')e--;

    if ( b == 0 )
    {
        m_str[e + 1] = '\0';
        m_length = e + 1;
    }
    else
    {
        for(int i = 0, j = b; j <= e; i++, j++)
        {
            m_str[i] = m_str[j];
        }

        m_str[e-b+1] = '\0';
        m_length = e-b+1;
    }

    return *this;
}

int String::indexOf(const char* s) const
{
    return kmp(m_str, s ? s : "");
}

int String::indexOf(const String& s) const
{
    return kmp(m_str, s.m_str);
}

String& String::remove(int index, int len)
{
    if ( (0 <= index) && (index < m_length) )
    {
        int n = index;
        int m = index + len;

        while( (n < m) && (m < m_length) )
        {
            m_str[n++] = m_str[m++];
        }

        m_str[n] = '\0';
        m_length = n;
    }

    return *this;
}

String& String::remove(const char* s)
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

String& String::remove(const String& s)
{
    return remove(indexOf(s), s.length());
}

String& String::replace(const char* t, const char* s)
{
    int index = indexOf(t);

    if ( index >= 0 )
    {
        remove(t);
        insert(index, s);
    }

    return *this;
}

String& String::replace(const String& t, const char* s)
{
    return replace(t.m_str, s);
}

String& String::replace(const char* t, const String& s)
{
    return replace(t, s.m_str);
}

String& String::replace(const String& t, const String& s)
{
    return replace(t.m_str, s.m_str);
}

String String::sub(int index, int len) const
{
    String ret;

    if ( (0 <= index) && (index < m_length) )
    {
        if ( len < 0 ) len = 0;
        if ( (index + len) > m_length ) len = m_length - index;
        char* str = reinterpret_cast<char*>(malloc(len + 1));

        if ( str != NULL )
        {
            strncpy(str, m_str + index, len);
            str[len] = '\0';

            ret = str;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new String ...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "Parameter index is invalid in String ...");
    }

    return ret;
}

char& String::operator [] (int index)
{
    if ( (0 <= index) && (index < m_length) )
    {
        return m_str[index];
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "Parameter i is invalid in String [] ...");
    }
}

char String::operator [] (int index) const
{
    return (const_cast<String&>(*this))[index];
}

bool String::operator == (const String& s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}

bool String::operator == (const char* s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}

bool String::operator != (const String& s) const
{
    return !(*this == s);
}

bool String::operator != (const char* s) const
{
    return !(*this == s);
}

bool String::operator > (const String& s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}

bool String::operator > (const char* s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}

bool String::operator < (const String& s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}

bool String::operator < (const char* s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}

bool String::operator >= (const String& s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}

bool String::operator >= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}

bool String::operator <= (const String& s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}

bool String::operator <= (const char* s) const
{
    return (strcmp(m_str, s ? s : "") <= 0);
}

String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}

String String::operator + (const char* s) const
{
    String ret;
    int len = m_length + strlen(s ? s : "");
    char* str = reinterpret_cast<char*>(malloc(len + 1));

    if ( str != NULL )
    {
        strcpy(str, m_str);
        strcat(str, s ? s : "");

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add String values ...");
    }

    return ret;
}

String& String::operator += (const String& s)
{
    return (*this = *this + s.m_str);
}

String& String::operator += (const char* s)
{
    return (*this = *this + s);
}

String String::operator - (const String& s) const
{
    return String(*this).remove(s);
}

String String::operator - (const char* s) const
{
    return String(*this).remove(s);
}

String& String::operator -= (const String& s)
{
    return remove(s);
}

String& String::operator -= (const char* s)
{
    return remove(s);
}

String& String::operator = (const String& s)
{
    return (*this = s.m_str);
}

String& String::operator = (const char* s)
{
    if ( m_str != s )
    {
        char* str = strdup(s ? s : "");

        if ( str != NULL )
        {
            free(m_str);

            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to assign new String value ...");
        }
    }

    return *this;
}

String& String::operator = (char c)
{
    char s[] = {c, '\0'};

    return (*this = s);
}

String::~String()
{
    free(m_str);
}

}