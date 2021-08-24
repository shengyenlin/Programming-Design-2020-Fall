#include <iostream>
#include <cstring>
using namespace std;

class Time
{
private:
  static bool hourIn12;
  int hour;
  int minute;
  int second;
  void printTwoDigits(int n);
public:
  Time();
  Time(int h, int m, int s);
  static void print12Hour(bool in12);
  bool isEarlierThan(Time t);
  void print();
  void printNicely();
};

bool Time::hourIn12 = false;

void Time::print12Hour(bool in12)
{
  Time::hourIn12 = in12;
}

void Time::printTwoDigits(int n)
{
  cout << (n < 10 ? "0" : "");
  cout << n; 
}

Time::Time()
{
  hour = minute = second = 0;
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
  if(hourIn12 == false)
    cout << hour << ":" << minute << ":" << second;
  else
  {
    if(hour < 12)
      cout << hour << ":" << minute << ":" << second << " AM";
    else
      cout << (hour - 12) << ":" << minute << ":" << second << " PM";      
  }
}

void Time::printNicely()
{
  if(hourIn12 == false || hour < 12)
    printTwoDigits(hour);
  else
    printTwoDigits(hour - 12);
  cout << ":"; 
  
  printTwoDigits(minute); 
  cout << ":"; 
  
  printTwoDigits(second);
  
  if(hourIn12 == true)
    cout << (hour < 12 ? " AM" : " PM");
}







class Event
{
private:
  char* name;
  Time start;
  Time end;
public:
  Event(char* n, Time s, Time t);
  ~Event();
  void printNicely();
  void setName(char* n);
};

Event::Event(char* n, Time s, Time t)
{
  int nameLen = strlen(n);
  name = new char[nameLen + 1];
  strcpy(name, n);
  start = s;
  end = t;
}

Event::~Event()
{
  delete [] name;
}

void Event::printNicely()
{
  cout << "\"" << name << "\"\n";
  cout << "Start: ";
  start.printNicely();
  cout << "\n";
  cout << "End:   ";
  end.printNicely();
  cout << "\n";
}

void Event::setName(char* n)
{
  delete [] name;
  
  int nameLen = strlen(n);
  name = new char[nameLen + 1];
  strcpy(name, n);  
}










int main()
{
  char n1[] = "PD";
  Event e1(n1, Time(14, 20, 0), Time(17, 20, 0));
  e1.printNicely(); 
  
  Event e2(e1); // copy an object
  char n2[] = "Calculus";
  e2.setName(n2);
  e2.printNicely();
  e1.printNicely(); // "Calculus" ???
                    // run-time error?
    
  return 0;
}

