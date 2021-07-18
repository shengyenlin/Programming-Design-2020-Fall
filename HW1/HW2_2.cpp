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
        int allowance = budget - cost;
        //500, 100, 50, 10, 5, 1
        int numFiveHundred = allowance / 500;
        int numOneHundred = (allowance - numFiveHundred * 500) / 100;
        int numFifty = (allowance - numFiveHundred * 500 - numOneHundred * 100) / 50;
        int numTen = (allowance - numFiveHundred * 500 - numOneHundred * 100 - numFifty * 50) / 10;
        int numFive = (allowance - numFiveHundred * 500 - numOneHundred * 100 - numFifty * 50 - numTen * 10) / 5;
        int numOne = allowance - numFiveHundred * 500 - numOneHundred * 100 - numFifty * 50 - numTen * 10 - numFive * 5;

        cout << numFiveHundred << "," << numOneHundred << "," << numFifty << "," << numTen << "," << numFive << "," << numOne;
    }
}