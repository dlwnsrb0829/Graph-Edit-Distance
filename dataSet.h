#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>
#include<string>
#include<stack>
#include<cstring>
#include"graph.h"

using namespace std;

class dataSet{
private:
    int v_size;
    int e_size;
    bool is_first_edge;
    string fileName;
    graph g;
    vector<int> split_vector;
    vector<int> split(string input, char delimiter, string type);

public:
    dataSet(){};
    dataSet(string fileName){
        this->fileName = fileName;
        read_file();
    }
    void read_file();
    graph get_graph();
};

void dataSet :: read_file(){
    ifstream readFile;
    string v_label = "";
    int graph_num = 0;
    readFile.open(this->fileName);
    if(readFile.is_open()){
        char arr[256];
        while(!readFile.eof()){
            readFile.getline(arr, 256);
            switch (arr[0]){
                case 't':
                    split_vector = split(arr, ' ', "graph_num");
                    graph_num = split_vector[0];
                    this->v_size = 0;
                    this->e_size = 0;
                    this->is_first_edge = true;
                    v_label = "";
                    break;
                case 'v':
                    split_vector = split(arr, ' ', "data");
                    v_label += to_string(split_vector[1]) + " ";
                    v_size++;
                    break;
                case 'e':
                    if(this->is_first_edge){
                        this->is_first_edge = false;
                        split_vector = split(v_label, ' ', "");
                        int * v_labels = new int[v_size];
                        for(int i = 0 ; i < v_size ; i++){
                            v_labels[i] = split_vector[i];
                        }
                        g = graph(v_size);
                        g.set_v_labels(v_labels);
                        g.set_graph_num(graph_num);
                    }
                    split_vector = split(arr, ' ', "data");
                    g.set_edge(split_vector[0], split_vector[1], split_vector[2]);
                    e_size++;
                    break;
                default:
                    break;
            }
        }
    }
    readFile.close();
}

graph dataSet :: get_graph(){
    return this->g;
}

vector<int> dataSet :: split(string input, char delimiter, string type) {
    vector<int> result;
    if(!type.compare("data")){
        input = input.substr(2);
    }else if(!type.compare("graph_num")){
        input = input.substr(4);
    }
    stringstream ss(input);
    string temp;
    while (getline(ss, temp, delimiter)) {
        result.push_back(stoi(temp));
    }
    return result;
}