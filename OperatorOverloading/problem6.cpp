#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class MyVector{
    private:
        int n;
        double* m;
    public:
        MyVector(); 
        MyVector(int dim, double value = 0);
        MyVector(int dim, double v[]);
        MyVector(const MyVector& v);
        ~MyVector();
        int getN() {return n;}
        double operator[] (int i) const;
        //return reference, so that the instance variable can be modified
        double& operator[] (int i);
        bool operator== (const MyVector& v) const;
        bool operator== (const double d);
        const MyVector& operator= (const MyVector& v);
        void print() const;
};

//we need headers:)
bool operator== (double d, const MyVector& v);
const MyVector operator- (const MyVector& v);

int main(){
    double d = 1.23;
    double m[3] = {-d, -d, -d};
    MyVector v(3, m);
    v.print();
    v = -v;
    v.print();
    if (v == d){
        cout << "Equal!";
    } else{
        cout << "Unequal!";
    }
    return 0;
}

//global functions
bool operator== (double d, const MyVector& v){
    return (v == d); 
}

//not return reference, since v2 will disappear at the end of the function
//return v2 only return its member variable?
const MyVector operator- (const MyVector& v){
    MyVector v2(v);
    for (int i = 0; i < v2.getN(); i++){
        v2[i] = -v2[i];
    }
    return v2;
}

//member functions
//use member initializers to initialize constant variable
MyVector::MyVector():n(0){
    m = nullptr;
}

MyVector::MyVector(int dim, double m):n(dim){
    this->m = new double[n];
    for (int i = 0;i < n; i++){
        this->m[i] = m;
    }
}

MyVector::MyVector(int dim, double v[]):n(dim){
    //this->n: instance variable
    //n: local variable
    //this->n = n;
    this->m = new double[n];
    for (int i = 0; i < n; i++){
        this->m[i] = v[i];
    }
}


//copy constructor, shallow copy by default
MyVector::MyVector(const MyVector& v):n(v.n){
    //deep copy manually!!
    m = new double[n];
    for (int i = 0; i < n; i++){
        m[i] = v.m[i];
    }
}


void MyVector::print() const{
    cout << "(";
    for (int i = 0; i < this->n - 1; i++){
        cout << m[i] << ", ";
    }
    cout << m[n-1] << ")\n";
}

//allow a1 = a2 = a3
const MyVector& MyVector::operator=(const MyVector& v){
    //safe time for a1 = a1
    if (this != &v){
        cout << "!" << endl;
        if (this->n != v.n){
            //avoid memory leak
            delete [] this->m;
            this->n = v.n;
            this->m = new double[this->n];
        }
        for (int i = 0; i < n; i++){
            this->m[i] = v.m[i];
        }
    }
    
    return *this;
}


bool MyVector::operator==(const MyVector& v) const{
    if (n != v.n){
        return false;
    }
    else{
        for (int i = 0; i < n; i++){
            if (m[i] != v.m[i])
                return false;
        }
    }
    return true;
}

bool MyVector::operator== (const double d){
    for (int i = 0; i < n; i++){
        if (abs(m[i] - d) > 0.00001){
            //cout << m[i];
            return false;
        }
    }
    return true;
}

double MyVector::operator[](int i) const{
    if (i < 0 || i >= n){
        //terminate the program and send 1 to the operating system
        exit(1);
    }
    else{
        return this->m[i];
    }
}

double& MyVector::operator[](int i){
    if (i < 0 || i >= n){
        exit(1);
    }
    else{
        return this->m[i];
    }
}


MyVector::~MyVector(){
    delete [] m;
}

