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
    public:
        Time(int h, int m, int s);
        int getH() {return hour;}
        int getM() {return minute;}
        int getS() {return second;}
        void print();
        bool isEarlierThan(Time t);
};

int main(){
    int hourArray[ARRAY_LEN] = {0};
    int minuteArray[ARRAY_LEN] = {0};
    int secondArray[ARRAY_LEN] = {0};

    for (int i = 0; i < ARRAY_LEN; i++){
        cin >> hourArray[i] >> minuteArray[i] >> secondArray[i];
    }

    Time t1(hourArray[0], minuteArray[0], secondArray[0]);
    Time t2(hourArray[1], minuteArray[1], secondArray[1]);
    Time t3(hourArray[2], minuteArray[2], secondArray[2]);

    //t2 > t1
    if (t1.isEarlierThan(t2)){
        //t3 > t2
        if (t2.isEarlierThan(t3)){
            cout << 3;
        }
        //t2 > t3
        else{
            cout << 2;
        }
    }
    //t1 > t2
    else{
        //t3 > t1
        if (t1.isEarlierThan(t3)){
            cout << 3;
        }
        //t3 > t1
        else{
            cout << 1;
        }
    }

    // Time t1(14, 30, 0);
    // Time t2(14, 25, 5);
    // if (t2.isEarlierThan(t1)){
    //     t2.print();
    // }
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
/*
14 0 0 15 4 13 15 8 2
3

14 0 0 16 4 13 15 8 2
2

14 0 0 14 0 0 15 8 2
3
*/