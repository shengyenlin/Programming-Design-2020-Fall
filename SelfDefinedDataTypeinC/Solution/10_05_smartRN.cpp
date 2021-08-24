#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

void naiveRN(int rn[], int n);
void smartRN(int rn[], int n);

int main()
{
  srand(time(nullptr));
  int n = 0;
  cin >> n;
  int* rn = new int[n];
  for(int i = 0; i < n; i++)
    rn[i] = 0;
      
  smartRN(rn, n);
  
//  for(int i = 0; i < n; i++)
//    cout << rn[i] << " ";
  
  delete [] rn;
   
  return 0;
}

void naiveRN(int rn[], int n)
{
  int success = 0;
  while(success < n)
  {
    int r = rand() % n + 1;
    bool exist = false;
    for(int j = 0; j < success; j++)
    {
      if(r == rn[j])
      {
        exist = true;
        break;
      }
    }
    if(exist == false)
    {
      rn[success] = r;
      success++;
    }
  }
}

void smartRN(int rn[], int n)
{
  for(int i = 0; i < n; i++)
    rn[i] = i + 1;
  
  for(int i = 0; i < n; i++)
  {
    int r = rand() % n;
    int temp = rn[r];
    rn[r] = rn[i];
    rn[i] = temp;
  }
}

/*
[1, 2, 3, 4]
2 @ index0

[3, 2, 1, 4]
3 @ index1

[3, 4, 1, 2]
3 @ index 2

[3, 4, 2, 1]
2 @ index 3

[3, 4, 1, 2]
*/


