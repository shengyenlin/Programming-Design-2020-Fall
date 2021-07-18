#include <iostream>
using namespace std;

int main()
{
    //numType:幾種票, budget:預算, limit:張數上限
    int numType = 0, budget = 0, limit = 0;
    cin >> numType >> budget >> limit;

    // totalCost:花費總金額, totalTic:總張數
    int totalCost = 0, totalTic = 0;

    //讀入票價與張數資料
    for (int i = 0; i < numType; i++)
    {
        int numTic = 0, priceTic = 0;
        cin >> numTic >> priceTic;
        totalCost += numTic * priceTic;
        totalTic += numTic;
    }

    if (totalTic > limit)
    {
        '' cout << "-1";
    }

    else if (totalCost > budget)
    {
        cout << "-2";
    }

    else
    {
        //allowance:找錢總金額
        int allowance = budget - totalCost;

        //500, 100, 50, 10, 5, 1
        int numFiveHundred = allowance / 500;
        allowance -= numFiveHundred * 500;

        int numOneHundred = allowance / 100;
        allowance -= numOneHundred * 100;

        int numFifty = allowance / 50;
        allowance -= numFifty * 50;

        int numTen = allowance / 10;
        allowance -= numTen * 10;

        int numFive = allowance / 5;
        allowance -= numFive * 5;

        int numOne = allowance;

        cout << numFiveHundred << "," << numOneHundred << "," << numFifty << "," << numTen << "," << numFive << "," << numOne;
    }
}