#include <iostream>
using namespace std;

class Time
{
private:
  int hour;
  int minute;
  int second;
public:
  Time(int h, int m, int s);
  bool isEarlierThan(Time t);
  void print();
};

Time::Time(int h, int m, int s)
{
  hour = h;
  minute = m;
  second = s;
}

bool Time::isEarlierThan(Time t)
{
  if(hour < t.hour)
    return true;
  else if(hour == t.hour)
  {
    if(minute < t.minute)
      return true;
    else if(minute == t.minute)
    {
      if(second < t.second)
        return true;
    }
  }
  return false;
  
  // an alternative method
  /* 
  int numSecSelf = 3600 * hour + 60 * minute + second;
  int numSecT = 3600 * t.hour + 60 * t.minute + t.second;
  if(numSecSelf < numSecT)
    return true;
  else
    return false;
  */
}

void Time::print()
{
  cout << hour << ":" << minute << ":" << second;
}

int main()
{
  int te[9] = {0};
  for(int i = 0; i < 9; i++)
    cin >> te[i];
  Time t1(te[0], te[1], te[2]); 
  Time t2(te[3], te[4], te[5]);
  Time t3(te[6], te[7], te[8]);
  
  if(t1.isEarlierThan(t2))
  {
    if(t2.isEarlierThan(t3))
      cout << 3;
    else
      cout << 2;
  }
  else
  {
    if(t1.isEarlierThan(t3))
      cout << 3;
    else
      cout << 1;
  }
  
  return 0;
}




