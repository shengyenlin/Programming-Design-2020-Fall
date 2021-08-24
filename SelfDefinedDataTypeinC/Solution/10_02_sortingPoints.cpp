#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Point
{
  int id;
  int x;
  int y;
  int distOriSq();
  bool isSmallerThan(Point p); 
  void print();
};
int Point::distOriSq()
{
  return pow(x, 2) + pow(y, 2);
}
bool Point::isSmallerThan(Point p)
{
  int distSelf = distOriSq();
  int distP = p.distOriSq();
  if(distSelf < distP)
    return true;
  else if(distSelf == distP && x < p.x)
    return true;
  else
    return false;
}

void insertionSort(const Point unsorted[], int sortedIndices[], int len);

int main()
{
  int pointCnt = 0;
  cin >> pointCnt;

  Point* unsorted = new Point[pointCnt];
  int* sortedIndices = new int[pointCnt];
  
  for(int i = 0; i < pointCnt; i++)
    unsorted[i].id = i + 1;
  for(int i = 0; i < pointCnt; i++)
    cin >> unsorted[i].x;
  for(int i = 0; i < pointCnt; i++)
    cin >> unsorted[i].y;

  insertionSort(unsorted, sortedIndices, pointCnt);
  delete [] unsorted;

  for(int i = 0; i < pointCnt - 1; i++)
  {
    cout << sortedIndices[i];
    cout << " ";
  }
  cout << sortedIndices[pointCnt - 1];

  delete [] sortedIndices;
    
  return 0;
}

void insertionSort(const Point unsorted[], int sortedIndices[], int len)
{
  Point* sorted = new Point[len];

  for(int i = 0; i < len; i++)
    sorted[i] = unsorted[i];
  
  for(int i = 0; i < len; i++)
  {
    for(int j = i; j > 0; j--)
    {
      if(sorted[j].isSmallerThan(sorted[j - 1]))
      {
        Point temp = sorted[j];
        sorted[j] = sorted[j - 1];
        sorted[j - 1] = temp;
      }
      else
        break;
    }
  }
  
  for(int i = 0; i < len; i++)
    sortedIndices[i] = sorted[i].id;
  
  delete [] sorted;
}
