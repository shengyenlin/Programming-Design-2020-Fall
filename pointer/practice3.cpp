#include<iostream>
using namespace std;

int* maxPtr(int* a, int* b);

int main(){
    int a = 0, b = 0;
    cin >> a >> b;
    cout << *maxPtr(&a, &b) << '\n';
    return 0;
}

int* maxPtr(int* a, int* b){
    return *a > *b ? a : b;
}