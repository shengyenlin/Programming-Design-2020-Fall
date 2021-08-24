#include <iostream>
using namespace std;

int main(){
    int a = 0;
    //cout << a << "\n";
    int* aPtr = &a;
    cin >> *aPtr;
    cout << a;
    return 0;
}