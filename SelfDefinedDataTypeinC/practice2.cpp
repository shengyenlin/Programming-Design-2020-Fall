#include<iostream>
#include<cmath>
using namespace std;

const int ARRAY_LEN = 1000;

struct Point{
    int x;
    int y;
};

void vectorSort (const Point unsorted[], int sortedIndices [], int len);
void bubbleSort(const int unsorted[], int sorted[], int sortedIndices [], int len);

int main(){
    int len = 0;
    cin >> len;
    Point unsortedPointArray[ARRAY_LEN] = {0};
    int sortedIndices[ARRAY_LEN] = {0};
    for (int i = 0; i < len; i++){
        sortedIndices[i] = i + 1;
    }
    for (int i = 0; i < len; i++){
        cin >> unsortedPointArray[i].x;
    }
    for (int i = 0; i < len; i++){
        cin >> unsortedPointArray[i].y;
    }
    vectorSort(unsortedPointArray, sortedIndices, len);
    for (int i = 0; i < len; i++){
        cout << sortedIndices[i];
        if (i != len - 1){
            cout << " ";
        }
    }
    return 0;
}

void vectorSort (const Point unsorted[], int sortedIndices[], int len){
    int sumArray[ARRAY_LEN] = {0};
    int sortedArray[ARRAY_LEN] = {0};
    for (int i = 0; i < len; i++){
        sumArray[i] = pow(unsorted[i].x, 2) + pow(unsorted[i].y, 2);
    }
    bubbleSort(sumArray, sortedArray, sortedIndices, len);
}

void bubbleSort(const int unsorted[], int sorted[], int sortedIndices[],int len){
    //copy array
    for (int i = 0; i < len; i++){
        sorted[i] = unsorted[i];
    }
    //bubble sort
    for (int i = 0; i < len; i++){
        for (int j = 0; j < len - i - 1; j++){
            if (sorted[j] > sorted[j+1]){
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;

                int temp_ind = sortedIndices[j];
                sortedIndices[j] = sortedIndices[j + 1];
                sortedIndices[j + 1] = temp_ind;
            }
        }
    }
}

/*
3
9 4 5
2 8 7

3 2 1

*/

/*
3
9 4 5
2 9 9

1 2 3
*/

/*
4
9 4 5 7
2 8 7 3

4 3 2 1
*/
