#include<iostream>
using namespace std;

int* max(int a, int b)
{
  int* cPtr = new int(a);
  if(b > a)
    *cPtr = b;
  return cPtr;
}

int main()
{
  int a = 0, b = 0;
  cin >> a >> b;
  int* maxAddr = max(a, b);
  cout << *maxAddr << "\n";
  
  delete maxAddr; // otherwise memory leak
  return 0;
}
