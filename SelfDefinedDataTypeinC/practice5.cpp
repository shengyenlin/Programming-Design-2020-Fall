#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;

const int ARRAY_LEN = 100;
const int MAX = 10000;
const int BINCNT = 10;

void naiveSetRN(int rn [], int len);

int main(){
    int rnArray[ARRAY_LEN] = {0};
    int len = 10;
    int rn = 0;
    naiveSetRN(rnArray, len);
    for (int i = 0; i < len; i++){
        cout << rnArray[i] << " ";
    }
    return 0; 
}

void naiveSetRN (int rn [], int len){
    //set seed
    time_t t = time(nullptr);
    srand(t);
    for (int i = 0; i < len; i++){
        int randVal = rand() % MAX;
        for (int j = 0; j < i; j++){
            if (randVal == rn[j]){
                randVal = rand()% MAX;
            }
        }
        rn[i] = randVal;
    }
}