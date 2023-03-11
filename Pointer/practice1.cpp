#include<iostream>
using namespace std;

int main(){
    int anInteger = 0;
    cout << &anInteger << "\n";
    for (int i = 0; i < 10; i++){
        int anotherInteger = 0;
        cout << &anotherInteger << " ";
    }   
    return 0;
}