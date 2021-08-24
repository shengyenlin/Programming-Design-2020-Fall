#include <iostream>
using namespace std;

class MyVector{
    //can only be accessed by itself and its SUCCESSORS
    protected:
        int n;
        double* m;

    //private: WON'T be inherited
    //constructor and destructor won't be inherited too
    public:
        MyVector();
        MyVector(int dim, double m);
        MyVector(int n, double m[]);
        MyVector(const MyVector& v);
        ~MyVector();
        void print() const;

        int constGetN() const {return n;}
        int getN() {return n;}
        double constGetM(int i) const {return m[i];}
        double getM(int i) const {return m[i];}
        bool operator== (const MyVector& v) const;
        bool operator< (const MyVector& v) const;
        bool operator!= (const MyVector& v) const;

        MyVector& operator= (const MyVector& v);
        const MyVector& operator+= (const MyVector& v);
        const MyVector operator+ (const MyVector& v);
        const MyVector operator+ (int d);
        double operator[] (int i) const;
        //return reference, so that the instance variable can be modified
        double& operator[] (int i);
};

class MyVector2D:public MyVector{
    public:
        MyVector2D();
        MyVector2D(double m[]);
        void setValue(double i1, double i2);
        //the copy constructor of parent class will also be called
        //when the copy constructor of child class is called
        MyVector2D(const MyVector2D& v);
        //the destructor of parent class will also be called
        //when the destructor of child class is called

        //function overriding: override the original function inherited from the parent class
        void print() const;
};

//cascade inheritance(grandchildren)
class NNVector2D:public MyVector2D{
    public:
        NNVector2D();
        NNVector2D(double m[]);
        void setValue(double i1, double i2);
};

int main(){
    double i[2] = {1, 2};
    //parent class constructor will be called before the initialization of child class object!
    MyVector2D v(i);
    v.print();
    cout << v[1] << endl;
    return 0;
}

MyVector::MyVector():n(0){
    m = nullptr;
}

MyVector::MyVector(int dim, double m):n(dim){
    this->m = new double[n];
    for (int i = 0;i < n; i++){
        this->m[i] = m;
    }
}

MyVector::MyVector(int dim, double m[]):n(dim){
    this->m = new double[n];
    for (int i = 0; i < n; i++){
        this->m[i] = m[i];
    }
}


MyVector::MyVector(const MyVector& v):n(v.n){
    m = new double[n];
    for (int i = 0; i < n; i++){
        m[i] = v.m[i];
    }
}

void MyVector::print() const{
    cout << "(";
    for (int i = 0; i < n - 1; i++){
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

MyVector2D::MyVector2D(){
    this->n;
}

//":"(member initializer) : specify a parent constructor to call!
MyVector2D::MyVector2D(double m[]):MyVector(2, m){
}

//parent class can't access a child's member
void MyVector2D::setValue(double i1, double i2){
    if (this->m == nullptr){
        this->m = new double[2];
    }
    this->m[0] = i1;
    this->m[1] = i2;
}

void MyVector2D::print() const{
    cout << "2D: ";
    //we may also invoke parent's member in the child class
    MyVector::print();
}

NNVector2D::NNVector2D(){
    //call grandparent default constructor
    //call parent default constructor
}

NNVector2D::NNVector2D(double m[]){
    //we don't specify any parent constructor
    //call grandparent default constructor
    //call parent default constructor
    this->m = new double[2];
    this->m[0] = m[0] >= 0 ? m[0] : 0;
    this->m[1] = m[1] >= 0 ? m[1] : 0;
}


/*Alternative implementation
//call parent constructor
NNVector2D::NNVector2D(double m[]):MyVector2D(m){
    if(m[0] < 0){
        this->m[0] = 0;
    }
    if(m[1] < 0){
        this->m[1] = 0;
    }
}
*/

//destructor situation (inverse of constructor)
//call grandparent default constructor
//call parent default constructor


void NNVector2D::setValue(double i1, double i2){
    if (this->m == nullptr){
        this->m = new double[2];
    }
    this->m[0] = i1 >= 0 ? i1 : 0;
    this->m[1] = i2 >= 0 ? i2 : 0;
}

