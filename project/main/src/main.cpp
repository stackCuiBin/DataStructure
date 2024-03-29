/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-02 00:00:21
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-10-14 01:11:40
 */

#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace DTLib;

int search_max_path(Graph<int, int>& g, int v, Array<int>& count,  Array< LinkList<int>* >& path, Array<int>& mark)
{
    int ret = 0;
    SharedPointer< Array<int> > aj = g.getAdjacent(v);

    for (int i = 0; i < aj->length(); i++) {
        int num = 0;

        if ( !mark[(*aj)[i]] ) {
            num = search_max_path(g, (*aj)[i], count, path, mark);
        } else {
            num = count[(*aj)[i]];
        }

        if ( ret < num )
        {
            ret = num;
        }
    }

    for (int i = 0; i < aj->length(); i++) {
        if ( ret == count[(*aj)[i]]) {
            path[v]->insert((*aj)[i]);
        }
    }

    ret++;   /* 算上自身顶点数 */

    count[v] = ret;
    mark[v] = true;

    return ret;
}

SharedPointer< Graph<int, int> > create_graph(int* a, int len)
{
    ListGraph<int, int>* ret = new ListGraph<int, int>(len);

    for (int i = 0; i < len; i++) {
        ret->setVertex(i, a[i]);
    }

    for (int i = 0; i < len; i++) {
        for (int j = i+1; j < len; j++) {
            if ( a[i] <= a[j] ) {
                ret->setEdge(i, j, 1);
            }
        }
    }

    return ret;
}

void init_array(Array<int>& count,  Array< LinkList<int>* >& path, Array<int>& mark)
{
    for (int i = 0; i < count.length(); i++) {
        count[i] = 0;
    }

    for (int i = 0; i < path.length(); i++) {
        path[i] = new LinkList<int>();
    }

    for (int i = 0; i < mark.length(); i++) {
        mark[i] = false;
    }
}

void print_path(Graph<int, int>& g, int v, Array< LinkList<int>* >& path, LinkList<int>& cp)
{
    cp.insert(v);

    if ( path[v]->length() > 0 ) {
        for (path[v]->move(0); !path[v]->end(); path[v]->next()) {
            print_path(g, path[v]->current(), path, cp);
        }
    } else {
        cout << "Elements: ";
        for (cp.move(0); !cp.end(); cp.next()) {
            cout << g.getVertex(cp.current()) << " ";
        }
        cout << endl;
    }

    cp.remove(cp.length()-1);
}

void print_max_path(Graph<int, int>& g, Array<int>& count, Array< LinkList<int>* >& path)
{
    int max = 0;
    LinkList<int> cp;

    for (int i = 0; i < count.length(); i++) {
        if ( max < count[i] ) {
            max = count[i];
        }
    }

    cout << "len: " << max << endl;

    for (int i = 0; i < count.length(); i++) {
        if ( max == count[i] ) {
            print_path(g, i, path, cp);
        }
    }
}

void search_max_path(Graph<int, int>& g, Array<int>& count, Array< LinkList<int>* >& path, Array<int>& mark)
{
    for (int i = 0; i < g.vCount(); i++) {
        if ( !mark[i] ) {
            search_max_path(g, i, count, path, mark);
        }
    }
}
void solution(int* a, int len)
{
    DynamicArray<int> count(len);
    DynamicArray< LinkList<int>* > path(len);
    DynamicArray<int> mark(len);
    SharedPointer< Graph<int, int> > g;

    g = create_graph(a, len);

    init_array(count, path, mark);

    search_max_path(*g, count, path, mark);

    print_max_path(*g, count, path);
}

int main(int argc, const char* argv[])
{
    int a[] = {4, 3, 2, 1};
    // int a[] = {1, 2, 3, 4};
    // int a[] = {1, 3, 5, 4};
    // int a[] = {2, 1, 3, 5, 4};

    solution(a, sizeof(a)/sizeof(*a));

    return 0;
}
