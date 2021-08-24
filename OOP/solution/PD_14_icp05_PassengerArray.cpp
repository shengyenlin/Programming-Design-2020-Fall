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
  virtual void print() = 0;
};

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat)
  : id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat)
{
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
  // EntityArray(const EntityArray& ea);
  // operator=(const EntityArray& ea);
  ~EntityArray();
  virtual bool add(string id, bool isOn, bool isSer, double lon, double lat) = 0;
  void print();
};

EntityArray::EntityArray()
{
  this->cnt = 0;
  this->capacity = 20000;
  this->entityPtr = new Entity*[this->capacity];
}

EntityArray::~EntityArray()
{
  for(int i = 0; i < this->cnt; i++)
    delete this->entityPtr[i];
  delete [] this->entityPtr;
}

void EntityArray::print()
{
  for(int i = 0; i < this->cnt; i++)
    this->entityPtr[i]->print();
}







class CarArray : public EntityArray
{
private:
public:
  bool add(string id, bool isOn, bool isSer, double lon, double lat);
};

bool CarArray::add(string id, bool isOn, bool isSer, double lon, double lat)
{
  if(this->cnt < this->capacity)
  {
    this->entityPtr[this->cnt] = new Car(id, isOn, isSer, lon, lat);
    this->cnt++;
    return true;
  }
  else
    return false;
}





class PassengerArray : public EntityArray
{
private:
public:
  bool add(string id, bool isOn, bool isSer, double lon, double lat);
};

bool PassengerArray::add(string id, bool isOn, bool isSer, double lon, double lat)
{
  if(this->cnt < this->capacity)
  {
    this->entityPtr[this->cnt] = new Passenger(id, isOn, isSer, lon, lat);
    this->cnt++;
    return true;
  }
  else
    return false;
}














int main()
{
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

