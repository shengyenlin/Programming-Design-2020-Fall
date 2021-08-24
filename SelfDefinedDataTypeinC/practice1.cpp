#include<iostream>
using namespace std;

const int ARRAY_LEN = 1000;

void bubbleSort(const int unsorted[], int sorted[], int len);
void insertionSort(const int unsorted[], int sorted[], int len);
int main(){
    int len = 0;
    cin >> len;
    int unsorted[ARRAY_LEN] = {0};
    int sorted[ARRAY_LEN] = {0};
    for (int i = 0; i < len; i++){
        cin >> unsorted[i];
    }
    insertionSort(unsorted, sorted, len);
    for (int i = 0; i < len; i++){
        cout << sorted[i];
        if (i != len - 1){
            cout << " ";
        }
    }
    return 0;
}
void bubbleSort(const int unsorted[], int sorted[], int len){
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
            }
        }
    }
}

void insertionSort(const int unsorted[], int sorted[], int len){
    //copy array
    for (int i = 0; i < len; i++){
        sorted[i] = unsorted[i];
    }
    //insertion sort
    for (int i = 1; i < len; i++){
        for (int j = i; j > 0; j--){
            if (sorted[j-1] > sorted[j]){
                int temp = sorted[j-1];
                sorted[j-1] = sorted[j];
                sorted[j] = temp; 
            }
        }
    }

}