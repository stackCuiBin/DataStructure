/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-02 00:00:21
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-16 01:47:44
 */

#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace DTLib;

/*
            A
        1 /   \ 3
        /       \
       B --1---- C
        \       /
        4 \   / 1
            D
 */

int main(int argc, const char* argv[])
{
	ListGraph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');

    g.setEdge(0, 1, 1);
    g.setEdge(0, 2, 3);
    g.setEdge(1, 2, 1);
    g.setEdge(1, 3, 4);
    g.setEdge(2, 3, 1);

    SharedPointer< Array<int> > aj = g.dijkstra(0, 3, 65535);
    for ( int i = 0; i < aj->length(); i++ ) {
        cout << (*aj)[i] << " ";
    }
    cout << endl;
    
    return 0;
}
