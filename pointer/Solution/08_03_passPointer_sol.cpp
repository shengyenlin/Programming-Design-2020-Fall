#include<iostream>
using namespace std;

int* maxPtr(int* a, int* b)
{
  if(*a > *b)
    return a;
  else
    return b;  
}

int main()
{
  int a = 0, b = 0;
  cin >> a >> b;
  cout << *maxPtr(&a, &b) << "\n";
  return 0;
}
