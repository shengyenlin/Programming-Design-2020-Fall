#include <iostream>
using namespace std;

const int LOCATION_MAX = 10000;

int main()
{
    //locationNum: 機場數量, flightNum: 航線數量
    int locationNum = 0, flightNum = 0;
    cin >> locationNum >> flightNum;
    //costArray: 每個機場的建造成本
    int costArray[LOCATION_MAX] = { 0 };

    for (int i = 1; i <= locationNum; i++)
    {
        int cost = 0;
        cin >> cost;
        costArray[i] = cost;
    }

    //airline : 存入每一條航線的資訊
    //airline[0] : 起始機場, airline[1] : 終點機場, airline[2] : 創造的收益
    int** airline = new int* [flightNum];
    for (int i = 0; i < flightNum; i++)
    {
        airline[i] = new int[3]();
    }

    for (int i = 0; i < flightNum; i++)
    {
        int first = 0, second = 0, b = 0;
        cin >> first >> second >> b;
        airline[i][0] = first;
        airline[i][1] = second;
        airline[i][2] = b;
    }

    //新增一個要被刪除機場的Array
    int deleteArray[LOCATION_MAX] = { 0 };
    //algo
    int finalBenefit = 0;
    while (true)
    {
        int maxBenefit = 0, delIndex = 0;
        //i=0就是都沒有移除的情況, i:遍歷每個可以刪除的城市
        for (int i = 0; i <= locationNum; i++)
        {

            bool stop = false;
            //如果此機場已經被刪除就不用再跑一次
            if (deleteArray[i] == 1)
                continue;

            int totalRev = 0, totalCost = 0, benefitTemp = 0;
            //summation all benefit
            for (int k = 0; k < flightNum; k++)
            {
                if ((airline[k][0] != i) && (airline[k][1] != i))
                {
                    totalRev += airline[k][2];
                }
            }
            //summation all costs
            for (int j = 1; j <= locationNum; j++)
            {
                if (i != j)
                {
                    totalCost += costArray[j];
                }
            }

            benefitTemp = totalRev - totalCost;

            if (i == 0)
            {
                maxBenefit = benefitTemp;
            }
            else if (benefitTemp > maxBenefit)
            {
                delIndex = i;
                maxBenefit = benefitTemp;
            }
            /*
            //若在某輪中有複數個機場的移除都能得到同樣大的新整體利潤，則選機場編號最小者。
            else if (benefitTemp == maxBenefit)
            {
                if (i < delIndex)
                {
                    delIndex = i;
                    maxBenefit = benefitTemp;
                }
            }
            */
        }
        if (delIndex == 0)
        {
            finalBenefit = maxBenefit;
            break;
        }

        else
        {
            //將cost和benefit歸零
            costArray[delIndex] = 0;
            for (int k = 0; k < flightNum; k++)
            {
                if ((airline[k][0] == delIndex) || (airline[k][1] == delIndex))
                {
                    airline[k][2] = 0;
                }
            }
            //將不要的機場設為1
            deleteArray[delIndex] = 1;
        }


    }

    bool first = false;
    for (int i = 1; i <= locationNum;i++)
    {
        if ((deleteArray[i] == 0) && first == false)
        {
            cout << i;
            first = true;
        }
        else if (deleteArray[i] == 0)
            cout << "," << i;
    }
    cout << ";" << finalBenefit;
    return 0;

}
