#include <iostream>
using namespace std;
int main()
{

    int productivity = 0, repairLen = 0, totalTime = 0, OrderNum;
    int decreaseRate = 0, Rate0 = 0, lbRate = 0;
    cin >> productivity >> decreaseRate >> repairLen >> Rate0 >> totalTime >> lbRate >> OrderNum;

    //ttlProduct = total product, currentOrder : order being processed
    int ttlProduct = 0, currentOrder = 1;
    //produceTime : record the time that each order begin to process
    int produceTime[21] = {0};
    //the first order must start at t = 1
    produceTime[currentOrder] = 1;
    //process start from t = 1
    int start = 1;

    //count cumulative productivity
    for (int i = 1; i <= OrderNum; i++)
    {
        int order = 0;
        cin >> order;

        for (int j = start; j <= totalTime; j++)
        {
            int currentRate = Rate0 - j * decreaseRate;
            if (currentRate <= lbRate)
            {
                currentRate = lbRate;
            }
            int product = productivity / 100 * currentRate;
            ttlProduct += product;
            if (ttlProduct >= order)
            {
                //moving to the next order after finishing this order
                currentOrder += 1;
                //record the time the next order start to process
                produceTime[currentOrder] = j + 1;
                //reset total product produced
                ttlProduct = 0;
            }
            start += 1;
            cout << start << " ";
        }
    }

    //print result
    for (int i = 1; i <= OrderNum; i++)
    {
        if (i == 1)
        {
            cout << produceTime[i];
        }

        else
        {
            cout << "," << produceTime[i];
        }
    }

    return 0;
}