#include<iostream>
#include"dataSet.h"
using namespace std;

int main(){
    dataSet d = dataSet("SAMPLE");
    graph g = d.get_graph();
    g.print_graph_num();
    g.print_matrix();
    // g.print_vertex_label();
    g.DFS_use_stack();
    g.DFS_use_recursion();

    return 0;
}