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

void Time::print()
{
  cout << hour << ":" << minute << ":" << second;
}






int main()
{
  Time t1(14, 30, 0); 
  Time t2(14, 25, 5);
  
  t1.print();
  cout << "\n";
  t2.print();
  
  return 0;
}





