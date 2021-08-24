#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;

const int ARRAY_LEN = 100;
const int MAX = 10000;
const int BINCNT = 10;

void setRN(int rn [], int len);
void bubbleSort(const int unsorted[], int sorted[], int len);
void hist(const int value[], int len, int freq[], int binCnt);

int main(){
    int rnArrayUnsorted[ARRAY_LEN] = {0};
    int rnArraySorted[ARRAY_LEN] = {0};
    int len = 10;
    int rn = 0;
    setRN(rnArrayUnsorted, len);
    bubbleSort(rnArrayUnsorted, rnArraySorted, len);
    for (int i = 0; i < len; i++){
        cout << rnArraySorted[i] << " ";
    }
    cout << "\n";
    //int value[BINCNT] = {0, 10, 100};
    int freq[BINCNT] = {0};
    hist(rnArraySorted, len, freq, BINCNT);
    for (int i = 0; i < BINCNT; i++){
        cout << freq[i] << " ";
    }
    return 0; 
}

void setRN (int rn [], int len){
    //set seed
    time_t t = time(nullptr);
    srand(t);
    for (int i = 0; i < len; i++){
        rn[i] = rand() % MAX;
    }
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

void hist(const int value[], int len, int freq[], int binCnt){
    int interval = 1000;
    int binsValue = 0 + interval;
    int count = 0;
    for (int i = 0; i < len; i++){
        if (value[i] > binsValue) {
            count++;
            binsValue = binsValue + interval;
            //cout << "!" << " ";
            if (count == binCnt){
                break;
            }
        }
        freq[count]++;
    }
}