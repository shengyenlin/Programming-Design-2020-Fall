#include <iostream>

using namespace std;

int main()
{
    int xlim = 0, ylim = 0, cover = 0;
    cin >> xlim >> ylim >> cover;
    //這邊要設1200
    int resident[100][100] = {0};
    for (int i = 0; i <= ylim; i++)
    {
        for (int j = 0; j <= xlim; j++)
        {
            int value = 0;
            cin >> value;
            resident[j][i] = value;
        }
    }

    //run每一個座標
    int maxRes = 0;
    for (int i = 0; i <= ylim; i++)
    {
        for (int j = 0; j <= xlim; j++)
        {
            int totalRes = 0, count = 0;
            //加總居民數量
            for (int k = j - cover; k <= j; k++)
            {
                for (int m = i - count; m <= i + count; m++)
                {
                    if ((k >= 0) && (k <= xlim) && (m >= 0) && (m <= ylim))
                    {
                        totalRes += resident[k][m];
                    }
                }
                count += 1;
            }

            count = cover - 1;
            for (int k = j + 1; k <= j + cover; k++)
            {
                for (int m = i - count; m <= i + count; m++)
                {
                    if ((k >= 0) && (k <= xlim) && (m >= 0) && (m <= ylim))
                    {
                        totalRes += resident[k][m];
                    }
                }
                count -= 1;
            }

            if (totalRes >= maxRes)
            {
                maxRes = totalRes;
            }
        }
    }

    cout << maxRes;
}