#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

class MyVector{
    private:
        int n;
        double* m;
        //disallow assignment between object
        //void operator= (MyVector v) {};
    public:
        MyVector(); 
        MyVector(int dim, double value = 0);
        MyVector(int dim, double v[]);
        MyVector(const MyVector& v);
        ~MyVector();
        //const function can only be used with const object/instance
        int constGetN() const {return n;}
        int getN() {return n;}
        int constGetM(int i) const {return m[i];}
        int getM(int i) const {return m[i];}
        //void setN(int v) {n = v;}
        //use call by reference to avoid calling copy constructor
        //operator: use to overload operator
        bool operator== (const MyVector& v) const;
        bool operator== (const double d);
        bool operator< (const MyVector& v) const;
        bool operator!= (const MyVector& v) const;
        MyVector& operator= (const MyVector& v);
        const MyVector& operator+= (const MyVector& v);
        const MyVector operator+ (const MyVector& v);
        const MyVector operator+ (int d);
        double operator[] (int i) const;
        //return reference, so that the instance variable can be modified
        //we may write v[1] = 5;
        double& operator[] (int i);
        //constant function can be called by constant and non-constant instance
        void print() const;
    //friend functions and class: private objects in this class can be accessed by your FRIEND!
    friend void test();
    friend class Test;
    friend const MyVector operator+ (const MyVector& v, int d);
};

//create a global function to allow 4 + vector
//need to be a friend of MyVector class in order to retrieve the instance variable
const MyVector operator+ (const MyVector& v, int d);
const MyVector operator+ (int d, const MyVector& v);
const MyVector operator+ (const MyVector& v1, const MyVector& v2);

//we need headers:)
bool operator== (double d, const MyVector& v);

int main(){
    double d1[5] = {3.01, 3.01, 3.01, 3.01, 3.01};
    MyVector v1(5, d1);
    double d = 3.0000000001;
    cout << (v1 == d);
    cout << (d == v1);
    return 0;
}

//global functions
bool operator== (double d, const MyVector& v){
    return (v == d); 
}

const MyVector operator+ (const MyVector& v, int d){
    MyVector sum(v);
    for (int i = 0; i < v.n; i++){
        sum[i] += d;
    }
    return sum;
}

const MyVector operator+ (double d, const MyVector& v){
    return v + d;
}

const MyVector operator+ (const MyVector& v1, const MyVector& v2){
    MyVector sum(v1);
    sum += v2;
    return sum;
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

bool MyVector::operator<(const MyVector& v) const{
    if (this->n != v.n){
        return false;
    }
    else{
        for (int i = 0; i < n; i++){
            if (this->m[i] >= v.m[i])
            return false;
        }
    }
    return true;
}

bool MyVector::operator!=(const MyVector& v) const{
    if (*this == v){
        return false;
    }
    else{
        return true;
    }
}

//allow a1 = a2 = a3
MyVector& MyVector::operator=(const MyVector& v){
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

const MyVector& MyVector::operator+= (const MyVector& v){
    if (this->n == v.n){
        for (int i = 0; i < n; i++){
            this->m[i] += v.m[i];
        }
    }
    return *this;
}

//return value becuase the local var will disappear after the function ends
const MyVector MyVector::operator+(const MyVector& v){
    MyVector sum(*this);
    sum += v;
    return sum;
}

const MyVector MyVector::operator+(int d){
    MyVector sum(*this);
    for (int i = 0; i < n; i++){
        sum[i] += d;
    }
    return sum;
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

