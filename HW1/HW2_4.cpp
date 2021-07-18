#include <iostream>
using namespace std;
int main()
{
    float temperature = 0;
    int count = 0;

    //因為會一直重複，所以使用while，等到不符合條件再break
    while (true)
    {
        cin >> temperature;
        int intTemperature = temperature / 1;

        //第一次的情況，因為希望第一個不要印出逗點
        if (temperature < 37 && count == 0)
        {
            cout << intTemperature;
        }
        else if (temperature < 37 && count != 0)
        {
            cout << ",";
            cout << intTemperature;
        }

        else
        {
            break;
        }
        count += 1;
    }
}