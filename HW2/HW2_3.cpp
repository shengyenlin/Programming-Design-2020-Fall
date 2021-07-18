#include <iostream>
using namespace std;
int main()
{
    int num = 0;
    cin >> num;

    int thousand = 0, hundred = 0, ten = 0, one = 0;

    thousand = num / 1000;
    num -= thousand * 1000;
    hundred = num / 100;
    num -= hundred * 100;
    ten = num / 10;
    num -= ten * 10;
    one = num;

    int result = 0;
    int low1 = 0, low2 = 0, high1 = 0, high2 = 0, middle1 = 0, middle2 = 0;
    int highest = 0, lowest = 0;
    int first = 0, second = 0, third = 0, fourth = 0;
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

    result = first * 1 + second * 10 + third * 100 + fourth * 1000;
    cout << result;
    return 0;
}