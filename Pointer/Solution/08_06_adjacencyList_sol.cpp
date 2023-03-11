#include<iostream>
using namespace std;

const int NODE_CNT_MAX = 100;

int inputGraphInfo(int* neighbors[], int degrees[]);
void printGraph(int* neighbors[], const int degrees[], int nodeCnt);
void printGraphMatrix(int* neighbors[], const int degrees[], int nodeCnt);
void releaseMemory(int* neighbors[], int nodeCnt);
bool isNeighbor(int* neighbors[], const int degrees[], int node1, int node2);

int main()
{
  int* neighbors[NODE_CNT_MAX] = {0};
  int degrees[NODE_CNT_MAX] = {0};
  int nodeCnt = inputGraphInfo(neighbors, degrees);
  printGraphMatrix(neighbors, degrees, nodeCnt);
  releaseMemory(neighbors, nodeCnt);

  return 0;
}

int inputGraphInfo(int* neighbors[], int degrees[])
{
  int nodeCnt = 0;
  cin >> nodeCnt;
  for(int i = 0; i < nodeCnt; i++)
  {
    // cout << "Node " << i 
    //     << "\'s degree is: ";
    cin >> degrees[i];
    neighbors[i] = new int[degrees[i]];
    // cout << "Node " << i 
    //      << "\'s neighbors: ";
    for(int j = 0; j < degrees[i]; j++)
      cin >> neighbors[i][j];
  }  
  return nodeCnt;
}

void printGraph(int* neighbors[], const int degrees[], int nodeCnt)
{
  for(int i = 0; i < nodeCnt; i++)
  {
    // cout << "Node " << i << ": ";
    for(int j = 0; j < degrees[i]; j++)
      cout << neighbors[i][j] << " ";
    cout << "\n";
  }
}

void printGraphMatrix(int* neighbors[], const int degrees[], int nodeCnt)
{
  for(int i = 0; i < nodeCnt; i++)
  {
    for(int j = 0; j < nodeCnt - 1; j++)
      cout << isNeighbor(neighbors, degrees, i, j) << " ";   
    cout << isNeighbor(neighbors, degrees, i, nodeCnt - 1);
    cout << "\n";
  }  
}

void releaseMemory(int* neighbors[], int nodeCnt)
{
  for(int i = 0; i < nodeCnt; i++)
    delete [] neighbors[i];
}

bool isNeighbor(int* neighbors[], const int degrees[], int node1, int node2)
{
  for(int i = 0; i < degrees[node1]; i++)
  {
    if(node2 == neighbors[node1][i])
      return true;
  }
  return false;
}
