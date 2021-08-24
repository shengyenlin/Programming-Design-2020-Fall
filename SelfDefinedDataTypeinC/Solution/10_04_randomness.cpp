#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int LEN = 1000000;
const int MAX = 10000;
const int BIN_CNT = 10;

void setRN(int rn[], int len);
void hist(const int value[], int len, int freq[], int binCnt);

int main()
{
  int* rn = new int[LEN];
  int freq[BIN_CNT] = {0};

  setRN(rn, LEN);
  hist(rn, LEN, freq, BIN_CNT);
  
  for(int i = 0; i < BIN_CNT; i++)
    cout << freq[i] << " ";
  
  delete [] rn;
  
  return 0;
}

void setRN(int rn[], int len)
{
  srand(time(nullptr));
  for(int i = 0; i < len; i++)
  {
    double r = static_cast<double>(rand()) / RAND_MAX;
    rn[i] = static_cast<int>(MAX * r);
//    rn[i] = rand() % MAX;
  }
}

void hist(const int value[], int len, int freq[], int binCnt)
{
  for(int i = 0; i < len; i++)
  {
    // what if MAX / BIN_CNT is not an integer? 
    int d = value[i] / (MAX / binCnt); 
    freq[d]++;
  }
}
