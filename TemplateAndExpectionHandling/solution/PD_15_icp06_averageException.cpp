#include<iostream>
#include<stdexcept>
using namespace std;

double averageNonzero(double grades[], int gradeCnt) throw(logic_error)
{
  double sum = 0;
  int nonzeroCnt = 0;
  for(int i = 0; i < gradeCnt; i++)
  {
    if(grades[i] != 0)
    {
      sum += grades[i];
      nonzeroCnt++;
    }
  }
  
  if(nonzeroCnt == 0)
    throw logic_error("divisor is 0!");
  else 
    return sum / nonzeroCnt;
}

int main()
{
  double grades[100] = {0}, avg = 0;
  int gradeCnt = 0;
  while(true)
  {
    double temp = 0;
    cin >> temp;
    if(temp == -1)
      break;
    else
    {
      grades[gradeCnt] = temp;
      gradeCnt++;
    }
  }
  
  try
  {
    avg = averageNonzero(grades, gradeCnt);
  }
  catch(logic_error e)
  {
    avg = 0;
  }
  cout << avg;
  return 0;
}
