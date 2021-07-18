#include <iostream>
using namespace std;

int main()
{
    int numPoint = 0, numRoad = 0;
    cin >> numPoint >> numRoad;
    int adjMatrix[200][200] = {0};
    for (int i = 0; i < numRoad; i++)
    {
        int start = 0, end = 0;
        cin >> start >> end;
        adjMatrix[start][end] = 1;
    }

    int pointNum = 0;
    cin >> pointNum;
    int pointArray[15000] = {0};
    for (int i = 0; i < pointNum; i++)
    {
        int point = 0;
        cin >> point;
        pointArray[i] = point;
    }

    //刪除用不到的元素
    for (int i = 1; i <= numPoint; i++)
    {
        int j;
        for (j = 0; j < pointNum; j++)
            if (i == pointArray[j])
                break;

        if (j == pointNum)
        {
            int del = i;
            for (int k = 1; k <= numPoint; k++)
            {
                adjMatrix[del][k] = 0;
                adjMatrix[k][del] = 0;
            }
        }
    }

    int temp[200][200] = {0};
    for (int i = 1; i < numPoint; i++)
    {
        for (int j = 1; j < numPoint; j++)
        {
            temp[i][j] = adjMatrix[i][j];
        }
    }

    //result = temp * sub
    //assign result to temp and then repeat (pointNum - 1) times
    int result[200][200] = {0};
    for (int l = 0; l < pointNum - 1; l++)
    {
        // matrix multiplication
        for (int i = 1; i <= numPoint; i++)
        {
            for (int k = 1; k <= numPoint; k++)
            {
                int sum = 0;
                for (int j = 1; j <= numPoint; j++)
                {

                    sum += temp[i][j] * adjMatrix[j][k];
                }
                result[i][k] = sum;
            }
        }

        //assign result to temp
        for (int i = 1; i <= numPoint; i++)
        {
            for (int j = 1; j <= numPoint; j++)
            {
                temp[i][j] = result[i][j];
            }
        }
    }

    int count = 0;
    for (int i = 1; i <= pointNum; i++)
    {
        for (int j = 0; j < pointArray[j]; j++)
        {
            if ((i == pointArray[j]) && (result[i][i] != 0))
            {
                count += 1;
            }
        }
    }

    if (count == 0)
    {
        cout << 0;
    }

    else
    {
        cout << 1;
    }

    return 0;
}
