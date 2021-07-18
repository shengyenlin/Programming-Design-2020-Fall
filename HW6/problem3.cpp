#include <iostream>
using namespace std;
int main()
{

    float productivity = 0;
    int repairLen = 0, totalTime = 0, OrderNum;
    float decreaseRate = 0, Rate0 = 0, lbRate = 0;
    cin >> productivity >> decreaseRate >> repairLen >> Rate0 >> totalTime >> lbRate >> OrderNum;

    //input order
    int orderArray[20000] = { 0 };
    for (int i = 1; i <= OrderNum; i++)
    {
        int order = 0;
        cin >> order;
        orderArray[i] = order;
    }

    //count cumulative productivity
    //ttlProduct = total product
    float ttlProduct = 0;
    //currentOrder : order being processed
    int currentOrder = 1;
    //produceTime : record the time that each order begin to process
    int produceTime[20000] = { 0 };

    //the first order must start at t = 1
    produceTime[currentOrder] = 1;
    for (int i = 1; i <= totalTime; i++)
    {
        float currentRate = Rate0 - i * decreaseRate;
        if (currentRate <= lbRate)
        {
            currentRate = lbRate;
        }
        float product = productivity / 100 * currentRate;
        ttlProduct += product;
        if (ttlProduct >= orderArray[currentOrder])
        {
            //moving to the next order after finishing this order
            currentOrder += 1;
            //record the time the next order start to process
            produceTime[currentOrder] = i + 1;
            //reset total product produced
            ttlProduct = 0;
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