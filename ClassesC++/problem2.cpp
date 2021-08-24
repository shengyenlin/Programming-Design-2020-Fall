#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;

const int ARRAY_LEN = 3;

class Time{
    private:
        int hour;
        int minute;
        int second;
        bool lessThanTen(int v) {return v < 10;}
    public:
        Time(int h, int m, int s);
        int getH() {return hour;}
        int getM() {return minute;}
        int getS() {return second;}
        void print();
        bool isEarlierThan(Time t);
        void printNicely();
};

int main(){
    int hourArray[ARRAY_LEN] = {0};
    int minuteArray[ARRAY_LEN] = {0};
    int secondArray[ARRAY_LEN] = {0};

    for (int i = 0; i < ARRAY_LEN; i++){
        cin >> hourArray[i] >> minuteArray[i] >> secondArray[i];
    }
    int sys = 0;
    cin >> sys; //12 or 24
    Time t1(hourArray[0], minuteArray[0], secondArray[0]);
    Time t2(hourArray[1], minuteArray[1], secondArray[1]);
    Time t3(hourArray[2], minuteArray[2], secondArray[2]);

    //t2 > t1
    if (t1.isEarlierThan(t2)){
        //t3 > t2
        if (t2.isEarlierThan(t3)){
            t3.printNicely();
        }
        //t2 > t3
        else{
            t2.printNicely();
        }
    }
    //t1 > t2
    else{
        //t3 > t1
        if (t1.isEarlierThan(t3)){
            t3.printNicely();
        }
        //t3 > t1
        else{
            t1.printNicely();
        }
    }
    return 0;
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

bool Time::print12Hour (Inaccessible){}

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
}

/*
14 0 0 15 4 13 15 8 2
15:08:02

4 0 0 6 4 13 5 8 2
06:04:13
*/
