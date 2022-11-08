#include<iostream>
#include"dataSet.h"
#include"GED.h"
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

    GED ged = GED(g1, g2);

    // cout << g1.get_v_size() << " " << g2.get_v_size() << endl;
    // cout << ged.get_edit_cost() << endl;
    // ged.test_GED();
    cout << "GED : " << ged.get_GED() << endl;

    // cout << g2.get_edit_cost(g1) << endl;

    return 0;
}