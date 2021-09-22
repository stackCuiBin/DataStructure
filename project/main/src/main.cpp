/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-02 00:00:21
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-22 17:03:40
 */

#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace DTLib;

/*
          _ B
        1 /|  \ 1
        /      _\|
       A --3----> C
 */

int main(int argc, const char* argv[])
{
	ListGraph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');

    g.setEdge(0, 1, 1);
    g.setEdge(1, 2, 1);
    g.setEdge(0, 2, 3);

    SharedPointer< Array<int> > aj = g.floyd(0, 2, 65535);
    for ( int i = 0; i < aj->length(); i++ ) {
        cout << (*aj)[i] << " ";
    }
    cout << endl;
    
    return 0;
}
