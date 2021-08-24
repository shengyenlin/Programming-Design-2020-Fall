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









int main()
{
  Car* cars[20000] = {0};
  int carCnt = 0;
  cars[0] = new Car("5HE-313", true, true, 0, 0);
  carCnt++;
  cars[1] = new Car("LPA-039", true, false, 1, 1);  
  carCnt++;
  for(int i = 0; i < carCnt; i++)
    cars[i]->print();

  return 0;
}


