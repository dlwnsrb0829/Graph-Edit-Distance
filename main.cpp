#include<iostream>
#include"dataSet.h"
using namespace std;

int main(){
    dataSet d = dataSet("Graph1");
    graph g1 = d.get_graph();
    g1.print_graph_num();
    g1.print_matrix();

    d = dataSet("Graph2");
    graph g2 = d.get_graph();
    g2.print_graph_num();
    g2.print_matrix();

    cout << g2.get_GED(g1) << endl;

    return 0;
}