#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int LEN = 20; 
const int MAX = 10000;

void setRN(int rn[], int len);

int main()
{
  int rn[LEN] = {0};

  setRN(rn, LEN);
  for(int i = 0; i < LEN; i++)
    cout << rn[i] << " ";
  cout << "\n";

  return 0;
}

void setRN(int rn[], int len)
{
  srand(time(nullptr));
  for(int i = 0; i < len; i++)
    rn[i] = rand() % MAX;
}
