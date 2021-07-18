#include <iostream>
using namespace std;
int main()
{
    int intervalNum1 = 0, intervalNum2 = 0, needTic1 = 0, needTic2 = 0, budget = 0, method = 0;
    cin >> intervalNum1 >> intervalNum2 >> needTic1 >> needTic2 >> budget >> method;

    //ticketNum : 每個區間的票數, ticketPrice : 每個區間的票價, lastPrice : 每一種票的最後票價
    int ticketNum1[10000] = {0}, ticketNum2[10000] = {0}, ticketPrice1[10000] = {0}, ticketPrice2[10000] = {0}, lastPrice1 = 0, lastPrice2 = 0;

    //將票價和張數存入第一種票價的區間Array
    for (int i = 0; i < intervalNum1; i++)
    {
        int Num = 0, price = 0;
        cin >> Num >> price;
        ticketNum1[i] = Num;
        ticketPrice1[i] = price;
    }
    cin >> lastPrice1;

    //將票價和張數存入第二種票價的區間Array
    for (int i = 0; i < intervalNum2; i++)
    {
        int Num = 0, price = 0;
        cin >> Num >> price;
        ticketNum2[i] = Num;
        ticketPrice2[i] = price;
    }
    cin >> lastPrice2;

    //toalCost : 總購買成本, totalTic : 總購買張數
    int totalCost = 0, totalTic1 = 0, totalTic2 = 0;
    //currentTic : 當前區間的票數
    int currentTic1 = 0, currentTic2 = 0;

    //算買所有票數的總成本
    for (int i = 0; i < intervalNum1; i++)
    {
        if (i == 0)
        {
            currentTic1 = ticketNum1[i];
            currentTic2 = ticketNum2[i];
        }
        else
        {
            currentTic1 = ticketNum1[i] - ticketNum1[i - 1];
            currentTic2 = ticketNum2[i] - ticketNum2[i - 1];
        }

        if (totalTic1 < needTic1)
        {
            //不足的票低於區間
            if (currentTic1 >= needTic1 - totalTic1)
            {
                totalCost += (needTic1 - totalTic1) * ticketPrice1[i];
                totalTic1 += (needTic1 - totalTic1);
            }

            //購買完區間段的票，需要的票仍然沒有被滿足
            else
            {
                totalCost += currentTic1 * ticketPrice1[i];
                totalTic1 += currentTic1;
            }

            //若最後一個區間都買完了但票數仍然不足
            if (i == intervalNum1 - 1 && totalTic1 < needTic1)
            {
                totalCost += (needTic1 - totalTic1) * lastPrice1;
                totalTic1 = needTic1;
            }
        }

        if (totalTic2 < needTic2)
        {
            //不足的票低於區間
            if (currentTic2 >= needTic2 - totalTic2)
            {
                totalCost += (needTic2 - totalTic2) * ticketPrice2[i];
                totalTic2 += (needTic2 - totalTic2);
            }

            //購買完區間段的票，需要的票仍然沒有被滿足
            else
            {
                totalCost += currentTic2 * ticketPrice2[i];
                totalTic2 += currentTic2;
            }

            //若最後一個區間都買完了但票數仍然不足
            if (i == intervalNum2 - 1 && totalTic2 < needTic2)
            {
                totalCost += (needTic2 - totalTic2) * lastPrice2;
                totalTic2 = needTic2;
            }
        }
    }

    //看可不可以用預算買完
    if (totalCost <= budget)
    {
        cout << totalTic1 << "," << totalTic2 << "," << totalCost;
    }
    //不行的話才進入method//
    else
    {
        //toalCost : 總購買成本, totalTic : 總購買張數
        int totalCost = 0, totalTic1 = 0, totalTic2 = 0, optCost = 0, optTic1 = 0, optTic2 = 0;
        //方法0
        if (method == 0)
        {

            //Tic1, Tic2 :每個區間的區間長度
            //totalPrice1, totalPrice2 : 單買tic1或tic2的總和價格
            int Tic1 = 0, Tic2 = 0, totalPrice1 = 0, totalPrice2 = 0;
            int TicWanted1[1000000] = {0}, TicWanted2[1000000] = {0};
            for (int i = 0; i < intervalNum1; i++)
            {
                if (i == 0)
                {
                    Tic1 = ticketNum1[i];
                    for (int j = 0; j < Tic1; j++)
                    {
                        totalPrice1 += ticketPrice1[i];
                        TicWanted1[j] = totalPrice1;
                    }
                }
                else
                {
                    Tic1 = ticketNum1[i] - ticketNum1[i - 1];
                    for (int j = 0; j < Tic1; j++)
                    {
                        totalPrice1 += ticketPrice1[i];
                        TicWanted1[ticketNum1[i] - Tic1 + j] = totalPrice1;
                    }
                }

                if (i == intervalNum1 - 1 && needTic1 - ticketNum1[i] > 0)
                {
                    int addtionTic = needTic1 - ticketNum1[i];
                    for (int j = 0; j < addtionTic; j++)
                    {
                        totalPrice1 += lastPrice1;
                        TicWanted1[ticketNum1[i] + j] = totalPrice1;
                    }
                }
            }

            for (int i = 0; i < intervalNum2; i++)
            {
                if (i == 0)
                {
                    Tic2 = ticketNum2[i];
                    for (int j = 0; j < Tic2; j++)
                    {
                        totalPrice2 += ticketPrice2[i];
                        TicWanted2[j] = totalPrice2;
                    }
                }
                else
                {
                    Tic2 = ticketNum2[i] - ticketNum2[i - 1];
                    for (int j = 0; j < Tic2; j++)
                    {
                        totalPrice2 += ticketPrice2[i];
                        TicWanted2[ticketNum2[i] - Tic2 + j] = totalPrice2;
                    }
                }

                if (i == intervalNum2 - 1 && needTic2 - ticketNum2[i] > 0)
                {
                    int addtionTic = needTic2 - ticketNum2[i];
                    for (int j = 0; j < addtionTic; j++)
                    {
                        totalPrice2 += lastPrice2;
                        TicWanted2[ticketNum2[i] + j] = totalPrice2;
                    }
                }
            }

            //策略
            //暴力搜尋: 迴圈進行x1 * x2次
            //測試每一組結果若符合條件就更新成最佳的張數
            totalTic1 = 0;
            for (int i = 0; i < needTic1; i++)
            {
                totalTic1 += 1;

                for (int k = 0; k < needTic2; k++)
                {
                    totalCost = TicWanted1[i] + TicWanted2[k];
                    totalTic2 += 1;
                    if (totalCost <= budget)
                    {
                        //最大化總票數。若平手，則選票數乘積最大者；若還是平手，則選第一種票票數較多者。
                        if (totalTic1 + totalTic2 > optTic1 + optTic2)
                        {
                            optTic1 = totalTic1;
                            optTic2 = totalTic2;
                            optCost = totalCost;
                        }
                        else if (totalTic1 + totalTic2 == optTic1 + optTic2)
                        {
                            if (totalTic1 * totalTic2 > optTic1 * optTic2)
                            {
                                optTic1 = totalTic1;
                                optTic2 = totalTic2;
                                optCost = totalCost;
                            }

                            if (totalTic1 * totalTic2 == optTic1 * optTic2)
                            {
                                if (totalTic1 > optTic1)
                                {
                                    optTic1 = totalTic1;
                                    optTic2 = totalTic2;
                                    optCost = totalCost;
                                }
                            }
                        }
                    }
                    totalCost = 0;
                }
                totalTic2 = 0;
            }

            cout << optTic1 << "," << optTic2 << "," << optCost;
        }

        //方法1 : 先最大化第一種票//
        if (method == 1)
        {
            for (int i = 0; i < intervalNum1; i++)
            {
                int currentTic1 = 0;
                //currentTic : 當前區段的票數
                if (i == 0)
                {
                    currentTic1 = ticketNum1[i];
                }
                else
                {
                    currentTic1 = ticketNum1[i] - ticketNum1[i - 1];
                }

                //先檢查預算有沒有足夠
                if (budget > totalCost)
                {
                    //當第一種數量的票不滿足就繼續買
                    if (totalTic1 < needTic1)
                    {
                        //若這個區間段的票大於剩下需要買的票數就只購買需要的票數
                        if (currentTic1 >= needTic1 - totalTic1)
                        {
                            //檢查預算，若不足則買剩下的錢可以購買的票
                            if (budget < totalCost + (needTic1 - totalTic1) * ticketPrice1[i])
                            {
                                int leftMoney = budget - totalCost;
                                //leftTic: 剩下的錢最多可以購買的張數
                                int leftTic = leftMoney / ticketPrice1[i];
                                totalCost += leftTic * ticketPrice1[i];
                                totalTic1 += leftTic;
                                break;
                            }
                            else
                            {
                                totalCost += (needTic1 - totalTic1) * ticketPrice1[i];
                                totalTic1 += (needTic1 - totalTic1);
                            }
                        }

                        //購買完區間段的票，需要的票仍然沒有被滿足
                        else
                        {
                            //檢查預算，若不足則買剩下的錢可以購買的票
                            if (budget < totalCost + currentTic1 * ticketPrice1[i])
                            {
                                int leftMoney = budget - totalCost;
                                //leftTic: 剩下的錢最多可以購買的張數
                                int leftTic = leftMoney / ticketPrice1[i];
                                totalCost += leftTic * ticketPrice1[i];
                                totalTic1 += leftTic;
                                break;
                            }
                            else
                            {
                                totalCost += currentTic1 * ticketPrice1[i];
                                totalTic1 += currentTic1;
                            }
                        }

                        //若最後一個區間都買完了但票數仍然不足
                        if (i == intervalNum1 - 1 && totalTic1 < needTic1)
                        {
                            //檢查預算能不能買到想要的票，若不足則買剩下的錢可以購買的票
                            if (budget < totalCost + (needTic1 - totalTic1) * lastPrice1)
                            {
                                int leftMoney = budget - totalCost;
                                //leftTic: 剩下的錢最多可以購買的張數
                                int leftTic = leftMoney / lastPrice1;
                                totalCost += leftTic * lastPrice1;
                                totalTic1 += leftTic;
                                break;
                            }
                            else
                            {
                                totalCost += (needTic1 - totalTic1) * lastPrice1;
                                totalTic1 = needTic1;
                            }
                        }
                    }
                }
            }

            //第一種票買完開始買第二種票
            for (int i = 0; i < intervalNum2; i++)
            {
                int currentTic2 = 0;
                //currentTic : 當前區段的票數
                if (i == 0)
                {
                    currentTic2 = ticketNum2[i];
                }
                else
                {
                    currentTic2 = ticketNum2[i] - ticketNum2[i - 1];
                }
                //若這個區間段的票大於剩下需要買的票數就只購買需要的票數
                if (currentTic2 >= needTic2 - totalTic2)
                {
                    //檢查預算，若不足則買剩下的錢可以購買的票
                    if (budget < totalCost + (needTic2 - totalTic2) * ticketPrice2[i])
                    {
                        int leftMoney = budget - totalCost;
                        //leftTic: 剩下的錢最多可以購買的張數
                        int leftTic = leftMoney / ticketPrice2[i];
                        totalCost += leftTic * ticketPrice2[i];
                        totalTic2 += leftTic;
                        break;
                    }
                    else
                    {
                        totalCost += (needTic2 - totalTic2) * ticketPrice2[i];
                        totalTic2 += (needTic2 - totalTic2);
                    }
                }

                //購買完區間段的票，需要的票仍然沒有被滿足
                else
                {
                    //檢查預算，若不足則買剩下的錢可以購買的票
                    if (budget < totalCost + currentTic2 * ticketPrice2[i])
                    {
                        int leftMoney = budget - totalCost;
                        //leftTic: 剩下的錢最多可以購買的張數
                        int leftTic = leftMoney / ticketPrice2[i];
                        totalCost += leftTic * ticketPrice2[i];
                        totalTic2 += leftTic;
                        break;
                    }
                    else
                    {
                        totalCost += currentTic2 * ticketPrice2[i];
                        totalTic2 += currentTic2;
                    }
                }

                //若最後一個區間都買完了但票數仍然不足
                if (i == intervalNum2 - 1 && totalTic2 < needTic2)
                {
                    //檢查預算能不能買到想要的票，若不足則買剩下的錢可以購買的票
                    if (budget < totalCost + (needTic2 - totalTic2) * lastPrice2)
                    {
                        int leftMoney = budget - totalCost;
                        //leftTic: 剩下的錢最多可以購買的張數
                        int leftTic = leftMoney / lastPrice2;
                        totalCost += leftTic * lastPrice2;
                        totalTic2 += leftTic;
                        break;
                    }
                    else
                    {
                        totalCost += (needTic2 - totalTic2) * lastPrice2;
                        totalTic2 = needTic2;
                    }
                }
            }
            cout << totalTic1 << "," << totalTic2 << "," << totalCost;
        }

        //方法2 : 先最大化第二種票
        if (method == 2)
        {
            for (int i = 0; i < intervalNum2; i++)
            {
                int currentTic2 = 0;
                //currentTic : 當前區段的票數
                if (i == 0)
                {
                    currentTic2 = ticketNum2[i];
                }
                else
                {
                    currentTic2 = ticketNum2[i] - ticketNum2[i - 1];
                }

                //先檢查預算有沒有足夠
                if (budget > totalCost)
                {
                    //當第二種數量的票不滿足就繼續買
                    if (totalTic2 < needTic2)
                    {
                        //若這個區間段的票大於剩下需要買的票數就只購買需要的票數
                        if (currentTic2 >= needTic2 - totalTic2)
                        {
                            //檢查預算，若不足則買剩下的錢可以購買的票
                            if (budget < totalCost + (needTic2 - totalTic2) * ticketPrice2[i])
                            {
                                int leftMoney = budget - totalCost;
                                //leftTic: 剩下的錢最多可以購買的張數
                                int leftTic = leftMoney / ticketPrice2[i];
                                totalCost += leftTic * ticketPrice2[i];
                                totalTic2 += leftTic;
                                break;
                            }
                            else
                            {
                                totalCost += (needTic2 - totalTic2) * ticketPrice2[i];
                                totalTic2 += (needTic2 - totalTic2);
                            }
                        }

                        //購買完區間段的票，需要的票仍然沒有被滿足
                        else
                        {
                            //檢查預算，若不足則買剩下的錢可以購買的票
                            if (budget < totalCost + currentTic2 * ticketPrice2[i])
                            {
                                int leftMoney = budget - totalCost;
                                //leftTic: 剩下的錢最多可以購買的張數
                                int leftTic = leftMoney / ticketPrice2[i];
                                totalCost += leftTic * ticketPrice2[i];
                                totalTic2 += leftTic;
                                break;
                            }
                            else
                            {
                                totalCost += currentTic2 * ticketPrice2[i];
                                totalTic2 += currentTic2;
                            }
                        }

                        //若最後一個區間都買完了但票數仍然不足
                        if (i == intervalNum2 - 1 && totalTic2 < needTic2)
                        {
                            //檢查預算能不能買到想要的票，若不足則買剩下的錢可以購買的票
                            if (budget < totalCost + (needTic2 - totalTic2) * lastPrice2)
                            {
                                int leftMoney = budget - totalCost;
                                //leftTic: 剩下的錢最多可以購買的張數
                                int leftTic = leftMoney / lastPrice2;
                                totalCost += leftTic * lastPrice2;
                                totalTic2 += leftTic;
                                break;
                            }
                            else
                            {
                                totalCost += (needTic2 - totalTic2) * lastPrice2;
                                totalTic2 = needTic2;
                            }
                        }
                    }
                }
            }

            //第二種票買完開始買第一種票
            for (int i = 0; i < intervalNum1; i++)
            {
                int currentTic1 = 0;
                //currentTic : 當前區段的票數
                if (i == 0)
                {
                    currentTic1 = ticketNum1[i];
                }
                else
                {
                    currentTic1 = ticketNum1[i] - ticketNum1[i - 1];
                }
                //若這個區間段的票大於剩下需要買的票數就只購買需要的票數
                if (currentTic1 >= needTic1 - totalTic1)
                {
                    //檢查預算，若不足則買剩下的錢可以購買的票
                    if (budget < totalCost + (needTic1 - totalTic1) * ticketPrice1[i])
                    {
                        int leftMoney = budget - totalCost;
                        //leftTic: 剩下的錢最多可以購買的張數
                        int leftTic = leftMoney / ticketPrice1[i];
                        totalCost += leftTic * ticketPrice1[i];
                        totalTic1 += leftTic;
                        break;
                    }
                    else
                    {
                        totalCost += (needTic1 - totalTic1) * ticketPrice1[i];
                        totalTic1 += (needTic1 - totalTic1);
                    }
                }

                //購買完區間段的票，需要的票仍然沒有被滿足
                else
                {
                    //檢查預算，若不足則買剩下的錢可以購買的票
                    if (budget < totalCost + currentTic1 * ticketPrice1[i])
                    {
                        int leftMoney = budget - totalCost;
                        //leftTic: 剩下的錢最多可以購買的張數
                        int leftTic = leftMoney / ticketPrice1[i];
                        totalCost += leftTic * ticketPrice1[i];
                        totalTic1 += leftTic;
                        break;
                    }
                    else
                    {
                        totalCost += currentTic1 * ticketPrice1[i];
                        totalTic1 += currentTic1;
                    }
                }

                //若最後一個區間都買完了但票數仍然不足
                if (i == intervalNum1 - 1 && totalTic1 < needTic1)
                {
                    //檢查預算能不能買到想要的票，若不足則買剩下的錢可以購買的票
                    if (budget < totalCost + (needTic1 - totalTic1) * lastPrice1)
                    {
                        int leftMoney = budget - totalCost;
                        //leftTic: 剩下的錢最多可以購買的張數
                        int leftTic = leftMoney / lastPrice1;
                        totalCost += leftTic * lastPrice1;
                        totalTic1 += leftTic;
                        break;
                    }
                    else
                    {
                        totalCost += (needTic1 - totalTic1) * lastPrice1;
                        totalTic1 = needTic1;
                    }
                }
            }
            cout << totalTic1 << "," << totalTic2 << "," << totalCost;
        }
    }

    return 0;
}