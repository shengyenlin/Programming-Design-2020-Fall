#include <iostream>
using namespace std;

int* max(int, int);

int main(){
    int a = 0, b = 0;
    cin >> a >> b;
    int* maxAddr = max(a, b);
    cout << *maxAddr << "\n";
    delete maxAddr;
    return 0;
}

int* max(int a, int b){
    //the allocated space will exist after the function ends
    int* cPtr = new int(a);
    if (b > a){
        *cPtr = b;
    }
    return cPtr;
}