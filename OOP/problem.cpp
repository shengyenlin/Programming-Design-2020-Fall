#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Entity{
    protected:
        string id;
        bool isOn;
        bool isSer; //means nothing if isOn == false
        double lon;
        double lat;
    public:
        Entity(string id, bool isOn, bool isSer, double lon, double lat);
        virtual void print() = 0;
};

class Car:public Entity{
    private:
    public:
        Car(string id, bool isOn, bool isSer, double lon, double lat);
        void print();
};

class Passenger:public Entity{
    private:
    public:
        Passenger(string id, bool isOn, bool isSer, double lon, double lat);
        void print();
};


class EntityArray{
    protected:
        int capacity;
        int cnt;
        Entity** entityPtr;
    public:
        EntityArray();
        ~EntityArray();
        virtual void add(string name, bool isOn, bool isSer, double lon, double lat) = 0;
        void print();
};

class CarArray:public EntityArray{
    private:
    public:
        void add(string name, bool isOn, bool isSer, double lon, double lat);
};

class PassengerArray:public EntityArray{
    private:
    public:
        void add(string name, bool isOn, bool isSer, double lon, double lat);
};


int main(){
    // Car* cars[2000] = {0};
    // int carCnt = 0;
    // cars[0] = new Car("5HE-313", true, true, 0, 0);
    // carCnt++;
    // cars[1] = new Car("LPA-039", true, false, 1, 1);
    // carCnt++;
    // for (int i = 0; i < carCnt; i++){
    //     cars[i]->print();
    // }
    CarArray ca;
    ca.add("5HE-313", true, true, 0, 0);
    ca.add("LPA-039", true, false, 1, 1);
    ca.print();

    PassengerArray pa;
    pa.add("B90705023", true, true, 0, 0);
    pa.add("R94725008", true, false, 1, 1);
    pa.print();
    return 0;
}

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat):
    id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat){}

void Entity::print(){
    cout << this->id << ": " << this->isOn << " " << this->isSer
         << " (" << this->lon << ", " << this->lat << ")" << endl;
}

Car::Car(string id, bool isOn, bool isSer, double lon, double lat):
    Entity(id, isOn, isSer, lon, lat){}

void Car::print(){
    cout << this->id << ": ";
    if (this->isOn){
        if (this->isSer){
            cout << "in-service, ";
        }
        else{
            cout << "empty, ";
        }
        cout << "(" << this->lon << ", " << this->lat << ")";
    }
    else{
        cout << "offline";
    }
    cout << endl;
}

// void EntityArray::add(string name, bool isOn, bool isSer, double lon, double lat){
//     if (this->cnt < this->capacity){
//         this->entityPtr[this->cnt] = new Entity(name, isOn, isSer, lon, lat);
//         this->cnt++;
//     }
// }

void EntityArray::print(){
    for (int i = 0; i < cnt; i++){
        this->entityPtr[i]->print();
    }
}

EntityArray::EntityArray(){
    this->cnt = 0;
    this->capacity = 20000;
    this->entityPtr = new Entity*[this->capacity];
}

EntityArray::~EntityArray(){
    for (int i = 0; i < this->cnt; i++){
        delete this->entityPtr[i];
    }
    delete [] this->entityPtr;
}

Passenger::Passenger(string id, bool isOn, bool isSer, double lon, double lat):
    Entity(id, isOn, isSer, lon, lat){}

void Passenger::print(){
    cout << this->id << ": ";
    if (this->isOn){
        if (this->isSer){
            cout << "in-service, ";
        }
        else{
            cout << "waiting, ";
        }
        cout << "(" << this->lon << ", " << this->lat << ")";
    }
    else{
        cout << "offline";
    }
    cout << endl;
}

void CarArray::add(string name, bool isOn, bool isSer, double lon, double lat){
    this->entityPtr[this->cnt] = new Car(name, isOn, isSer, lon, lat);
    this->cnt++;
}

void PassengerArray::add(string name, bool isOn, bool isSer, double lon, double lat){
    this->entityPtr[this->cnt] = new Passenger(name, isOn, isSer, lon, lat);
    this->cnt++;
}
