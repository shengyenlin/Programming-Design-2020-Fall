#include <iostream>
using namespace std;
int main()
{
    int num = 0;
    cin >> num;

    int result = 0;
    int low1 = 0, low2 = 0, high1 = 0, high2 = 0, middle1 = 0, middle2 = 0;
    int highest = 0, lowest = 0;
    int first = 0, second = 0, third = 0, fourth = 0;

    while (num != 6174)
    {
        //算出千位數、十位數、百位數、個位數
        int thousand = 0, hundred = 0, ten = 0, one = 0;

        thousand = num / 1000;
        num -= thousand * 1000;
        hundred = num / 100;
        num -= hundred * 100;
        ten = num / 10;
        num -= ten * 10;
        one = num;

        //排列四個數字的大小
        if (thousand < hundred)
        {
            low1 = thousand;
            high1 = hundred;
        }
        else
        {
            low1 = hundred;
            high1 = thousand;
        }

        if (ten < one)
        {
            low2 = ten;
            high2 = one;
        }
        else
        {
            low2 = one;
            high2 = ten;
        }
        if (low1 < low2)
        {
            lowest = low1;
            middle1 = low2;
        }
        else
        {
            lowest = low2;
            middle1 = low1;
        }

        if (high1 > high2)
        {
            highest = high1;
            middle2 = high2;
        }
        else
        {
            highest = high2;
            middle2 = high1;
        }

        //數字由小到大 : first, second, third, fourth
        if (middle1 < middle2)
        {
            first = lowest;
            second = middle1;
            third = middle2;
            fourth = highest;
        }

        else
        {
            first = lowest;
            second = middle2;
            third = middle1;
            fourth = highest;
        }

        //計算大減小
        num = (first * 1 + second * 10 + third * 100 + fourth * 1000) - (first * 1000 + second * 100 + third * 10 + fourth * 1);

        if (num == 6174)
        {
            cout << "6174";
            break;
        }

        else
        {
            cout << num << ",";
        }
    }

    return 0;
}