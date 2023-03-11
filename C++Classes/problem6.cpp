#include <iostream>
#include <cstring>
using namespace std;

class Time{
    private:
        int hour;
        int minute;
        int second;
        static bool isSys12; 
        bool lessThanTen(int v) {return v < 10;}
    public:
        Time();
        Time(int h, int m, int s);
        static void print12Hour(bool i);
        int getH() {return hour;}
        int getM() {return minute;}
        int getS() {return second;}
        void print();
        bool isEarlierThan(Time t);
        void printNicely();
};


class Event{
    private:
        char* name;
        Time start;
        Time end;
    public:
        //Event();
        Event(char* n, Time s, Time t);
        Event(const Event& e);
        void setName(char* n);
        ~Event();
        void printNicely();
};

int main(){
    char n1[] = "PD";
    Event e1 (n1, Time(14, 20, 0), Time(17, 20, 0));
    e1.printNicely();

    Event e2(e1);
    char n2[] = "Calculus";
    e2.setName(n2);
    e2.printNicely();
    e1.printNicely();
    return 0; 
}

Event::Event(char* n, Time s, Time t){
    int nameLen = strlen(n);
    name = new char[nameLen + 1];
    strcpy(name, n);
    start = s;
    end = t;
}

Event::Event(const Event& e){
    int nameLen = strlen(e.name);
    name = new char[nameLen + 1];
    strcpy(name, e.name);
    start = e.start;
    end = e.end;
}

Event::~Event(){
    delete [] name;
}

void Event::setName(char* n){
    delete [] name;
    int nameLen = strlen(n);
    name = new char[nameLen + 1];
    strcpy(name, n);
}

void Event::printNicely(){
    cout << "\"" << name << "\"\n";
    cout << "Start: ";
    start.printNicely();
    cout << "\n";
    cout << "End:   ";
    end.printNicely();
    cout << "\n";
}

Time::Time()
{
  hour = minute = second = 0;
}

Time::Time(int h, int m, int s){
    hour = h;
    minute = m;
    second = s;
}

void Time::print(){
    cout << hour << ":"
        << minute << ":"
        << second;
}

void Time::print12Hour(bool i){
    if (i){
        isSys12 = true;
    }
    else{
        isSys12 = false;
    }
}

bool Time::isSys12 = false;

bool Time::isEarlierThan(Time t){
    bool hourEqual = (t.getH() == hour);
    bool minuteEqual = (t.getM() == minute);
    //cout << hourEqual << " " << minuteEqual << " ";
    if (t.getH() > hour){
        return true;
    }

    else if (hourEqual){
        if (t.getM() > minute){
            return true;
        }
        else if (minuteEqual){
            if (t.getS() > second){
                //cout << "3";
                return true;
            }
            //if equal return false
            return false;
        }
        //cout << "5";
        return false;
    }
    //cout << "6";
    return false;
}

void Time::printNicely(){
    if (isSys12){
        hour = hour - 12;
    }
    bool hourIslessThanTen = lessThanTen(hour);
    bool minuteIslessThanTen = lessThanTen(minute);
    bool secondIslessThanTen = lessThanTen(second);

    if (hourIslessThanTen){
        if (minuteIslessThanTen){
            if(secondIslessThanTen){
                //VVV
                cout << 0 << hour << ":" << 0 << minute << ":" << 0 << second;
            }
            else{
                //VVX
                cout << 0 << hour << ":" << 0 << minute << ":" << second;
            }
        }
        else{
            if(secondIslessThanTen){
                //VXV
                cout << 0 << hour << ":" << minute << ":" << 0 << second;
            }
            else{
                //VXX
                cout << 0 << hour << ":" << minute << ":" << second;
            }
        }
    }
    else{
        if (minuteIslessThanTen){
            if(secondIslessThanTen){
                //XVV
                cout << hour << ":" << 0 << minute << ":" << 0 << second;
            }
            else{
                //XVX
                cout << hour << ":" << 0 << minute << ":" << second;
            }
        }
        else{
            if (secondIslessThanTen){
                //XXV
                cout << hour << ":" << minute << ":" << 0 << second;
            }
            else{
                //XXX
                cout << hour << ":" << minute << ":" << second;
            }
        }
    }

    if (isSys12){
        cout << " PM";
    }
}