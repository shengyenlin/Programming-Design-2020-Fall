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
    //indexArray:為了最後cout開設的陣列，如果最後元素是0就不要print
    int indexArray[LOCATION_MAX] = { 0 };

    for (int i = 1; i <= locationNum; i++)
    {
        int cost = 0;
        cin >> cost;
        costArray[i] = cost;
        indexArray[i] = 1;
    }

    //neighbor : 有航線的城市號碼,  benefit: 每個航線的營收, length: 每個dynamic array的長度
    int* neighbor[LOCATION_MAX] = { 0 };
    int* benefit[LOCATION_MAX] = { 0 };
    int length[LOCATION_MAX] = { 0 };

    int neighborNum = (flightNum / locationNum) + 1;
    //為每個城市宣告一個長度為 m/n 的動態陣列, 並記下號碼及長度
    for (int i = 1; i <= locationNum; i++)
    {
        neighbor[i] = new int[neighborNum];
        benefit[i] = new int[neighborNum];
    }

    //index: 現在這個城市儲存第幾個鄰近城市的資訊
    int previousCurrentCity = 1, index = 1;
    for (int i = 1; i <= flightNum; i++)
    {
        int currentCity = 0, neighborCity = 0, value = 0;
        cin >> currentCity >> neighborCity >> value;

        if (previousCurrentCity == currentCity)
        {
            if (index > neighborNum)
            {
                int neighborNum2 = (neighborNum * 2) + 1;
                int* tempNeighbor = new int[neighborNum2];
                int* tempBenefit = new int[neighborNum2];
                for (int j = 1; j <= neighborNum; j++)
                {
                    tempNeighbor[j] = neighbor[currentCity][j];
                    tempBenefit[j] = benefit[currentCity][j];
                }
                delete[] neighbor[currentCity];
                delete[] benefit[currentCity];

                neighbor[currentCity] = tempNeighbor;
                benefit[currentCity] = tempBenefit;

                neighbor[currentCity][index] = neighborCity;
                benefit[currentCity][index] = value;

                neighborNum = neighborNum2;
            }

            else
            {
                neighbor[currentCity][index] = neighborCity;
                benefit[currentCity][index] = value;
            }

        }
        else
        {
            index = 1;
            neighbor[currentCity][index] = neighborCity;
            benefit[currentCity][index] = value;
        }

        length[currentCity] = index;
        previousCurrentCity = currentCity;
        index++;
    }

    /*
    for (int i = 1; i <= locationNum; i++)
    {
        for (int j = 1; j <= length[i]; j++)
        {
            cout << i << " " << neighbor[i][j] << " " << benefit[i][j] << " ";
        }
        cout << "\n";
    }
    */


    //algo
    int finalBenefit = 0;
    while (true)
    {
        int maxBenefit = 0, delIndex = 0;
        //i=0就是都沒有移除的情況, i:遍歷每個可以刪除的城市
        for (int i = 0; i <= locationNum; i++)
        {
            int totalRev = 0, totalCost = 0, benefitTemp = 0;
            for (int j = 1; j <= locationNum; j++)
            {
                if (i != j)
                {
                    //summation all benefits
                    for (int k = 1; k <= length[j]; k++)
                    {
                        if (i != neighbor[j][k])
                        {
                            totalRev += benefit[j][k];
                        }
                    }
                    //summation all costs
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


            //若在某輪中有複數個機場的移除都能得到同樣大的新整體利潤，則選機場編號最小者。
            else if (benefitTemp == maxBenefit)
            {
                if (i < delIndex)
                {
                    delIndex = i;
                    maxBenefit = benefitTemp;
                }

                if ((delIndex == 0) && (i > delIndex))
                {
                    continue;
                }

            }



        }

        //刪除不要的機場
        for (int j = 1; j <= locationNum; j++)
        {
            for (int k = 1; k <= length[j]; k++)
            {
                if (neighbor[j][k] == delIndex)
                {
                    benefit[j][k] = 0;
                }
            }
        }
        costArray[delIndex] = 0;
        indexArray[delIndex] = 0;
        if (delIndex == 0)
        {
            finalBenefit = maxBenefit;
            break;
        }

    }

    int sum = 0;
    for (int i = 1; i <= locationNum; i++)
    {
        if (indexArray[i] == 1)
        {
            sum += 1;
        }
    }
    int count = 0;
    for (int i = 1; i <= locationNum; i++)
    {
        if (indexArray[i] == 1 && count == sum - 1)
        {
            cout << i;
        }
        else if (indexArray[i] == 1)
        {
            cout << i << ",";
            count += 1;
        }
    }

    cout << ";" << finalBenefit;
    return 0;
}