#include<iostream>
#include"mapping.h"

using namespace std;

class GED{
private : 
    graph g1;
    graph g2;

public :
    GED(graph g1, graph g2){
        this->g1 = g1;
        this->g2 = g2;
    }
    int get_edit_cost();


};

int GED :: get_edit_cost(){
    int cost = 0;
    int max_size = g1.get_v_size() > g2.get_v_size() ? g1.get_v_size() : g2.get_v_size();
    for(int i = 0 ; i < max_size ; i++){
        if(g1.get_vertex_label(i) != g2.get_vertex_label(i)){
            cost++;
        }
    }
    for(int i = 1 ; i < max_size ; i++){
        for(int j = i-1 ; j >= 0 ; j--){
            if(g1.get_edge_label(i, j) != g2.get_edge_label(i, j)){
                cost++;
            }
        }
    }
    mapping m;
    m.test(4);
    return cost;
}