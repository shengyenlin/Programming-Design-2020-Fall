#include <iostream>
using namespace std;
int main()
{
    int length = 0, posCount = 0, pos = 0, maxCount = 0, negCount = 0;
    cin >> length;

    for (int i = 1; i <= length; i++)
    {
        int num = 0;
        cin >> num;
        if (num > 0)
        {
            posCount += 1;
        }

        else
        {
            negCount += 1;
            if (maxCount < posCount)
            {
                maxCount = posCount;
                pos = i - maxCount;
            }
            posCount = 0;
        }
    }

    if (maxCount < posCount)
    {
        maxCount = posCount;
        pos = length - maxCount + 1;
    }

    if (negCount == length)
    {
        cout << "0";
    }

    else
    {
        cout << maxCount << "," << pos;
    }
}