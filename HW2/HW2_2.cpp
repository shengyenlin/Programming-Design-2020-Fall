#include <iostream>
using namespace std;
int main()
{
    int intervalNum = 0, numTic = 0, totalCost = 0;
    cin >> intervalNum >> numTic;

    int intervalNumTic = 0, ticPrice = 0, previousNum = 0, currentNum = 0;
    for (int i = 1; i <= intervalNum; i++)
    {
        cin >> intervalNumTic >> ticPrice;
        currentNum = intervalNumTic - previousNum;
        if (numTic > currentNum)
        {
            totalCost += currentNum * ticPrice;
            numTic -= currentNum;
        }
        else
        {
            totalCost += numTic * ticPrice;
            break;
        }
        previousNum += currentNum;
    }

    cout << totalCost;
    return 0;
}