#include<iostream>
using namespace std;

const int NODE_CNT_MAX = 100;

int inputGraphInfo(int* neighbors[], int degrees[]);
void printGraph(int* neighbors[], const int degrees[], int nodeCnt);
void releaseMemory(int* neighbors[], int nodeCnt);

int main()
{
    int* neighbors[NODE_CNT_MAX] = {0};
    int degrees[NODE_CNT_MAX] = {0};
    int nodeCnt = inputGraphInfo(neighbors, degrees);
    //cout << "\n";
    printGraph(neighbors, degrees, nodeCnt);
    releaseMemory(neighbors, nodeCnt);
    return 0;
}

int inputGraphInfo(int* neighbors[], int degrees[]){
    //有幾個node
    int nodeCnt = 0;
    cin >> nodeCnt;
    for(int i = 0; i < nodeCnt; i++){
        // cout << "Node " << i
        // << "\'s degree is: ";
        //每個node有幾個neighbor(有多深)
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

void printGraph(int* neighbors[], const int degrees[], int nodeCnt){
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
void releaseMemory(int* neighbors[], int nodeCnt)
{
    for(int i = 0; i < nodeCnt; i++)
        delete [] neighbors[i];
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