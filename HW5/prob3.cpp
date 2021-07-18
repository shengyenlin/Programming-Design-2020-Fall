#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int xlim = 0, ylim = 0, stationNum = 0, budget = 0;
    cin >> xlim >> ylim >> stationNum >> budget;
    int resident[1000][1000] = {0};
    //xStation:車站的x座標, yStation:車站的y座標
    int xStation[200] = {0}, yStation[200] = {0};
    for (int i = 0; i <= xlim; i++)
    {
        for (int j = 0; j <= ylim; j++)
        {
            int value = 0;
            cin >> value;
            resident[i][j] = value;
        }
    }

    for (int i = 0; i < stationNum; i++)
    {
        int x = 0, y = 0;
        cin >> x >> y;
        xStation[i] = x;
        yStation[i] = y;
    }

    //xAva1, yAva1 : 可建造車站座標的起點, xAva2, yAva2 : 可建造車站座標的終點, index1, index2:兩個車站的編號分別是多少
    int xAva1[1000] = {0}, yAva1[1000] = {0}, xAva2[1000] = {0}, yAva2[1000] = {0}, index1Array[1000] = {0}, index2Array[1000] = {0};
    //length:紀錄每一條鐵路的長度
    int lengthArray[1000] = {0};
    int count = 0;
    //count : 將總共有幾段鐵路可以興建記起來
    for (int i = 0; i < stationNum; i++)
    {
        for (int j = i + 1; j < stationNum; j++)
        {
            //x座標相同，且y路段不超過目前預算
            if (xStation[i] == xStation[j] && abs(yStation[i] - yStation[j]) <= budget)
            {
                xAva1[count] = xStation[i];
                yAva1[count] = yStation[i];
                xAva2[count] = xStation[j];
                yAva2[count] = yStation[j];
                index1Array[count] = i;
                index2Array[count] = j;
                lengthArray[count] = abs(yStation[i] - yStation[j]);
                count += 1;
            }
            //y座標相同，且x路段不超過目前預算
            if (yStation[i] == yStation[j] && abs(xStation[i] - xStation[j]) <= budget)
            {
                xAva1[count] = xStation[i];
                yAva1[count] = yStation[i];
                xAva2[count] = xStation[j];
                yAva2[count] = yStation[j];
                index1Array[count] = i;
                index2Array[count] = j;
                lengthArray[count] = abs(xStation[i] - xStation[j]);
                count += 1;
            }
        }
    }

    //挑出所有可建設路段
    int totalRes = 0;
    while (true)
    {
        //maxMarIndex1, maxMarIndex2 使邊際效益最大的兩個車站的編號
        float maxMarginalBenefit = 0, maxMarLength = 0, maxMarIndex1 = 0, maxMarIndex2 = 0;
        //finalIndex : 最終興建的車站組合是在array的哪一個位子
        int finalIndex = 0;
        for (int i = 0; i < count; i++)
        {
            //尋找在目前的budget之下還可以建設的路段
            float benefit = 0, length = 0, marginalBenefit = 0;
            //index1, index2: 兩個車站的編號
            int index1 = 0, index2 = 0;
            if ((lengthArray[i] <= budget) && (lengthArray[i] != 0))
            {
                //計算每條鐵路的marginal benefit
                if (xAva1[i] == xAva2[i])
                {
                    length = abs(yAva1[i] - yAva2[i]);
                    if (yAva1[i] < yAva2[i])
                    {
                        for (int j = 0; j <= length; j++)
                        {
                            benefit += resident[xAva1[i]][yAva1[i] + j];
                        }
                    }

                    else
                    {
                        for (int j = 0; j <= length; j++)
                        {
                            benefit += resident[xAva1[i]][yAva2[i] + j];
                        }
                    }
                    index1 = index1Array[i];
                    index2 = index2Array[i];
                }

                if (yAva1[i] == yAva2[i])
                {
                    length = abs(xAva1[i] - xAva2[i]);
                    if (xAva1[i] < xAva2[i])
                    {
                        for (int j = 0; j <= length; j++)
                        {
                            benefit += resident[xAva1[i] + j][yAva1[i]];
                        }
                    }

                    else
                    {
                        for (int j = 0; j <= length; j++)
                        {
                            benefit += resident[xAva2[i] + j][yAva1[i]];
                        }
                    }
                    index1 = index1Array[i];
                    index2 = index2Array[i];
                }
            }

            marginalBenefit = benefit / length;

            if (marginalBenefit > maxMarginalBenefit)
            {
                maxMarginalBenefit = marginalBenefit;
                maxMarLength = length;
                maxMarIndex1 = index1;
                maxMarIndex2 = index2;
                finalIndex = i;
            }

            else if (marginalBenefit == maxMarginalBenefit)
            {
                //長度較小者
                if (length < maxMarLength)
                {
                    maxMarginalBenefit = marginalBenefit;
                    maxMarLength = length;
                    maxMarIndex1 = index1;
                    maxMarIndex2 = index2;
                    finalIndex = i;
                }
                else if (length == maxMarLength)
                {
                    //選擇編號合計較小的
                    if (index1 + index2 < maxMarIndex1 + maxMarIndex2)
                    {
                        maxMarginalBenefit = marginalBenefit;
                        maxMarLength = length;
                        maxMarIndex1 = index1;
                        maxMarIndex2 = index2;
                        finalIndex = i;
                    }

                    else if (index1 + index2 == maxMarIndex1 + maxMarIndex2)
                    {
                        int minIndex = min<int>(index1, index2);
                        int minMarIndex = min<int>(maxMarIndex1, maxMarIndex2);
                        if (minIndex < minMarIndex)
                        {
                            maxMarginalBenefit = marginalBenefit;
                            maxMarLength = length;
                            maxMarIndex1 = index1;
                            maxMarIndex2 = index2;
                            finalIndex = i;
                        }
                    }
                }
            }
        }
        if (maxMarginalBenefit == 0)
        {
            break;
        }
        //更新數據
        budget = budget - maxMarLength;
        totalRes += maxMarginalBenefit * maxMarLength;

        //更新resdient矩陣
        int x1 = xAva1[finalIndex], y1 = yAva1[finalIndex], x2 = xAva2[finalIndex], y2 = yAva2[finalIndex];
        if (x1 == x2)
        {
            if (y1 < y2)
            {
                for (int i = 0; i <= abs(y1 - y2); i++)
                {
                    resident[x1][y1 + i] = 0;
                }
            }

            else
            {
                for (int i = 0; i <= abs(y1 - y2); i++)
                {
                    resident[x1][y2 + i] = 0;
                }
            }
        }

        if (y1 == y2)
        {
            if (x1 < x2)
            {
                for (int i = 0; i <= abs(x1 - x2); i++)
                {
                    resident[x1 + i][y1] = 0;
                }
            }

            else
            {
                for (int i = 0; i <= abs(x1 - x2); i++)
                {
                    resident[x2 + i][y1] = 0;
                }
            }
        }
        //更新可興建矩陣
        xAva1[finalIndex] = 0, yAva1[finalIndex] = 0, xAva2[finalIndex] = 0, yAva2[finalIndex] = 0;
        lengthArray[finalIndex] = 0;
    }
    cout << totalRes << "," << budget;

    return 0;
}