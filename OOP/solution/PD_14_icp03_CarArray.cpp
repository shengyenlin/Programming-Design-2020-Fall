#include <iostream>
#include <string>
using namespace std;

class Entity
{
protected:
  string id;
  bool isOn; 
  bool isSer; // means nothing if isOn == false
  double lon;
  double lat;
public: 
  Entity(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
  : id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat)
{
}

void Entity::print()
{
  cout << this->id << ": " << this->isOn << " " << this->isSer
       << " (" << this->lon << ", " << this->lat << ")" << endl;
}







class Car : public Entity
{
private:
public:
  Car(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};

Car::Car(string id, bool isOn, bool isSer, double lon, double lat)
  : Entity(id, isOn, isSer, lon, lat)
{
}

void Car::print()
{
  cout << this->id << ": ";
  if(this->isOn == true)
  {
    if(this->isSer == true)
      cout << "in-service, (";
    else
      cout << "empty, (";
    cout << this->lon << ", " << this->lat << ")";
  }
  else
    cout << "offline";
  cout << endl;
}














class CarArray
{
private:
  int capacity;
  int cnt;
  Car** carPtr;
public:
  CarArray();
  // CarArray(const CarArray& ea);
  // operator=(const CarArray& ea);
  ~CarArray();
  bool add(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};

CarArray::CarArray()
{
  this->cnt = 0;
  this->capacity = 20000;
  this->carPtr = new Car*[this->capacity];
}

CarArray::~CarArray()
{
  for(int i = 0; i < this->cnt; i++)
    delete this->carPtr[i];
  delete [] this->carPtr;
}

bool CarArray::add(string id, bool isOn, bool isSer, double lon, double lat)
{
  if(this->cnt < this->capacity)
  {
    this->carPtr[this->cnt] = new Car(id, isOn, isSer, lon, lat);
    this->cnt++;
    return true;
  }
  else
    return false;
}

void CarArray::print()
{
  for(int i = 0; i < this->cnt; i++)
    this->carPtr[i]->print();
}








int main()
{
  CarArray ca;
  ca.add("5HE-313", true, true, 0, 0);
  ca.add("LPA-039", true, false, 1, 1);  
  ca.print();
  
  return 0;
}

