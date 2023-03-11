#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;

class MyVector{
    //by default, all the variables and functions are private in class
    //private vars/funcs can only be used in class and classes' functions
    private:
        int n;
        int* m;
    //public vars/funcs can be retrieved everywhere
    public:
        //overload an instance functions with different params
        //constructor, no return value, even void;
        MyVector(); //ONE default constructor
        MyVector(int dim, int value = 0);
        MyVector(int dim, int v[]);
        MyVector(const MyVector& v);
        //destructor
        ~MyVector();
        //const function can only be used with const object/instance
        int constGetN() const {return n;}
        int getN() {return n;}
        int constGetM(int i) const {return m[i];}
        int getM(int i) const {return m[i];}
        void setN(int v) {n = v;}
        void print();
    //friend functions and class: private objects in this class can be accessed by your FRIEND!
    friend void test();
    friend class Test;
};


class Test{
    public:
        void test(MyVector v){
            v.n = 200;
            cout << v.n;
        }
};

class Window{
    private:
        int width;
        int height;
        //static: var/fun that is class-specific not OBJECT-specific
        static int barColor;
    public:
        static int getBarColor();
        static void setBarColor(int color);
};

class A{
    private:
        static int count;
        int i;
    public:
        A() {A::count++; cout << "A";}
        //copy constructor: call when passing this object to functions or a object is being copied
        //must call by reference, otherwise it will invoke itself infinite times
        A(const A& a){cout << "a";}
        static int getCount() {return A::count;}
        ~A() {A::count--; //cout << "a\n";
        }
};

class B{
    private:
        A a;
    public:
        B() {
            //cout << "B\n";
            }
        ~B() {//cout << "b\n"; //clean when the program ends
            } 
};

MyVector sumVector(MyVector* v1, MyVector* v2, MyVector* v3);
MyVector sumVectorByRef(const MyVector& v1, const MyVector& v2, const MyVector& v3);
void foo(A a1, A a2, A a3);

int main(){

    Window w;
    cout << Window::getBarColor() << "\n";
    Window::setBarColor(1);
    cout << Window::getBarColor() << "\n";
    if (true)
        A a1, a2, a3;
    cout << A::getCount() << "\n";

    MyVector v(5, 123);
    MyVector* ptrV = &v;
    v.print();
    //object pointer: prtV->print() == (*ptrV).print()
    //can delay invocation of constructors
    ptrV->print();

    //dynamic object arrays
    MyVector* ptrV2 = new MyVector(5);
    ptrV2->print();
    delete ptrV2;

    //object pointer arrays: stores object POINTERS, delay invocation of constructors
    MyVector* ptrArray[3];
    for (int i = 0; i < 3; i++){
        ptrArray[i] = new MyVector(2, 10);
    }

    MyVector sov = sumVector(ptrArray[0], ptrArray[1], ptrArray[2]);
    MyVector sov2 = sumVectorByRef(*ptrArray[0], *ptrArray[1], *ptrArray[2]);
    sov.print();
    sov2.print();
    for (int i = 0; i < 3; i++){
        delete ptrArray[i];
    }

    A a1, a2, a3;
    cout << "\n";
    //copy object: calling copy constructor
    A a4(a1);
    //equivalent syntax
    A a5 = a1;
    cout << "\n";
    foo(a1, a2, a3);

    MyVector v5(5, 1);
    MyVector v6(v5);
    return 0;
}

MyVector::MyVector(){
    n = 0;
    m = nullptr;
}

MyVector::MyVector(int dim, int value){
    n = dim;
    m = new int[n];
    for (int i = 0;i < n; i++){
        m[i] = value;
    }
}

MyVector::MyVector(int dim, int v[]){
    n = dim;
    m = new int[n];
    for (int i = 0; i < n; i++){
        m[i] = v[i];
    }
}

//copy constructor, shallow copy by default
MyVector::MyVector(const MyVector& v){
    n = v.n;
    //deep copy manually!!
    m = new int[n];
    for (int i = 0; i < n; i++){
        m[i] = v.m[i];
    }
}

MyVector::~MyVector(){
    delete [] m;
}

void MyVector::print(){
    cout << "(";
    for (int i = 0; i < n - 1; i++){
        cout << m[i] << ", ";
    }
    cout << m[n-1] << ")\n";
}

MyVector sumVector(MyVector* v1, MyVector* v2, MyVector* v3){
    //assume their dim are indentical
    int n = v1->getN();
    int* sumOfVec = new int[n];
    for (int i = 0; i < n; i++){
        sumOfVec[i] = v1->getM(i) + v2->getM(i) + v3->getM(i);
    }
    MyVector sov(n, sumOfVec);
    return sov;
}

//much easier and cleaner, and create only one MyVector object
MyVector sumVectorByRef(const MyVector& v1, const MyVector& v2, const MyVector& v3){
    //assume their dim are indentical
    int n = v1.constGetN();
    int* sumOfVec = new int[n];
    for (int i = 0; i < n; i++){
        sumOfVec[i] = v1.constGetM(i) + v2.constGetM(i) + v3.constGetM(i);
    }
    MyVector sov(n, sumOfVec);
    return sov;
}

int Window::barColor = 0;

int Window::getBarColor(){
    return barColor;
}

void Window::setBarColor(int color){
    barColor = color;
}

int A::count = 0;

void test(){
    MyVector v;
    v.n = 100; //ok, since its my friend
    cout << v.n;
}


void foo(A a1, A a2, A a3){
    A a4;
}