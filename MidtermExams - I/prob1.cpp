#include <iostream>
using namespace std;
int main()
{
    int num1 = 0, num2 = 0, num3 = 0;
    cin >> num1 >> num2 >> num3;
    int big = 0, mid = 0, small = 0;
    if ((num1 >= num2) && (num1 >= num3))
    {
        big = num1;

        if (num2 >= num3)
        {
            mid = num2;
            small = num3;
        }

        else
        {
            mid = num3;
            small = num2;
        }
    }

    else if ((num2 >= num1) && (num2 >= num3))
    {
        big = num2;
        if (num1 >= num3)
        {
            mid = num1;
            small = num3;
        }

        else
        {
            mid = num1;
            small = num3;
        }
    }

    else
    {
        big = num3;
        if (num1 >= num2)
        {
            mid = num1;
            small = num2;
        }

        else
        {
            mid = num2;
            small = num1;
        }
    }

    cout << mid;
    return 0;
}