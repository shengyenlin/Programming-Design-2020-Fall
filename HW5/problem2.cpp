#include <iostream>

using namespace std;

int main()
{
    int xlim = 0, ylim = 0, cover = 0;
    cin >> xlim >> ylim >> cover;
    int resident[1000][1000] = {0};
    for (int i = 0; i <= ylim; i++)
    {
        for (int j = 0; j <= xlim; j++)
        {
            int value = 0;
            cin >> value;
            resident[i][j] = value;
        }
    }

    for (int i = 0; i <= ylim; i++)
    {
        for (int j = 0; j <= xlim; j++)
        {
            cout << resident[i][j];
        }
    }

    return 0;
}