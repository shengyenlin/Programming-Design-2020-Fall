#include <iostream>
using namespace std;
int main()
{
    int numCity = 0, cover = 0;
    int city[20000] = {0};

    cin >> numCity >> cover;
    for (int i = 0; i < cover; i++)
    {
        city[i] = 0;
    }

    for (int i = cover; i < numCity + cover; i++)
    {
        int resident = 0;
        cin >> resident;
        city[i] = resident;
    }

    for (int i = numCity + cover; i < numCity + cover + cover; i++)
    {
        city[i] = 0;
    }

    /*
    for (int i = 0; i < numCity + cover + cover; i++)
    {
        cout << city[i] << " ";
    }
    */

    //calculate sum of residents
    int maxResident = 0;
    for (int i = cover; i < numCity + cover; i++)
    {
        int sumResident = 0;
        for (int j = 0; j <= cover; j++)
        {
            sumResident += city[i - j];
        }

        for (int j = 1; j <= cover; j++)
        {
            sumResident += city[i + j];
        }

        if (sumResident > maxResident)
        {
            maxResident = sumResident;
        }
    }

    cout << maxResident;
    return 0;
}