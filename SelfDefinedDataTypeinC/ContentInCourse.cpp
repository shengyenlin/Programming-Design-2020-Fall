#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;


struct Point{
    int x;
    int y;
    //member functions
    double distOri();
    //the syntax below is equivalent, but syntax above is preferred
    /*
    double distOri(){
        return sqrt(pow(x, 2) + pow(y, 2));
    }
    */
};

struct Randomizer{
    int a;
    int b;
    int c;
    int cur;
    double rand();
};

typedef double Dollar;
typedef Point Vector;

Vector vector(Point A, Point B){
    Point vecXY;
    vecXY.x = B.x - A.x;
    vecXY.y = B.y - A.y;
    return vecXY;
}

int main(){
    Point a = {0, 0}, b = {10, 20};
    Vector vecAB = vector(a, b);
    cout << vecAB.x << " ";
    cout << vecAB.y << "\n";
    cout << vecAB.distOri() << "\n";
    //partial assignment, equivalent to Point c = {5, 0};
    Point c = {5};
    
    //a point (structure) = 8 bytes
    cout << sizeof(Point) << " ";

    //typedef: create a new data type from ANOTHER DATA TYPE
    //you can change the type of dollar to int or other datatypes without changing the whole program
    Dollar nt;
    Dollar us;
    //cin >> us;
    //nt = us * 29;
    //cout << nt << "\n";

    //ctime library
    clock_t sTime = clock();
    for (int i = 0; i < 10021156; i++){
        continue;
    }
    clock_t eTime = clock();
    cout << sTime << " " << eTime << "\n";
    cout << static_cast<double>(eTime - sTime) / CLOCKS_PER_SEC << "\n";
    
    //set seed
    time_t t = time(nullptr);
    srand(t);
    //get random numbers
    int rn = 0;
    for (int i = 0; i < 10; i++){
        rn = rand();
        cout << rn << " ";
    }
    cout << '\n';

    //self-defined randomizer
    Randomizer r1 = {10, 4, 51, 5};
    for (int i = 0; i < 10; i++){
        cout << r1.rand() << " ";
    }
    cout << "\n";
    return 0;
}

double Point::distOri(){
    return sqrt(pow(x, 2) + pow(y, 2));
}

double Randomizer::rand(){
    cur = (a * cur + b) % c;
    return cur;
}