#include<iostream>
#include<queue>

class mapping{
private : 
    int ** map;

public : 
    void test(int size);
    mapping(){
        map = new int*[2];
        for(int i = 0 ; i < 2 ; i++){
            map[i] = new int[4];
            memset(map[i], 0, sizeof(int) * 4);
        }
        for(int i = 0 ; i < 4 ; i++){
            map[0][i] = i;
        }
    }

};

void mapping :: test(int size){
    queue<int> q;
    if(size == 0){
        for(int i = 0 ; i < 4 ; i++){
            cout << map[1][i] << " ";
        }
        cout << endl;
        return;
    }
    for(int i = 0 ; i < size ; i++){
        q.push(i);
    }
    test(size-1);
    q.pop();
}