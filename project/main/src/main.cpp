/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2019-08-02 00:00:21
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-11 01:58:04
 */

#include <iostream>
#include "MatrixGraph.h"

using namespace std;
using namespace DTLib;

int main(int argc, const char* argv[])
{
	MatrixGraph<3, int, int> g;

    /*    ---->
     *  0        1 ----> 2
     *    <----
     */
    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 2);
    g.setEdge(1, 2, 3);

    cout << "vCount: " << g.vCount() << endl;
    cout << "eCount: " << g.eCount() << endl;
    cout << "ID(1): " << g.ID(1) << endl;
    cout << "OD(1): " << g.OD(1) << endl;
    cout << "TD(1): " << g.TD(1) << endl;

    cout << "W(0, 1): " << g.getEdge(0, 1) << endl;
    cout << "W(1, 0): " << g.getEdge(1, 0) << endl;
    cout << "W(1, 2): " << g.getEdge(1, 2) << endl;

    SharedPointer< Array<int> > aj = g.getAdjacent(1);
    for(int i = 0; i < aj->length(); i++) {
        cout << (*aj)[i] << " ";
    }
    cout << endl;
	
    return 0;
}
