#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>


const int LOCATION_MAX = 10000;
const int MAX_CHAR_LENGTH = 10000;

void normalize(char str[], int strStartPos, char* ptr1, char* ptr2, char charToBeAssigned[]);

using namespace std;
int main()
{
    //locationNum: 機場數量, flightNum: 航線數量
    int locationNum = 0, flightNum = 0;
    cin >> locationNum >> flightNum;
    //airportName:存機場的名字
    char** airportName = new char* [locationNum];

    //int airportIndex[LOCATION_MAX] = { 0 };

    for (int i = 1; i <= locationNum; i++)
    {
        airportName[i] = new char[3];
        cin >> airportName[i];
        //airportIndex[i] = i;
    }

    //costArray: 每個機場的建造成本
    int costArray[LOCATION_MAX] = { 0 };
    for (int i = 1; i <= locationNum; i++)
    {
        int cost = 0;
        cin >> cost;
        costArray[i] = cost;
    }


    /*
    for (int i = 1; i <= locationNum; i++)
    {
        cout << airportName[i] << " ";
    }
    */

    //airline : 存入每一條航線的資訊
    //airline[0] : 起始機場, airline[1] : 終點機場, airline[2] : 創造的收益
    int** airline = new int* [flightNum];
    for (int i = 0; i < flightNum; i++)
    {
        airline[i] = new int[3];
    }

    cin.ignore();
    //機場名字正常化並且改成數字
    for (int i = 0; i < flightNum; i++)
    {
        //start:起始機場名字, end:終點機場名字
        char str[MAX_CHAR_LENGTH] = { 0 };
        cin.getline(str, MAX_CHAR_LENGTH);
        //紀錄每個'"'的位置
        char* first = strchr(str, '"');
        char* second = strchr(str + 1, '"');
        char* third = strchr(second + 1, '"');
        char* fourth = strchr(third + 1, '"');
        //紀錄每一個char開始的index
        int index1 = 1;
        int index2 = third - str + 1;
        //回傳開始結束的character
        char start[10] = { 0 }, end[10] = { 0 };
        normalize(&str[0], index1, str, second, &start[0]);
        normalize(&str[0], index2, third, fourth, &end[0]);

        int benefit = 0;
        benefit = atoi(&str[(second - first + 2) + (fourth - third + 2)]);
        //第一座機場名字對應到index
        for (int j = 1; j <= locationNum; j++)
        {
            if (start[0] == airportName[j][0] && start[1] == airportName[j][1] && start[2] == airportName[j][2])
            {
                airline[i][0] = j;
            }
        }

        //第二座機場名字對應到index
        for (int j = 1; j <= locationNum; j++)
        {
            if (end[0] == airportName[j][0] && end[1] == airportName[j][1] && end[2] == airportName[j][2])
            {
                airline[i][1] = j;
            }
        }
        //存入benefit
        airline[i][2] = benefit;
        /*
        cout << start << " " << airline[i][0] << "\n";
        cout << end << " " << airline[i][1] << "\n";
        cout << benefit;
        */
    }

    //algo
    //新增一個要被刪除機場的Array
    int deleteArray[LOCATION_MAX] = { 0 };
    int finalBenefit = 0;
    while (true)
    {
        int maxBenefit = 0, delIndex = 0;
        //i=0就是都沒有移除的情況, i:遍歷每個可以刪除的城市
        for (int i = 0; i <= locationNum; i++)
        {

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


        if (delIndex == 0)
        {
            finalBenefit = maxBenefit;
            break;
        }


    }


    //bubble sort
    for (int i = locationNum; i >= 1; i--)
    {
        for (int j = 1; j <= i - 1; j++)
        {
            if (strcmp(airportName[j], airportName[j + 1]) > 0)
            {
                char* tmp = airportName[j];
                airportName[j] = airportName[j + 1];
                airportName[j + 1] = tmp;

                int tmp2 = deleteArray[j];
                deleteArray[j] = deleteArray[j + 1];
                deleteArray[j + 1] = tmp2;
            }

        }
    }


    //按照字典順序印出
    bool first = false;
    for (int i = 1; i <= locationNum;i++)
    {
        if ((deleteArray[i] == 0) && first == false)
        {
            cout << airportName[i];
            first = true;
        }
        else if (deleteArray[i] == 0)
            cout << "," << airportName[i];
    }
    cout << ";" << finalBenefit;


    return 0;
}

void normalize(char str[], int strStartPos, char* ptr1, char* ptr2, char charToBeAssigned[])
{
    int position = 0;
    for (int i = 0; i < ptr2 - ptr1 - 1; i++)
    {
        //讀進來的字是小寫，轉成大寫
        if (islower(str[strStartPos + i]) != 0)
        {
            charToBeAssigned[position] = toupper(str[strStartPos + i]);
            position++;
        }

        //讀進來的字是空白判斷他後面有沒有空白
        else if (isspace(str[strStartPos + i]) != 0)
        {
            int numWhite = 1;
            while (str[strStartPos + i + numWhite] == ' ')
            {
                numWhite++;
            }

            charToBeAssigned[position] = toupper(str[strStartPos + i + numWhite]);
            position++;
            i += numWhite;
        }

        //讀進來的字是大寫的狀況
        else
        {
            charToBeAssigned[position] = str[strStartPos + i];
            position++;
        }
    }
}

/*
3 3
TPE SFO LAX
5 10 15
"TPE" "SFO" 20
"TPE" "La X" 20
"s f o" "LAX" 5

LAX ,SFO ,TPE ;15
*/

/*
3 2
TPE SFO LAX
5 15 30
"TPE" "SF o" 20
"t p e" "l a x" 25

SFO,TPE;0
*/
