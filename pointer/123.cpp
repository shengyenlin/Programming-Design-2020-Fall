#include<iostream>
using namespace std;

void changePtr(int* pInt){
    int g_int = 0;
    *pInt = g_int;
}
int main(){
    int localInt = 1;
    int* localPInt = &localInt;
    changePtr(localPInt);
    cout << *localPInt;
}