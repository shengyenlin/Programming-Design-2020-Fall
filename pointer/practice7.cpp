#include<iostream>
using namespace std;

const int NODE_CNT_MAX = 100;

int inputGraphInfo(int**& neighbors, int*& degrees);
void printGraph(int** neighbors, const int* degrees, int nodeCnt);
void releaseMemory(int** neighbors, int* degrees, int nodeCnt);

int main()
{
    int** neighbors = nullptr;
    int* degrees = nullptr;
    int nodeCnt = inputGraphInfo(neighbors, degrees);
    //cout << neighbors << " " << degrees << " ";
    //cout << "\n";
    printGraph(neighbors, degrees, nodeCnt);
    releaseMemory(neighbors, degrees, nodeCnt);
    return 0;
}

//有在裡面呼叫到neighbor就要做call by reference
//還是不太懂
int inputGraphInfo(int**& neighbors, int*& degrees){
    //有幾個node
    int nodeCnt = 0;
    cin >> nodeCnt;
    neighbors = new int*[nodeCnt];
    degrees = new int[nodeCnt];
    for(int i = 0; i < nodeCnt; i++){
        cin >> degrees[i];
        neighbors[i] = new int[nodeCnt]();
        // cout << "Node " << i
        // << "\'s neighbors: ";
        for(int j = 0; j < degrees[i]; j++){
            int neighbor = 0;
            cin >> neighbor;
            neighbors[i][neighbor] = 1;
        }
    }
    return nodeCnt;
}

void printGraph(int** neighbors, const int* degrees, int nodeCnt){
    for(int i = 0; i < nodeCnt; i++){
        // cout << "Node " << i << ": ";
        for(int j = 0; j < nodeCnt; j++){
            cout << neighbors[i][j];
            if (j != nodeCnt - 1){
                cout << " ";
            }
        }
        cout << "\n";
    }
}
void releaseMemory(int** neighbors, int* degrees, int nodeCnt){
    for(int i = 0; i < nodeCnt; i++)
        delete [] neighbors[i];
    delete[] neighbors;
    delete[] degrees;
}

/*
example1
intput:
4
1 1
2 0 2
2 1 3
1 2

output:
1
0 2
1 3
2

example2    
intput:
4
2 1 3
2 0 2
2 1 3
2 0 2

output:
1 3
0 2
1 3
0 2
*/