/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-09-11 00:04:56
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-14 00:38:29
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Sort.h"

namespace DTLib
{

template < typename E >
struct Edge : public Object
{
    int b;
    int e;
    E data;

    Edge(int i = -1, int j = -1)
    {
        b = i;
        e = j;
    }

    Edge(int i, int j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator == (const Edge& obj)
    {
        return (b == obj.b) && (e == obj.e);
    }

    bool operator != (const Edge& obj)
    {
        return !(*this == obj);
    }

    bool operator < (const Edge& obj)
    {
        return (data < obj.data);
    }

    bool operator > (const Edge& obj)
    {
        return (data > obj.data);
    }

};

template < typename V, typename E >
class Graph : public Object
{
protected:
    template < typename T >
    DynamicArray<T>* toArray(LinkQueue<T>& queue)
    {
        DynamicArray<T>* ret = new DynamicArray<T>(queue.length());

        if ( ret != NULL ) {
            for ( int i = 0; i < ret->length(); i++, queue.remove() ) {
                ret->set(i, queue.front());
            }
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object");
        }

        return ret;
    }

    SharedPointer< Array< Edge<E> > > getUndirectedEdges()
    {
        DynamicArray< Edge<E> >* ret = NULL;

        if ( asUndirected() ) {
            LinkQueue< Edge<E> > queue;

            for ( int i = 0; i < vCount(); i++ ) {
                for ( int j = i; j < vCount(); j++ ) {
                    if ( isAdjacent(i, j) ) {
                        queue.add(Edge<E>(i, j, getEdge(i,j)));
                    }
                }
            }

            ret = toArray(queue);
        } else {
            THROW_EXCEPTION(InvalidOperationException, "This function is for undirected graph only");
        }

        return ret;
    }

    int find(Array<int>& p, int v)
    {
        while ( p[v] != -1 ) {
            v = p[v];
        }

        return v;
    }

public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;
    /* 判断i和j是否相邻 */
    virtual bool isAdjacent(int i, int j) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;

    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

    /* 判断是否为无向图 */
    bool asUndirected()
    {
        bool ret = true;

        for ( int i = 0; (i < vCount()) && ret; i++ ) {
            for ( int j = 0; (j < vCount()) && ret; j++ ) {
                if ( isAdjacent(i, j) ) {
                    ret = ret && isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }

        return ret;
    }

    /* 默认查找最小生成树，LIMIT设置最大值 */
    SharedPointer< Array< Edge<E> > > prim(const E& LIMIT, const bool ISMINCMP = true)
    {
        LinkQueue< Edge<E> > ret;

        if ( asUndirected() ) {                     /* 先判断是否可以看做无向图 */
            DynamicArray<int> adjVex(vCount());     /* cost中权值的对应顶点 */
            DynamicArray<bool> mark(vCount());      /* 顶点编号是在T or F 集 */
            DynamicArray<E> cost(vCount());         /* 记录T集合到F集合中顶点的最小权值 */
            SharedPointer< Array<int> > aj = NULL;
            bool end = false;
            int v = 0;

            for ( int i = 0; i < vCount(); i++ ) {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = LIMIT;
            }

            mark[v] = true;
            aj = getAdjacent(v);
            for ( int i = 0; i < aj->length(); i++ ) {      /* 将顶点 v 添加到T集后，查找所有的边并保存权值 */
                cost[(*aj)[i]] = getEdge(v, (*aj)[i]);
                adjVex[(*aj)[i]] = v;
            }

            for ( int i = 0; (i < vCount()) && !end; i++ ) {
                E m = LIMIT;
                int k = -1;

                for ( int j = 0; j < vCount(); j++ ) {      /* 遍历 T 到 F 集合中所有边的权值最小值 */
                    if ( !mark[j] && (ISMINCMP ? (cost[j] < m) : (cost[j] > m)) ) {
                        m = cost[j];
                        k = j;
                    }
                }

                end = (k == -1);
                if ( !end ) {
                    ret.add(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));
                    mark[k] = true;
                    aj = getAdjacent(k);
                    for ( int j = 0; j < aj->length(); j++ ) {
                        if ( !mark[(*aj)[j]] && (ISMINCMP ? (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]) : (getEdge(k, (*aj)[j]) > cost[(*aj)[j]])) ) {
                            cost[(*aj)[j]] = getEdge(k, (*aj)[j]);
                            adjVex[(*aj)[j]] = k;
                        }
                    }
                }
            }
        } else {
            THROW_EXCEPTION(InvalidOperationException, "Prim operation is for undirected graph only");
        }

        if ( ret.length() != (vCount()-1) ) {
            THROW_EXCEPTION(InvalidOperationException, "No enough edge for prim operation");
        }
        
        return toArray(ret);
    }

    SharedPointer< Array< Edge<E> > > kruskal(const bool ISMINCMP = true)
    {
        LinkQueue< Edge<E> > ret;
        SharedPointer< Array< Edge<E> > > edges = getUndirectedEdges();
        DynamicArray<int> p(vCount());

        for ( int i = 0; i < vCount(); i++ ) {
            p[i] = -1;
        }

        Sort::Shell(*edges, ISMINCMP);

        for ( int i = 0; (i < edges->length()) && (ret.length() < (vCount() -1 )); i++ ) {
            int b = find(p, (*edges)[i].b);
            int e = find(p, (*edges)[i].e);

            if ( b != e ) {
                p[e] = b;
                ret.add((*edges)[i]);
            }
        }

        if ( ret.length() != (vCount() -1 ) ) {
            THROW_EXCEPTION(InvalidOperationException, "No enough edges for kruskal");
        }

        return toArray(ret);
    }

    SharedPointer< Array<int> > BFS(int i)
    {
        DynamicArray<int>* ret = NULL;

        if ( (i >= 0) && (i < vCount()) ) {
            LinkQueue<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for ( int j = 0; j < visited.length(); j++) {
                visited[j] = false;
            }

            q.add(i);

            while ( q.length() > 0 ) {
                int v = q.front();

                q.remove();
                if ( !visited[v] ) {
                    SharedPointer< Array<int> > aj = getAdjacent(v);

                    for ( int j = 0; j < aj->length(); j++ ) {
                        q.add((*aj)[j]);
                    }

                    r.add(v);
                    visited[v] = true;
                }
            }

            ret = toArray(r);
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Input parameter is invalid");
        }
        return ret;
    }

    SharedPointer< Array<int> > DFS(int i)
    {
        DynamicArray<int>* ret = NULL;

        if ( (i >= 0) && (i < vCount()) ) {
            LinkStack<int> q;
            LinkQueue<int> r;
            DynamicArray<bool> visited(vCount());

            for ( int j = 0; j < visited.length(); j++ ) {
                visited[j] = false;
            }

            q.push(i);
            while( q.size() > 0 ) {
                int v = q.top();

                q.pop();

                if ( !visited[v] ) {
                    SharedPointer< Array<int> > aj = getAdjacent(v);
                    for ( int j = aj->length()-1; j >= 0; j-- ) {
                        q.push((*aj)[j]);
                    }

                    r.add(v);
                    visited[v] = true;
                }
            }

            ret = toArray(r);
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Input parameter is invalid");
        }

        return ret;
    }

};

}

#endif // GRAPH_H