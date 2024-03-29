/*************************************************************************
 ******* File Name: Exception.cpp
 ******* Author: bb.cui
 ******* Mail: bb.cui@foxmail.com 
 ******* Created Time: Sun 28 Jul 2019 10:53:55 AM CST
 ************************************************************************/

#include "Exception.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

namespace DTLib
{

void Exception::init(const char* message, const char* file, int line)
{
    if(message != NULL)
    {
        // 需要考虑message为空时，防止strdup异常
        m_message = (message ? strdup(message) : NULL);
    }
    else
    {
        m_message = NULL;
    }

    if(file != NULL)
    {
        char sl[16] = {0};

        //itoa(line, sl, 10); // 不是ANSI标准函数，禁止使用
        snprintf(sl, sizeof(sl), "%d", line);

        m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
        if(m_location != NULL)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, sl);
        }
    }
    else
    {
        m_location = NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message, NULL, 0);
}

Exception::Exception(const char*file, int line)
{
    init(NULL, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message, file, line);
}

Exception::Exception(const Exception& e)
{
    if(e.m_message != NULL)
        m_message = strdup(e.m_message);
    if(e.m_location != NULL)
        m_location = strdup(e.m_location);
}

Exception& Exception::operator = (const Exception& e)
{
    if( this != &e)
    {
        if(m_message != NULL)
            free(m_message);
        if(m_location != NULL)
            free(m_location);

        if(e.m_message != NULL)
            m_message = strdup(e.m_message);
        if(e.m_location != NULL)
            m_location = strdup(e.m_location);
    }

    return *this;
}

const char* Exception::message() const
{
    return m_message;
}

const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    if(m_message != NULL)
        free(m_message);
    if(m_location != NULL)
        free(m_location);
}

}

