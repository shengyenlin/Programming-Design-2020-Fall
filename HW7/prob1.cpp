#include <iostream>

using namespace std;
int main()
{

    float productivity = 0, decreaseRate = 0, Rate0 = 0, lbRate = 0;
    int repairLen = 0, totalTime = 0, OrderNum = 0;
    cin >> productivity >> decreaseRate >> repairLen >> Rate0 >> totalTime >> lbRate >> OrderNum;

    //input order
    int orderArray[20000] = { 0 };
    for (int i = 1; i <= OrderNum; i++)
    {
        int order = 0;
        cin >> order;
        orderArray[i] = order;
    }

    //input deadline
    int deadLine[20000] = { 0 };
    for (int i = 1; i <= OrderNum; i++)
    {
        int dl = 0;
        cin >> dl;
        deadLine[i] = dl;
    }


    //count cumulative productivity
    //ttlProduct = total product
    float ttlProduct = 0;
    //currentOrder : order being processed
    int currentOrder = 1;
    //produceTime : record the time that each order begin to process, finishTime: record the time that each order is finished
    int produceTime[20000] = { 0 }, finishTime[20000] = { 0 };

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
            //record the time current order is finished
            finishTime[currentOrder] = i;
            //moving to the next order after finishing this order
            currentOrder += 1;
            //record the time the next order start to process
            produceTime[currentOrder] = i + 1;
            //reset total product produced
            ttlProduct = 0;
        }

    }

    //count delay time when without repairment
    int minDelay = 0, minRepairTime = 0;
    for (int i = 1; i <= OrderNum; i++)
    {
        if (finishTime[i] > deadLine[i])
        {
            minDelay += (finishTime[i] - deadLine[i]);
        }
    }

    //iterate the time machine can be repaired, which is the time that each order starts to produce
    for (int i = 1; i <= OrderNum; i++)
    {
        int repairTime = produceTime[i];
        int currentOrder = i;

        int finishTimeCopy[20000] = { 0 };
        //copy the original finish time
        for (int j = 1; j <= OrderNum; j++)
        {
            finishTimeCopy[j] = finishTime[j];
        }

        int produceTimeCopy[20000] = { 0 };
        //copy the original finish time
        for (int j = 1; j <= OrderNum; j++)
        {
            produceTimeCopy[j] = produceTime[j];
        }

        //recalculate each finish time
        //j: the time that product starts to process after repairment
        //duration : time passed after repairment
        float duration = 0;
        for (int j = repairTime + repairLen; j <= totalTime; j++)
        {
            float currentRate = 100 - duration * decreaseRate;
            if (currentRate <= lbRate)
            {
                currentRate = lbRate;
            }
            float product = productivity / 100 * currentRate;
            ttlProduct += product;
            if (ttlProduct >= orderArray[currentOrder])
            {
                //record the time current order is finished
                finishTimeCopy[currentOrder] = j;
                //moving to the next order after finishing this order
                currentOrder += 1;
                //record the time the next order start to process
                produceTimeCopy[currentOrder] = j + 1;
                //reset total product produced
                ttlProduct = 0;
            }
            duration++;
        }

        //count delay time for each time
        int ttlDelay = 0;
        for (int j = 1; j <= OrderNum; j++)
        {
            if (finishTimeCopy[j] > deadLine[j])
            {
                ttlDelay += (finishTimeCopy[j] - deadLine[j]);
            }
        }


        if (ttlDelay < minDelay)
        {
            minDelay = ttlDelay;
            minRepairTime = repairTime;
        }

    }

    cout << minRepairTime << "," << minDelay;
    return 0;

}