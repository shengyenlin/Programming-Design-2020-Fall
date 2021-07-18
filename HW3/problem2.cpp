#include <iostream>
using namespace std;
int main()
{
    int totalLen = 0, ignore = 0;
    cin >> totalLen >> ignore;
    int numArray[1000] = {0};
    for (int i = 0; i < totalLen; i++)
    {
        int num = 0;
        cin >> num;

        if (num % ignore == 0 && num > 0)
        {
            numArray[i] = 0;
        }

        else
        {
            numArray[i] = num;
        }
    }

    //searchArray存要暴力搜尋的區間長度
    int searchArary[1000] = {0};
    for (int i = 0; i < totalLen; i++)
    {
        searchArary[i] = i + 1;
    }

    int searchLen = 0;
    int beginPos = 0, endPos = 0;
    int maxSum = 0, optSearchLen = 0, optBeginPos = 0;
    for (int i = 0; i < totalLen; i++)
    {
        searchLen = searchArary[i];
        for (int j = searchLen - 1; j < totalLen; j++)
        {
            int sum = 0;
            for (int k = 0; k < searchLen; k++)
            {
                sum += numArray[j - k];
            }

            if (j == 0)
            {
                maxSum = sum;
            }

            if (sum > maxSum)
            {
                optSearchLen = searchLen;
                optBeginPos = j - (optSearchLen - 1) + 1;
                endPos = optBeginPos + optSearchLen - 1;
                maxSum = sum;
            }

            if (sum == maxSum)
            {
                if (searchLen > optSearchLen)
                {
                    optSearchLen = searchLen;
                }

                if (searchLen == optSearchLen)
                {
                    if (beginPos > optBeginPos)
                    {
                        optBeginPos = beginPos;
                    }
                }
                optBeginPos = j - (optSearchLen - 1) + 1;
                endPos = optBeginPos + optSearchLen - 1;
                maxSum = sum;
            }
        }
    }
    cout << optBeginPos << "," << endPos << "," << maxSum;
    return 0;
}