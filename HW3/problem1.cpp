#include <iostream>
using namespace std;
int main()
{

    int intervalNum = 0, needTicket = 0;
    cin >> intervalNum >> needTicket;
    int ticketNum[30] = {0}, ticketPrice[30] = {0};
    for (int i = 0; i < intervalNum; i++)
    {
        int Num = 0, price = 0;
        cin >> Num >> price;
        ticketNum[i] = Num;
        ticketPrice[i] = price;
    }

    int lastPrice = 0;
    cin >> lastPrice;
    for (int i = intervalNum - 1; i >= 0; i--)
    {
        if (i != 0)
        {
            ticketNum[i] = ticketNum[i] - ticketNum[i - 1];
        }

        else
        {
            ticketNum[i] = ticketNum[i];
        }
    }

    int totalTicket[30] = {0}, totalcost[30] = {0};

    for (int i = 0; i < intervalNum; i++)
    {
        if (i != 0)
        {
            totalcost[i] = totalcost[i - 1] + ticketPrice[i] * ticketNum[i];
            totalTicket[i] = totalTicket[i - 1] + ticketNum[i];
        }

        else
        {
            totalTicket[i] = ticketNum[i];
            totalcost[i] = ticketPrice[i] * ticketNum[i];
        }
    }

    int optTic = 0, optCost = 100000, optindex = 0;
    for (int i = 0; i < intervalNum; i++)
    {
        if (totalTicket[i] >= needTicket)
        {
            if (totalcost[i] < optCost)
            {
                optTic = totalTicket[i];
                optCost = totalcost[i];
                optindex = i;
            }
        }

        if ((i == intervalNum - 1) && totalTicket[i] <= needTicket)
        {
            optCost = totalcost[i] + (needTicket - totalTicket[i]) * lastPrice;
            optTic = needTicket;
        }
    }
    if (optTic >= needTicket)
    {
        if (ticketPrice[optindex] > 0)
        {
            optCost = optCost - (optTic - needTicket) * ticketPrice[optindex];
            optTic = needTicket;
        }
    }
    cout << optTic << "," << optCost;
    return 0;
}