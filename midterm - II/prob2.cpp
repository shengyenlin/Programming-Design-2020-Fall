#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

const int MAX_NUM = 10;

using namespace std;
int main()
{
    int num = 0;
    cin >> num;
    int** ptrX = new int* [MAX_NUM];
    int** ptrY = new int* [MAX_NUM];
    for (int i = 1; i <= num;i++)
    {
        ptrX[i] = new int[5];
        ptrY[i] = new int[5];
        for (int j = 1; j <= 4; j++)
        {
            int x = 0;
            cin >> x;
            ptrX[i][j] = x;
        }

        for (int j = 1; j <= 4; j++)
        {
            int y = 0;
            cin >> y;
            ptrY[i][j] = y;
        }
    }

    //檢查input
    /*
    for (int i = 1; i <= num; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            cout << ptrX[i][j] << " " << ptrY[i][j] << "\n";
        }

    }
    */

    //從第一個矩陣開始search
    int count = 0;
    int hasSearched[10][10] = { 0 };
    for (int i = 1; i <= num; i++)
    {
        bool search = false;
        for (int j = 1; j <= 4; j++)
        {
            int currentX = ptrX[i][j];
            int currentY = ptrY[i][j];

            for (int k = 1; k <= num; k++)
            {
                if (hasSearched[k][i] == 1 || hasSearched[i][k] == 1)
                    continue;

                else if (k == i)
                    continue;
                /*
                cout << ptrX[k][3] << " " << currentX << " " << ptrX[k][4] << " ";
                cout << ptrY[k][3] << " " << currentY << " " << ptrY[k][1];
                */
                //x和y座標都被夾住
                else if (currentX < ptrX[k][4] && currentX > ptrX[k][3] && currentY < ptrY[k][1] && currentY > ptrY[k][3])
                {
                    count += 1;
                    hasSearched[i][k] = 1;
                    //cout << i << " " << j << " " << k << "\n";
                    //cout << i << " " << k << "\n";
                }
            }
        }
    }
    cout << count;

    return 0;
}


/*
data
2
1 3 1 3 3 3 0 0
2 4 2 4 5 5 2 2

1

3
1 2 1 2 2 2 1 1
1 2 1 2 4 4 2 2
2 3 2 3 4 4 1 1

0

3
1 3 1 3 3 3 0 0
2 4 2 4 5 5 2 2
7 8 7 8 7 7 6 6

1

4
31 118 31 118 191 191 68 68
67 110 67 110 176 176 24 24
87 137 87 137 134 134 31 31
69 79 69 79 92 92 28 28

*/