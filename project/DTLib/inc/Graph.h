/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-09-11 00:04:56
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-22 17:11:42
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

    SharedPointer< Array<int> > dijkstra(int i, int j, const E& LIMIT)
    {
        LinkQueue<int> ret;

        if ( (i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()) ) {
            DynamicArray<E> dist(vCount());
            DynamicArray<bool> mark(vCount());
            DynamicArray<int> path(vCount());

            for ( int k = 0; k < vCount(); k++ ) {
                mark[k] = false;
                path[k] = -1;
                /* 和起始顶点相邻的：设置为权值 */
                dist[k] = isAdjacent(i, k) ? (path[k] = i, getEdge(i, k)) : LIMIT;
            }

            mark[i] = true;
            for ( int k = 0; k < vCount(); k++ ) {
                E m = LIMIT;
                int u = -1;

                /* 查找未被标记的最小权值的顶点 u */
                for ( int w = 0; w < vCount(); w++ ) {
                    if ( !mark[w] && (dist[w] < m) ) {
                        m = dist[w];
                        u = w;
                    }
                }

                /* 未查找到 u， 遍历结束 */
                if ( u == -1 ) {
                    break;
                }

                mark[u] = true;
                /* 目前以查找到顶点到u的最短路径，遍历u的未被标记的邻接顶点，更新它们的最小路径及前驱顶点 */
                for ( int w = 0; w < vCount(); w++ ) {
                    if ( !mark[w] && isAdjacent(u, w) && ((dist[u] + getEdge(u, w)) < dist[w]) ) {
                        dist[w] = dist[u] + getEdge(u, w);
                        path[w] = u;
                    }
                }
            }

            LinkStack<int> s;

            s.push(j);
            for ( int k = path[j]; k != -1; k = path[k] ) {
                s.push(k);
            }

            while ( s.size() > 0 ) {
                ret.add(s.top());
                s.pop();
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Input parameter is invalid");
        }

        if ( ret.length() < 2 ) {
            THROW_EXCEPTION(ArithmeticException, "There is no path from i to j");
        }

        return toArray(ret);
    }

    SharedPointer< Array<int> > floyd(int x, int y, const E& LIMIT)
    {
        LinkQueue<int> ret;

        if ( (0 <= x) && (x < vCount()) && (0 <= y) && (y < vCount()) ) {
            DynamicArray< DynamicArray<E> > dist(vCount());
            DynamicArray< DynamicArray<int> > path(vCount());

            for (int k = 0; k < vCount(); k++) {
                dist[k].resize(vCount());
                path[k].resize(vCount());
            }

            for ( int i = 0; i < vCount(); i++ ) {
                for (int j = 0; j < vCount(); j++ ) {
                    path[i][j] = -1;
                    dist[i][j] = isAdjacent(i, j) ? (path[i][j] = j, getEdge(i, j)) : LIMIT;
                }
            }

            for ( int k = 0; k < vCount(); k++ ) {
                for ( int i = 0; i < vCount(); i++ ) {
                    for ( int j = 0; j < vCount(); j++ ) {
                        if ( (dist[i][k] + dist[k][j]) < dist[i][j] ) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            path[i][j] = path[i][k];
                        }
                    }
                }
            }

            while( (x != -1) && (x != y) ) {
                ret.add(x);
                x = path[x][y];
            }

            if ( x != -1 ) {
                ret.add(x);
            }
            
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Input parameter is invalid");
        }

        if ( ret.length() < 2 ) {
            THROW_EXCEPTION(ArithmeticException, "There is no path from i to j");
        }

        return toArray(ret);
    }

};

}

#endif // GRAPH_H