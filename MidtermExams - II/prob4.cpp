#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

using namespace std;
int main()
{
    int num = 0, times = 0, start = 0, end = 0;
    cin >> num >> times >> start >> end;
    int price[201][201] = { 0 };
    for (int i = 1; i <= num; i++)
    {
        for (int j = i + 1; j <= num; j++)
        {
            int ticketPrice = 0;
            cin >> ticketPrice;
            price[i][j] = ticketPrice;
        }
    }

    //每次轉乘找最小化票價的方法
    for (int i = 0; i <= times; i++)
    {
        int availStation = end - start + 1;

    }


    return 0;
}

/*
6 0 1 4
10 90 100 70 30
30 90 80 50
20 20 90
100 60
40

100
*/