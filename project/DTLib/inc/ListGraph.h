/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-09-11 10:18:03
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-11 13:12:21
 */

#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "LinkList.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace DTLib
{

template < typename V, typename E >
class ListGraph : public Graph<V, E>
{
protected:
    struct Vertex : public Object
    {
        V* data;
        LinkList< Edge<E> > edge;

        Vertex()
        {
            data = NULL;
        }
    };

    LinkList<Vertex*> m_list;

public:
    ListGraph(unsigned int n = 0)
    {
        for ( unsigned int i = 0; i < n; i++ ) {
            addVertex();
        }
    }

    int addVertex()
    {
        int ret = -1;

        Vertex* vertex = new Vertex();

        if ( vertex != NULL ) {
            m_list.insert(vertex);
            ret = m_list.length() -1;
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new Vertex object");
        }

        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = addVertex();

        if ( ret >= 0 ) {
            setVertex(ret, value);
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = ( (i >= 0) && (i < vCount()) );

        if ( ret ) {
            Vertex* vertex = m_list.get(i);
            V* data = vertex->data;

            if ( data == NULL ) {
                data = new V();
            }

            if ( data != NULL ) {
                *data = value;
                vertex->data = data;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new Vertex value");
            }
        }

        return ret;
    }

    V getVertex(int i)
    {
        V ret;

        if ( !getVertex(i, ret) ) {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid");
        }

        return ret;
    }

    bool getVertex(int i, V& value)
    {
        int ret = ( (i >= 0) && (i < vCount()) );

        if ( ret ) {
            Vertex* vertex = m_list.get(i);

            if ( vertex->data != NULL ) {
                value = *(vertex->data);
            } else {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex");
            }
        }

        return ret;
    }

    void removeVertex()
    {
        if ( m_list.length() > 0 ) {
            int index = m_list.length() - 1;
            Vertex* v = m_list.get(index);

            if ( m_list.remove(index) ) {
                for( int i = (m_list.move(0), 0); !m_list.end(); i++, m_list.next() ) {
                    int pos = m_list.current()->edge.find(Edge<E>(i, index));

                    if ( pos >= 0 ) {
                        m_list.current()->edge.remove(pos);
                    }
                }

                delete v->data;
                delete v;
            }
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph");
        }
    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL;

        if ( (i >= 0) && (i < vCount()) ) {
            Vertex* vertex = m_list.get(i);

            ret = new DynamicArray<int>(vertex->edge.length());

            if ( ret != NULL ) {
                for( int k = (vertex->edge.move(0), 0); !vertex->edge.end(); k++, vertex->edge.next() ) {
                    ret->set(k, vertex->edge.current().e);
                }
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object");
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Input patameter is invalid");
        }

        return ret;
    }

    E getEdge(int i, int j)
    {
        E ret;

        if ( !getEdge(i, j, ret) ) {
            THROW_EXCEPTION(InvalidParameterException, "Input parameter is invalid");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)
    {
        bool ret = ( (i >= 0) && (i < vCount()) &&
                     (j >= 0) && (j < vCount()));

        if ( ret ) {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i,j));

            if ( pos >= 0 ) {
                value = vertex->edge.get(pos).data;
            } else {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret = ( (i >= 0) && (i < vCount()) &&
                     (j >= 0) && (j < vCount()));

        if ( ret ) {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i,j));

            if ( pos >= 0 ) {
                ret = vertex->edge.set(pos, Edge<E>(i, j, value));
            } else {
                ret = vertex->edge.insert(0, Edge<E>(i, j, value));
            }
        }

        return ret;  
    }

    bool removeEdge(int i, int j)
    {
        bool ret = ( (i >= 0) && (i < vCount()) &&
                     (j >= 0) && (j < vCount()));

        if ( ret ) {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i,j));

            if ( pos >= 0 ) {
                ret = vertex->edge.remove(pos);
            }
        }

        return ret;  
    }
    int vCount()
    {
        return m_list.length();
    }

    int eCount()
    {
        int ret = 0;

        for ( m_list.move(0); !m_list.end(); m_list.next() ) {
            ret += m_list.current()->edge.length();
        }

        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if ( (i >= 0) && (i < vCount()) ) {
            for ( m_list.move(0); !m_list.end(); m_list.next() ) {
                LinkList< Edge<E> >& edge = m_list.current()->edge;

                for ( edge.move(0); !edge.end(); edge.next() ) {
                    if ( edge.current().e == i ) {
                        ret++;
                        break;
                    }
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Input parameter is invalid");
        }

        return ret;
    }

    int OD(int i)
    {
        int ret = 0;

        if ( (i >= 0) && (i < vCount()) ) {
            ret = m_list.get(i)->edge.length();
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Input parameter is invalid");
        }

        return ret;
    }

    ~ListGraph()
    {
        while ( m_list.length() > 0 ) {
            Vertex* toDel = m_list.get(0);

            m_list.remove(0);

            delete toDel->data;
            delete toDel;
        }
    }
    
};

}

#endif // LISTGRAPH_Hincl