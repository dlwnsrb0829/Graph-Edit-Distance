#include<iostream>
#include"mapping.h"

using namespace std;

class GED{
private : 
    graph g1;
    graph g2;
    bool *search_array;
    int *index_array;
    int max_size;
    int index_mapping(int index);

public :
    GED(graph g1, graph g2){
        this->g1 = g1;
        this->g2 = g2;
        this->max_size = g1.get_v_size() > g2.get_v_size() ? g1.get_v_size() : g2.get_v_size();

        search_array = new bool[max_size];
        memset(search_array, true, sizeof(bool) * max_size);
        index_array = new int[max_size];
        memset(index_array, -1, sizeof(int) * max_size);
    }
    int get_edit_cost();
    void test();
    void print();

};

int GED :: get_edit_cost(){
    int cost = 0;
    // int max_size = g1.get_v_size() > g2.get_v_size() ? g1.get_v_size() : g2.get_v_size();
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
    return cost;
}

int GED :: index_mapping(int index){
    int n=0;
    if(index < max_size){
        search_array[index] = false;
        for(int i = 0 ; i < max_size ; i++){
            if(index_array[i] == -1){
                index_array[i] = index;
                n = i;
                break;
            }
        }
    }
    return n;
}

void GED :: test(){
    queue<int> q;
    for(int i = 0 ; i < max_size ; i++){
        if(search_array[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int temp = q.front();
        q.pop();
        int n = index_mapping(temp);
        print();
        cout << "-----" << endl;
        test();
        search_array[temp] = true;
        index_array[n] = -1;
    }
    
}

void GED :: print(){
    for(int i = 0 ; i < max_size ; i++){
        if(index_array[i] != -1){
            cout << "g1 : " << i << ", g2 = " << index_array[i] << endl;
        }
    }
}