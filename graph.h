#include<iostream>
#include<string>
#include<stack>
#include<ctime>

using namespace std;

class graph{
private:
    void DFS_use_recursion(int u, bool visited[]);
    int get_vertex_label(int vertex);
    int get_edge_label(int vertex1, int vertex2);
    int ** adj_matrix;
    int * v_labels;
    int v_size;
    int graph_num;
    int start, end;
public:
    graph(){}
    graph(int v_size){
        this->v_size = v_size;
        adj_matrix = new int *[v_size];
        for(int i = 0 ; i < v_size ; i++){
            adj_matrix[i] = new int[v_size];
            memset(adj_matrix[i], 0, sizeof(int) * v_size);
        }
    }
    void set_edge(int vertex1, int vertex2, int edge_label);
    void set_v_labels(int * v_labels);
    void set_graph_num(int graph_num);
    void print_matrix();
    void print_vertex_label();
    void print_graph_num();
    void DFS_use_recursion();
    void DFS_use_stack();
    int get_edit_cost(graph g);
    int get_v_size();
};

// set graph
void graph :: set_edge(int vertex1, int vertex2, int edge_label){
    this->adj_matrix[vertex1][vertex2] = edge_label;
    this->adj_matrix[vertex2][vertex1] = edge_label;
}

void graph :: set_v_labels(int * v_labels){
    this->v_labels = v_labels;
}

void graph :: set_graph_num(int graph_num){
    this->graph_num = graph_num;
}

// get graph
int graph :: get_v_size(){
    return v_size;
}


// print graph
void graph :: print_matrix(){
    for(int i = 0 ; i < v_size ; i++){
        for(int j = 0 ; j < v_size ; j++){
            cout << adj_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void graph :: print_vertex_label(){
    for(int i = 0 ; i < v_size ; i++){
        cout << "vertex" << i << "'s label : " << v_labels[i] << endl;
    }
}

void graph :: print_graph_num(){
    cout << "# " << this->graph_num << endl; 
}

// calculate dfs
void graph :: DFS_use_recursion(){
    bool visited[v_size];
    memset(visited, false, sizeof(bool) * v_size);
    start = clock();
    DFS_use_recursion(0, visited);
    end = clock();
    cout << "\nuse recursion time : " << (double)(end - start) << "ms" << endl;
}

void graph :: DFS_use_recursion(int u, bool visited[]){
    cout << u << " ";
    visited[u] = true;
    for(int i = 0 ; i < v_size ; i++){
        if(adj_matrix[u][i] != 0 && !visited[i]){
            DFS_use_recursion(i, visited);
        }
    }
}

void graph :: DFS_use_stack() {
    stack<int> stk;
    bool visited[v_size];
    memset(visited, false, sizeof(bool) * v_size);
    int u = 0;
    start = clock();
	int current = u;
	stk.push(current);
	visited[current] = true;
    cout << current<< " ";
	while (stk.size()) {
		current = stk.top();
		for (int i = 0; i < v_size; i++) {
			if (adj_matrix[current][i] != 0 && !visited[i]) {
				current = i;
				stk.push(current);
				visited[current] = true;
                cout << current<< " ";
                break;
			}else if(i == v_size-1){
                stk.pop();
            }
		}
	}
    end = clock();
    cout << "\nuse stack time : " << (double)(end - start) << "ms" << endl;
}

// calculate edit cost
int graph :: get_edit_cost(graph g){
    int cost = 0;
    int max_size = get_v_size() > g.get_v_size() ? get_v_size() : g.get_v_size();
    for(int i = 0 ; i < max_size ; i++){
        if(this->get_vertex_label(i) != g.get_vertex_label(i)){
            cost++;
        }
    }
    for(int i = 1 ; i < max_size ; i++){
        for(int j = i-1 ; j >= 0 ; j--){
            if(this->get_edge_label(i, j) != g.get_edge_label(i, j)){
                cost++;
            }
        }
    }
    return cost;
}

int graph :: get_vertex_label(int vertex){
    if(vertex < v_size){
        return v_labels[vertex];
    }else{
        return -1;
    }
}

int graph :: get_edge_label(int vertex1, int vertex2){
    if(vertex1 < v_size && vertex2 < v_size){
        return adj_matrix[vertex1][vertex2];
    }else{
        return 0;
    }
}