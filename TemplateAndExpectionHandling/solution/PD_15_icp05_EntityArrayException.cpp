#include <iostream>
#include <string>
#include <stdexcept>
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





class Passenger : public Entity
{
private:
public:
  Passenger(string id, bool isOn, bool isSer, double lon, double lat);
  void print();
};

Passenger::Passenger(string id, bool isOn, bool isSer, double lon, double lat)
  : Entity(id, isOn, isSer, lon, lat)
{
}

void Passenger::print()
{
  cout << this->id << ": ";
  if(this->isOn == true)
  {
    if(this->isSer == true)
      cout << "in-service, (";
    else
      cout << "waiting, (";
    cout << this->lon << ", " << this->lat << ")";
  }
  else
    cout << "offline";
  cout << endl;
}












class EntityArray
{
protected:
  int capacity;
  int cnt;
  Entity** entityPtr;
public:
  EntityArray();
  ~EntityArray();
  void add(string id, bool isOn, bool isSer, double lon, double lat) throw(overflow_error);
  void print() noexcept; 
};

EntityArray::EntityArray()
{
  this->cnt = 0;
  this->capacity = 1;
  this->entityPtr = new Entity*[this->capacity];
}

EntityArray::~EntityArray()
{
  for(int i = 0; i < this->cnt; i++)
    delete this->entityPtr[i];
  delete [] this->entityPtr;
}

void EntityArray::add(string id, bool isOn, bool isSer, double lon, double lat) throw(overflow_error)
{
  if(this->cnt < this->capacity)
  {
    this->entityPtr[this->cnt] = new Entity(id, isOn, isSer, lon, lat);
    this->cnt++;
  }
  else
    throw overflow_error(id + ": capacity limit reached!");
}

void EntityArray::print() noexcept
{
  for(int i = 0; i < this->cnt; i++)
    this->entityPtr[i]->print();
}














int main()
{
  EntityArray ca;
  try
  {
    ca.add("5HE-313", true, true, 0, 0);
    ca.add("LPA-039", true, false, 1, 1);  
  }
  catch(overflow_error e)
  {
    cout << e.what() << endl;
  } 
  ca.print();

  EntityArray pa;
  try
  {
    pa.add("B90705023", true, true, 0, 0);
    pa.add("R94725008", true, false, 1, 1);  
  }
  catch(overflow_error e)
  {
    cout << e.what() << endl;
  } 
  pa.print();
  
  return 0;
}

