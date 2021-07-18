#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

float MAPE(int windowSize, int periodCut, const int sales[]);
int main()
{
    int periodCut = 0;
    int sales[20000] = {0}, windowSizeArray[5] = {6, 5, 4, 3, 2};
    cin >> periodCut;

    for (int i = 0; i < periodCut; i++)
    {
        int value = 0;
        cin >> value;
        sales[i] = value;
    }

    float MAPEValue = 10000;
    int bestMAPE = 10000;
    int bestWindow = 0;
    for (int i = 0; i < 5; i++)
    {
        MAPEValue = MAPE(windowSizeArray[i], periodCut, sales);
        int finalMAPE = MAPEValue * 100;
        if (finalMAPE < bestMAPE)
        {
            bestMAPE = finalMAPE;
            bestWindow = windowSizeArray[i];
        }

        //若有MAPE的百分比形式的整數位恰好皆為最小的n，則取n比較小的值做輸出。
        if (finalMAPE == bestMAPE)
        {
            if (windowSizeArray[i] < bestWindow)
            {
                bestMAPE = finalMAPE;
                bestWindow = windowSizeArray[i];
            }
        }
    }
    cout << bestWindow << "," << bestMAPE;
    return 0;
}

float MAPE(int windowSize, int periodCut, const int sales[])
{
    float MAPE = 0;
    float errorSum = 0;
    for (int i = windowSize - 1; i < periodCut; i++)
    {
        //在計算MAPE時，若x_t = 0 則應跳過該期不做計算，換言之，只把x_t != 0 的那些期的絕對誤差比率做平均即可。
        if (sales[i + 1] == 0)
        {
            continue;
        }
        else
        {
            float sum = 0;
            float avg = 0;
            for (int j = 0; j < windowSize; j++)
            {

                sum += sales[i - j];
            }
            avg = sum / windowSize;

            float error = 0;
            if (i != periodCut - 1)
            {
                error = (avg - sales[i + 1]) / sales[i + 1];
                errorSum += abs(error);
            }
        }
    }

    MAPE = errorSum / (periodCut - windowSize);

    return MAPE;
}