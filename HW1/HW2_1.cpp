#include <iostream>
using namespace std;

int main()
{
    int numFull = 0, priceFull = 0, numStu = 0, priceStu = 0, budget = 0, limit = 0;
    cin >> numFull >> priceFull >> numStu >> priceStu >> budget >> limit;

    int totalTic = numFull + numStu;
    int cost = numFull * priceFull + numStu * priceStu;
    if (totalTic > limit)
    {
        cout << "-1";
    }

    else if (cost > budget)
    {
        cout << "-2";
    }

    else
    {
        cout << budget - cost;
    }
}