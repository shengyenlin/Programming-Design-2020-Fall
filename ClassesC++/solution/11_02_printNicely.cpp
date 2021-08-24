#include <iostream>
using namespace std;

class Time
{
private:
  int hour;
  int minute;
  int second;
  void printTwoDigits(int n);
public:
  Time(int h, int m, int s);
  bool isEarlierThan(Time t);
  void print();
  void printNicely();
};

void Time::printTwoDigits(int n)
{
  cout << (n < 10 ? "0" : "");
  cout << n; 
}

Time::Time(int h, int m, int s)
{
  hour = h;
  minute = m;
  second = s;
}

bool Time::isEarlierThan(Time t)
{
  int numSecSelf = 3600 * hour + 60 * minute + second;
  int numSecT = 3600 * t.hour + 60 * t.minute + t.second;
  if(numSecSelf < numSecT)
    return true;
  else
    return false;
}

void Time::print()
{
  cout << hour << ":" << minute << ":" << second;
}

void Time::printNicely()
{
  printTwoDigits(hour);
  cout << ":"; 
  printTwoDigits(minute); 
  cout << ":"; 
  printTwoDigits(second);
}

int main()
{
  Time t1(14, 30, 0); 
  Time t2(14, 25, 5);
  
  if(t2.isEarlierThan(t1))
    t2.printNicely(); // 14:25:05
  
  return 0;
}

