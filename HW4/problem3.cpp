#include <iostream>
using namespace std;
int main()
{
    int num = 0;
    cin >> num;
    int costArray[200] = {0};
    int indexArray[200] = {0};
    for (int i = 1; i <= num; i++)
    {
        int cost = 0;
        cin >> cost;
        costArray[i] = cost;
        indexArray[i] = 1;
    }

    int revMatrix[200][200] = {0};
    for (int i = 1; i < num; i++)
    {
        for (int j = 1 + i; j <= num; j++)
        {
            int cost = 0;
            cin >> cost;
            revMatrix[i][j] = cost;
            revMatrix[j][i] = cost;
        }
    }

    //刪除
    int finalBenefit = 0;
    while (true)
    {
        int maxBenefit = 0, delIndex = 0;
        //k=0就是都沒有移除的情況
        for (int k = 0; k <= num; k++)
        {
            int totalRev = 0, totalCost = 0, benefit = 0;
            for (int i = 1; i <= num; i++)
            {
                for (int j = 1; j <= num; j++)
                {
                    if ((i != k) && (j != k))
                    {
                        totalRev += revMatrix[i][j];
                    }
                }
            }

            totalRev = totalRev / 2;

            for (int i = 1; i <= num; i++)
            {
                if (i != k)
                {
                    totalCost += costArray[i];
                }
            }

            benefit = totalRev - totalCost;

            if (k == 0)
            {
                maxBenefit = benefit;
            }

            else if (benefit > maxBenefit)
            {
                delIndex = k;
                maxBenefit = benefit;
            }

            //若在某輪中有複數個機場的移除都能得到同樣大的新整體利潤，則選機場編號最小者。
            else if (benefit == maxBenefit)
            {
                if (k < delIndex)
                {
                    delIndex = k;
                    maxBenefit = benefit;
                }

                if ((delIndex == 0) && k > delIndex)
                {
                    continue;
                }
            }
        }

        costArray[delIndex] = 0;
        indexArray[delIndex] = 0;
        for (int m = 1; m <= num; m++)
        {
            revMatrix[delIndex][m] = 0;
            revMatrix[m][delIndex] = 0;
        }

        if (delIndex == 0)
        {
            finalBenefit = maxBenefit;
            break;
        }
    }

    for (int i = 1; i <= num; i++)
    {
        if (i != num)
        {
            cout << indexArray[i] << ",";
        }

        else
        {
            cout << indexArray[i] << ";";
        }
    }

    cout << finalBenefit;

    return 0;
}