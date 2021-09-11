/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-02 00:00:21
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-11 13:17:16
 */

#include <iostream>
#include "ListGraph.h"

using namespace std;
using namespace DTLib;

/*
        6
    A ------> D
    |      / /|\
   5|   9/    |2
   \|/|/_     |
    B ------> C
        8
 */

int main(int argc, const char* argv[])
{
	ListGraph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');

    // g.removeVertex();

    for ( int i = 0; i < g.vCount(); i++ ) {
        cout << i << " : " << g.getVertex(i) << endl;
    }

    g.setEdge(0, 1, 5);
    g.setEdge(0, 3, 6);
    g.setEdge(1, 2, 8);
    g.setEdge(2, 3, 2);
    g.setEdge(3, 1, 9);

    cout << "W(0, 1) : " << g.getEdge(0, 1) << endl;
    cout << "W(0, 3) : " << g.getEdge(0, 3) << endl;
    cout << "W(1, 2) : " << g.getEdge(1, 2) << endl;
    cout << "W(2, 3) : " << g.getEdge(2, 3) << endl;
    cout << "W(3, 1) : " << g.getEdge(3, 1) << endl;

    cout << "eCount : " << g.eCount() << endl;
    // g.removeEdge(3, 1);
    // cout << "eCount : " << g.eCount() << endl;

    SharedPointer< Array<int> > aj = g.getAdjacent(0);
    for ( int i = 0; i < aj->length(); i++ ) {
        cout << (*aj)[i] << " ";
    }
    cout << endl;

    cout << "ID(1) : " << g.ID(1) << endl;
    cout << "OD(1) : " << g.OD(1) << endl;
    cout << "TD(1) : " << g.TD(1) << endl;
	
    return 0;
}
