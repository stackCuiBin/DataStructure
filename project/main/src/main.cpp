/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-02 00:00:21
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-13 23:31:05
 */

#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace DTLib;

/*
            A
        1 / | \ 2
        /   |3  \
       B --1---- D
        \   |   /
        4 \ | / 1
            C
 */

int main(int argc, const char* argv[])
{
	ListGraph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');

    /* 双向设置相同的权值，视其为无向图 */
    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 1);

    g.setEdge(0, 2, 3);
    g.setEdge(2, 0, 3);

    g.setEdge(0, 3, 2);
    g.setEdge(3, 0, 2);

    g.setEdge(1, 2, 4);
    g.setEdge(2, 1, 4);

    g.setEdge(1, 3, 1);
    g.setEdge(3, 1, 1);

    g.setEdge(2, 3, 1);
    g.setEdge(3, 2, 1);

    SharedPointer< Array< Edge<int> > > aj = g.prim(65535);
    int ret = 0;
    for ( int i = 0; i < aj->length(); i++ ) {
        cout << (*aj)[i].b << " " << (*aj)[i].e << endl;
        ret += (*aj)[i].data;
    }
    cout << "ret " << ret << endl;

    return 0;
}
