#include <iostream>
using namespace std;

int main()
{
    int fullTic = 0, stuTic = 0, fullPrice = 0, stuPrice = 0, budget = 0, cost = 0;

    cin >> fullTic >> stuTic >> fullPrice >> stuPrice >> budget;
    cost = fullTic * fullPrice + stuTic * stuPrice;

    if (cost <= budget)
    {
        cout << budget - cost;
    }

    else
    {
        cout << "-1," << cost - budget;
    }

    return 0;
}