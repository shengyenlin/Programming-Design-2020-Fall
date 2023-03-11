#include<iostream>
using namespace std;

//call by reference
void swap_by_reference(int& x, int& y);
//call by pointer
void swap_by_pointer(int* ptrX, int* ptrY);
//returning a pointer
int* firstNeg(int a[], const int n);
//print two-dimensional dynamic arrays
void print(int** arr, int r);
//
void insertionSort(int* array, const int n);
int main()
{
    /*
    int a = 5;
    double b = 10.123;
    //reference operator
    int* aPtr = &a;
    double* bPtr = &b;
    cout << a << "\n" << b << "\n" << aPtr << "\n" << bPtr << "\n";
    //dereference operator
    cout << *aPtr << "\n";

    //null pointer
    int* p2 = nullptr;
    cout << "value of p2" << " " << p2 << "\n";

    //reference: another vairable that refers to the variable
    int c = 10;
    int& d = c;
    d = 20;
    cout << c << "\n";

    int e = 20;
    int* ptrE = &e;
    int f = 25;
    int* ptrF = &f;
    swap_by_reference(e, f);
    cout << e << " " << f << "\n";
    swap_by_pointer(ptrE, ptrF);
    cout << e << " " << f << "\n";

    int arrayA[10] = {0};
    for (int i = 0; i < 10; i++)
    {
        arrayA[i] = -i;
    }
    int* noneNegPtr = firstNeg(arrayA, 10);
    cout << *noneNegPtr << " " << noneNegPtr << "\n";

    //dynamic memory allocation
    int len = 10;
    int* dynammicArray = new int[len];
    for (int i = 0; i < len; i++)
    {
        dynammicArray[i] = i + 1;
    }
    for (int i = 0; i < len; i++)
    {
        cout << dynammicArray[i] << " ";
    }
    cout << "\n";

    //delete the memory allocation
    delete [] dynammicArray;
    //assign the origin pointer as null pointer, in case you deference it 
    dynammicArray = nullptr;
    */
    //two dimensional dynamic arrays: we can now create matrices with different lengths
    int h = 3;
    int** array = new int*[h];
    for (int i = 0; i < h; i++)
    {
        array[i] = new int[i + 1];
        for (int j = 0; j <= i; j++)
        {
            array[i][j] = j + 1;
        }
    }
    print(array, h);
    for (int i = 1; i <= h; i++)
    {
        delete [] array[i];
    }

    //arrays and pointer arithmetic
    double a[3] = {1, 2, 3};
    double* b = &a[0];
    b++;
    cout << *b << "\n";
    for (int i = 0; i < 3; i++)
    {
        //the two expressions are the same
        cout << a[i] << " ";
        cout << *(a+i) << " ";
    }
    cout << "\n";

    int Array[2] = {5, 4};
    insertionSort(&Array[0], 2);
    for (int i = 0; i < 2; i++){
        cout << Array[i] << " ";
    }
    return 0;
}

void swap_by_reference(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

void swap_by_pointer(int* ptrX, int* ptrY)
{
    int temp = *ptrX;
    *ptrX = *ptrY;
    *ptrY = temp;
}

int* firstNeg(int a[], const int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
            return &a[i];
    }
    return 0;
}

void print(int** arr, int r)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

void insertionSort(int* array, const int n){
    if (n > 1){
        insertionSort(array + 1, n - 1);
        int num1 = array[0];
        int i = 1;
        for (; i < n; i++){
            if (array[i] < num1){
                array[i-1] = array[i];
            }
            else{
                break;
            }
        }
        //i = n here
        array[i - 1] = num1;
    }
}