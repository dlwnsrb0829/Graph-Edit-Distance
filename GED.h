#include<iostream>
#include<ctime>
#include"mapping.h"

using namespace std;

struct Index
{
    int index_id;
    int cost;
    Index(int index_id, int cost){
        this->index_id = index_id;
        this->cost = cost;
    }
    bool operator<(const Index index) const {
        return this->cost > index.cost;
    }
};


class GED{
private : 
    graph g1;
    graph g2;
    bool *search_array;
    int *index_array;
    int max_size;
    int min_cost;
    int start, end;
    int index_mapping(int index);
    int index_unmapping(int index);
    bool is_full_mapping();
    int get_edit_cost();
    void print();
    void calculate_GED();

public :
    GED(graph g1, graph g2){
        this->g1 = g1;
        this->g2 = g2;
        this->max_size = g1.get_v_size() > g2.get_v_size() ? g1.get_v_size() : g2.get_v_size();

        search_array = new bool[max_size];
        memset(search_array, true, sizeof(bool) * max_size);
        index_array = new int[max_size];
        memset(index_array, -1, sizeof(int) * max_size);
        min_cost = -1;
    }
    int get_GED();
};

int GED :: index_mapping(int index){
    int n = -1;
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

int GED :: index_unmapping(int index){
    search_array[index] = true;
    for(int i = 0 ; i < max_size ; i++){
        if(index_array[i] == index){
            index_array[i] = -1;
        }
    }
    return 0;
}

bool GED :: is_full_mapping(){
    bool result = true;
    for(int i = 0 ; i < max_size ; i++){
        if(index_array[i] == -1){
            result = false;
        }
    }
    return result;
}

void GED :: print(){
    for(int i = 0 ; i < max_size ; i++){
        if(index_array[i] != -1){
            cout << "g1 : " << i << ", g2 = " << index_array[i] << endl;
        }
    }
}

int GED :: get_edit_cost(){
    int cost = 0;
    for(int i = 0 ; i < max_size ; i++){
        if(index_array[i] != -1){
            if(g1.get_vertex_label(i) != g2.get_vertex_label(index_array[i])){
                cost++;
            }
        }
    }
    for(int i = 1 ; i < max_size ; i++){
        for(int j = i-1 ; j >= 0 ; j--){
            if(index_array[i] != -1 && index_array[j] != -1){
                if(g1.get_edge_label(i, j) != g2.get_edge_label(index_array[i], index_array[j])){
                    cost++;
                }
            }
        }
    }
    return cost;
}

void GED :: calculate_GED(){
    priority_queue<Index> q;
    for(int i = 0 ; i < max_size ; i++){
        if(search_array[i]){
            index_mapping(i);
            int edit_cost = get_edit_cost();
            Index index = Index(i, edit_cost);
            index_unmapping(i);
            q.push(index);
        }
    }
    while(!q.empty()){
        Index index = q.top();
        q.pop();
        int n = index_mapping(index.index_id);
        if(index_array[max_size-1] != -1){
            if(min_cost == -1){
                min_cost = index.cost;
            }else{
                if(min_cost >= index.cost){
                    min_cost = index.cost;
                }
            }
        }
        if(min_cost != -1 && min_cost <= index.cost){
            index_unmapping(index.index_id);
            return;
        }
        calculate_GED();
        index_unmapping(index.index_id);
    }
}

int GED :: get_GED(){
    start = clock();
    calculate_GED();
    end = clock();
    cout << "\nuse priority queue time : " << (double)(end - start) << "ms" << endl;
    return min_cost;
}

// void GED :: calculate_GED(){
//     queue<int> q;
//     for(int i = 0 ; i < max_size ; i++){
//         if(search_array[i]){
//             q.push(i);
//         }
//     }
//     while(!q.empty()){
//         int temp = q.front();
//         q.pop();
//         int n = index_mapping(temp);
//         // print();
//         int cost = get_edit_cost();
//         // cout << "cost : " << cost << endl;
//         if(index_array[max_size-1] != -1){
//             min_cost = cost;
//         }
//         // cout << "---------------------" << endl;
//         if(min_cost != -1 && min_cost <= cost){
//             search_array[temp] = true;
//             index_array[n] = -1;
//             return;
//         }
//         calculate_GED();
//         search_array[temp] = true;
//         index_array[n] = -1;
//     }
// }

// void GED :: calculate_GED(){
//     priority_queue<Index> q;
//     for(int i = 0 ; i < max_size ; i++){
//         if(search_array[i]){
//             int a = index_mapping(i);
//             int temp_cost = get_edit_cost();
//             Index temp_index = Index(i, temp_cost);
//             index_unmapping(i);
//             q.push(temp_index);
//         }
//     }
//     while(!q.empty()){
//         Index temp = q.top();
//         q.pop();
//         int n = index_mapping(temp.index_id);
//         // print();
//         // cout << "cost : " << temp.cost << endl;
//         if(is_full_mapping()){
//             if(min_cost == -1){
//                 min_cost = temp.cost;
//             }else{
//                 if(min_cost >= temp.cost){
//                     min_cost = temp.cost;
//                 }
//             }
//         }
//         // cout << "---------------------" << endl;
//         if(min_cost != -1 && min_cost <= temp.cost){
//             index_unmapping(temp.index_id);
//             return;
//         }
//         calculate_GED();
//         index_unmapping(temp.index_id);
//     }
// }
