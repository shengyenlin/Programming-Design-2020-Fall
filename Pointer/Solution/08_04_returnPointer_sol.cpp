#include<iostream>
using namespace std;

int* max(int a, int b)
{
  int c = a;
  if(b > a)
    c = b;
  return &c; // c will then be released by the OS
}

int main()
{
  int a = 0, b = 0;
  cin >> a >> b;
  int* maxAddr = max(a, b);
  cout << *maxAddr << "\n"; // may access an invalid address
  return 0;
}

