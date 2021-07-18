#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int xLen = 0, yLen = 0, radius = 0, numStation = 0, numRoad = 0;
    cin >> xLen >> yLen >> radius >> numStation >> numRoad;
    int resident[100][100] = {0};
    for (int i = 0; i <= xLen; i++)
    {
        for (int j = 0; j <= yLen; j++)
        {
            int ppl = 0;
            cin >> ppl;
            resident[i][j] = ppl;
        }
    }

    int xStation[20] = {0}, yStation[20] = {0};
    for (int i = 1; i <= numStation; i++)
    {
        int x = 0, y = 0;
        cin >> x >> y;
        xStation[i] = x;
        yStation[i] = y;
    }

    int build[100][2] = {0};
    for (int i = 0; i < numRoad; i++)
    {
        int road1 = 0, road2 = 0;
        cin >> road1 >> road2;
        build[i][0] = road1;
        build[i][1] = road2;
    }

    int realBuild[100][100] = {0};
    for (int i = 0; i < numRoad; i++)
    {
        int xStation1 = 0, xStation2 = 0, yStation1 = 0, yStation2 = 0;
        xStation1 = xStation[build[i][0]];
        yStation1 = yStation[build[i][0]];
        xStation2 = xStation[build[i][1]];
        yStation2 = yStation[build[i][1]];

        if (xStation1 == xStation2)
        {
            int distance = abs(yStation1 - yStation2);
            if (yStation1 > yStation2)
            {
                for (int j = 0; j <= distance; j++)
                {
                    realBuild[xStation1][yStation2 + j] += 1;
                }
            }

            else
            {
                for (int j = 0; j <= distance; j++)
                {
                    realBuild[xStation1][yStation1 + j] += 1;
                }
            }
        }

        else if (yStation1 == yStation2)
        {
            int distance = abs(xStation1 - xStation2);
            if (xStation1 > xStation2)
            {
                for (int j = 0; j <= distance; j++)
                {
                    realBuild[xStation2 + j][yStation1] += 1;
                }
            }

            else
            {
                for (int j = 0; j <= distance; j++)
                {
                    realBuild[xStation1 + j][yStation1] += 1;
                }
            }
        }
    }

    //計算鐵路沿線受益人數
    //若等於1就加該村村民，若高於1只能算一次
    int finalPeople = 0;
    for (int i = 0; i <= xLen; i++)
    {
        for (int j = 0; j <= yLen; j++)
        {
            if (realBuild[i][j] >= 1)
            {
                finalPeople += resident[i][j];
            }
        }
    }

    //鐵路附近受益矩陣
    int nearBuild[100][100] = {0};
    for (int i = 1; i <= numStation; i++)
    {
        int xPos = 0, yPos = 0;
        xPos = xStation[i];
        yPos = yStation[i];

        for (int j = xPos - radius; j <= xPos + radius; j++)
        {
            for (int k = yPos - radius; k <= yPos + radius; k++)
            {
                nearBuild[j][k] += 1;
            }
        }
    }

    //計算鐵路附近受益人數
    int finalPeople2 = 0;
    for (int i = 0; i <= xLen; i++)
    {
        for (int j = 0; j <= yLen; j++)
        {
            if (nearBuild[i][j] >= 1)
            {
                finalPeople2 += resident[i][j];
            }
        }
    }

    cout << finalPeople2 << "," << finalPeople;
    return 0;
}
