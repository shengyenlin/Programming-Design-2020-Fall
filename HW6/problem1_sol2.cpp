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

    //取出子矩陣
    int subAdjMatrix[200][200] = {0};
    for (int i = 0; i < pointNum; i++)
    {
        for (int j = 0; j < pointNum; j++)
        {
            subAdjMatrix[i][j] = adjMatrix[pointArray[i]][pointArray[j]];
        }
    }

    int temp[200][200] = {0};
    for (int i = 0; i < pointNum; i++)
    {
        for (int j = 0; j < pointNum; j++)
        {
            temp[i][j] = subAdjMatrix[i][j];
        }
    }

    //result = temp * sub
    //assign result to temp and then repeat (pointNum - 1) times
    int result[200][200] = {0};
    bool find = false;
    for (int l = 0; l < pointNum - 1; l++)
    {
        // matrix multiplication
        for (int i = 0; i < pointNum; i++)
        {
            for (int k = 0; k < pointNum; k++)
            {
                int sum = 0;
                for (int j = 0; j < pointNum; j++)
                {

                    sum += temp[i][j] * subAdjMatrix[j][k];
                }
                result[i][k] = sum;
            }
        }

        //assign result to temp
        for (int i = 0; i < pointNum; i++)
        {
            for (int j = 0; j < pointNum; j++)
            {
                temp[i][j] = result[i][j];
            }
        }

        int count = 0;
        for (int i = 0; i < pointNum; i++)
        {
            if (result[i][i] != 0)
            {
                count += 1;
            }
        }

        if (count == 0)
        {
            continue;
        }

        else
        {
            cout << 1;
            find = true;
            break;
        }
    }
    if (find == false)
        cout << 0;
    return 0;
}