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
    bool is_edge(int vertex1, int vertex2);
    int get_edge_cost(int max_size, graph g1, graph g2);
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
    int get_GED(graph g);
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

// calculate GED
int graph :: get_GED(graph g){
    int cost = 0;
    int max_size = get_v_size() > g.get_v_size() ? get_v_size() : g.get_v_size();
    cout << "vertex label cost" << endl;
    for(int i = 0 ; i < max_size ; i++){
        if(this->get_vertex_label(i) != g.get_vertex_label(i)){
            cout << "i = " << i << endl;
            cout << "g1 = " << this->get_vertex_label(i) << endl;
            cout << "g2 = " << g.get_vertex_label(i) << endl << endl;
            cost++;
        }
    }
    cost += this->v_size < g.v_size ? get_edge_cost(max_size, *(this), g) : get_edge_cost(max_size, g, *(this));
    return cost;
}

int graph :: get_edge_cost(int max_size, graph g1, graph g2){ // g1이 작은거
    int cost = 0;
    cout << "edge label cost" << endl;
    for(int i = 0 ; i < g1.v_size ; i++){
        for(int j = i + 1 ; j < g1.v_size ; j++){
            if(g1.get_edge_label(i, j) != 0 && g2.get_edge_label(i, j) != 0){
                if(g1.get_edge_label(i, j) != g2.get_edge_label(i, j)){
                    cout << "i = " << i << " | j = " << j << endl;
                    cout << "g1 = " << g1.get_edge_label(i, j) << endl;
                    cout << "g2 = " << g2.get_edge_label(i, j) << endl << endl;
                    cout << endl;
                    cost++;
                }
            }
        }
    }
    cout << "edge cost" << endl;
    for(int i = 1 ; i < max_size ; i++){
        for(int j = i-1 ; j >= 0 ; j--){
            if(i < g1.v_size){
                if(g1.is_edge(i, j) ^ g2.is_edge(i, j)){
                    cout << "i = " << i << " | j = " << j << endl;
                    cout << "g1 = " << g1.is_edge(i, j) << endl;
                    cout << "g2 = " << g2.is_edge(i, j) << endl << endl;
                    cout << endl;
                    cost++;
                }
            }else{
                if(g2.is_edge(i, j)){
                    cout << "i = " << i << " | j = " << j << endl;
                    cout << "g1 = None" << endl;
                    cout << "g2 = " << g2.is_edge(i, j) << endl << endl;
                    cout << endl;
                    cost++;
                }
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
    return adj_matrix[vertex1][vertex2];
}

bool graph :: is_edge(int vertex1, int vertex2){
    if(adj_matrix[vertex1][vertex2] != 0){
        return true;
    }else{
        return false;
    }
}