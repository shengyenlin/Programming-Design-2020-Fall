#include <iostream>
using namespace std;

template <typename coorType> 
class MyVector2D
{
template <typename coorType1, typename coorType2>
friend bool operator==(const MyVector2D<coorType1>& u, const MyVector2D<coorType2>& v);
private:
  coorType x;
  coorType y;
public:
  MyVector2D();
  MyVector2D(coorType x, coorType y); 
  void print() const;   
  bool operator==(const MyVector2D<coorType>& v) const;
  void test() { cout << "...\n"; }
};

template <typename coorType> 
MyVector2D<coorType>::MyVector2D() : x(0), y(0) 
{
}

template <typename coorType> 
MyVector2D<coorType>::MyVector2D(coorType x, coorType y) : x(x), y(y)
{
}

template <typename coorType> 
void MyVector2D<coorType>::print() const 
{
  cout << "(" << this->x << ", " << this->y << ")\n";
}

template <typename coorType>
bool MyVector2D<coorType>::operator==(const MyVector2D<coorType>& v) const
{  
  if(this->x == v.x && this->y == v.y)
    return true;
  else
    return false;
}

template <typename coorType1, typename coorType2>
bool operator==(const MyVector2D<coorType1>& u, const MyVector2D<coorType2>& v)
{  
  if(u.x == v.x && u.y == v.y)
    return true;
  else
    return false;
}







int main()
{
  MyVector2D<double> u(1.2, 2.3);
  MyVector2D<int> v(1.4, 2.6);
  u.print();
  v.print();
  
  if(u == v)
    cout << "Equal!\n";
  else
    cout << "Unequal!\n";
  
  return 0;
}






