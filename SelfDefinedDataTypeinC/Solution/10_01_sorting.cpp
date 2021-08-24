#include <iostream>
using namespace std;

const int LEN = 7;

void bubbleSort(const int unsorted[], int sorted[], int len);
void insertionSort(const int unsorted[], int sorted[], int len);

int main()
{
  int values[] = {7, 5, 3, 3, 9, 6, 7};
  int sorted[LEN] = {0};

  bubbleSort(values, sorted, LEN);
  for(int i = 0; i < LEN; i++)
    cout << values[i] << " ";
  cout << "\n";

  insertionSort(values, sorted, LEN);
  for(int i = 0; i < LEN; i++)
    cout << values[i] << " ";
  cout << "\n";  
 
  return 0;
}

void bubbleSort(const int unsorted[], int sorted[], int len)
{
  for(int i = 0; i < len; i++)
    sorted[i] = unsorted[i];
    
  for(int i = len - 1; i > 0; i--)
  {
    for(int j = 0; j < i; j++)
    {
      if(sorted[j] > sorted[j + 1])
      {
        int temp = sorted[j];
        sorted[j] = sorted[j + 1];
        sorted[j + 1] = temp;
      }
    }
  }  
}

void insertionSort(const int unsorted[], int sorted[], int len)
{
  for(int i = 0; i < len; i++)
    sorted[i] = unsorted[i];
    
  for(int i = 0; i < len; i++)
  {
    for(int j = i; j > 0; j--)
    {
      if(sorted[j] < sorted[j - 1])
      {
        int temp = sorted[j];
        sorted[j] = sorted[j - 1];
        sorted[j - 1] = temp;
      }
      else
        break;
    }
  }    
}

