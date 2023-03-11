#include <iostream>
#include <cstdlib>
using namespace std;

void orderSwitch(int j, int* number);
void orderDistribute(int numO, int m, int* a, int* b, int* L, int* oQ, int* oT, int* oN, int** mO, int* mOA, int* mPR, int* mA, int* mDT);
void machineRepairSwitch(int n1, int n2, int* mR);
void determineRepair_1(int numM, int numW, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* mDT, int** wF, int** rL);
int determineRepair_2(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* mDT, int** wF, int** rL, int* mR, int i, int m);
void workerFreeUpdate_1(int numM, int numW, int* a, int* b, int* c, int* p, int* L, int* oQ, int** mO, int* mOA, int** wF, int** rL);
void workerFreeUpdate_2(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int** mO, int* mOA, int** wF, int** rL);

int reCalculate(int numM, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* rIA);
int tryRepair_Delay(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int** wF, int** rL);
int freeWorker(int numM, int h, int time, int* c, int** wF);



int main() {

    //INPUT處理
    //m:機台數量, n:訂單數量, h:同一時段最多維修機台數
    int m = 0, n = 0, h = 0;
    cin >> m >> n >> h;

    //a:每機台每小時生產速率, b:良率遞減速度, c:機台維修時間, p:初始良率, l:lower bond
    int* a = new int[m + 1];
    int* b = new int[m + 1];
    int* c = new int[m + 1];
    int* p = new int[m + 1];
    int* L = new int[m + 1];

    for (int i = 1; i <= m; i++)
        cin >> a[i] >> b[i] >> c[i] >> p[i] >> L[i];

    int* orderQuant = new int[n + 1];
    int* orderTime = new int[n + 1];

    for (int i = 1; i <= n; i++)
        cin >> orderQuant[i] >> orderTime[i];


    /////////////////////////////Order Sorting/////////////////////////////

    //Condition : 1.越快到期越前面 2.訂單量越大越前面 (bubble sorting method)

    int* orderNumber = new int[n + 1];            //record the serial number of each order 
    for (int i = 1; i <= n; i++)
        orderNumber[i] = i;

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            int n1 = orderNumber[j], n2 = orderNumber[j + 1];

            if (orderTime[n1] > orderTime[n2])
                orderSwitch(j, orderNumber);

            else if (orderTime[n1] == orderTime[n2] && orderQuant[n1] < orderQuant[n2])
                orderSwitch(j, orderNumber);
        }
    }


    /////////////////////////////Order Distribution/////////////////////////////

    //Goal : 依照訂單順序分配置合適的機台 
    //Condition : 1.最小化延遲時間/盡早完成訂單 2.選擇產能最低的機台(時間一樣的情況) 

    int** machineOrder = new int* [m + 1];            //machineOrder[i] : orders which are distributed to the ith machine
    for (int i = 1; i <= m; i++)
        machineOrder[i] = new int[n + 1];

    int* machineOrderAmount = new int[m + 1];        //machineOrderAmount[i] : the amount of orders for the ith machine
    for (int i = 1; i <= m; i++)
        machineOrderAmount[i] = 0;

    int* machineProductionRate = new int[m + 1];      //Production Rate when the last order complete
    int* machineAvailable = new int[m + 1];      //Time Point  when the machine complete the last order
    int* machineDelayTotal = new int[m + 1];

    //初始化 machineProductionRate,  machineAvailable, machineDelayTotal
    for (int i = 1; i <= m; i++)
    {
        machineProductionRate[i] = p[i] - b[i];
        if (machineProductionRate[i] < L[i])
            machineProductionRate[i] = L[i];

        machineAvailable[i] = 0;
        machineDelayTotal[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        orderDistribute(orderNumber[i], m, a, b, L, orderQuant, orderTime, orderNumber,
            machineOrder, machineOrderAmount, machineProductionRate, machineAvailable, machineDelayTotal);
    }


    /////////////////////////////Repair Decision/////////////////////////////

    //Goal : 分配維修人員到不同的機台
    //Condition : 1. 總延遲時間最多的機台 2. 訂單量最大的機台 3. 每小時產量(a)最大的機台

    //安排機台的維修順序
    int* machineRepair = new int[m + 1];              //the serial number of machine to be repaired 
    for (int i = 1; i <= m; i++)
        machineRepair[i] = i;
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j <= (m - i); j++)
        {
            if (machineDelayTotal[j] < machineDelayTotal[j + 1])
                machineRepairSwitch(j, j + 1, machineRepair);

            else if (machineDelayTotal[j] == machineDelayTotal[j + 1])
            {
                int sum1 = 0, sum2 = 0;
                for (int k = 1; k <= machineOrderAmount[j]; k++)
                    sum1 += orderQuant[machineOrder[j][k]];

                for (int k = 1; k <= machineOrderAmount[j + 1]; k++)
                    sum2 += orderQuant[machineOrder[j + 1][k]];

                if (sum1 < sum2)
                    machineRepairSwitch(j, j + 1, machineRepair);

                else if (sum1 == sum2 && a[j] < a[j + 1])
                    machineRepairSwitch(j, j + 1, machineRepair);
            }
        }

    }

    //利用 maxProductionTime 判斷 workerFree 所需配置之動態記憶體大小 
    int maxProductionTime = 0;
    for (int i = 1; i <= m; i++)
    {
        if (maxProductionTime < machineAvailable[i])
            maxProductionTime = machineAvailable[i];
    }
    int** workerFree = new int* [h + 1];
    for (int i = 1; i <= h; i++)
    {
        //避免記憶體空間不足 故配置 maxProductionTime + 10000 的空間 
        workerFree[i] = new int[maxProductionTime + 10001];
        for (int j = 1; j <= maxProductionTime + 10000; j++)
            workerFree[i][j] = 1;
    }

    //分配維修人員
    int** repairList = new int* [m + 1];               //repairList[i][j] = 1 
                                                    //if needed to be "REPAIR" before the jth order produced by the ith machine  
    for (int i = 1; i <= m; i++)
    {
        repairList[i] = new int[machineOrderAmount[i] + 1];
        for (int j = 1; j <= machineOrderAmount[i]; j++)
            repairList[i][j] = 0;
    }

    int* ifMachineCanRepair = new int[m + 1]; //紀錄機器還能不能塞維修 
    for (int i = 1; i <= m; i++)
        ifMachineCanRepair[i] = 1;  //0是已經塞不下維修了 

    for (int i = 1; i <= m; i++)
    {
        /*if(i <= h && machineDelayTotal[ machineRepair[i] ] > 0)
        {
            determineRepair_1(machineRepair[i], i, a, b, c, p, L, orderQuant, orderTime,
                              machineOrder, machineOrderAmount, machineDelayTotal, workerFree, repairList);
        }
        else*/


        if (machineDelayTotal[machineRepair[i]] > 0)
        {
            while (ifMachineCanRepair[machineRepair[i]] == 1)
                ifMachineCanRepair[machineRepair[i]] = determineRepair_2(machineRepair[i], h, a, b, c, p, L, orderQuant, orderTime,
                    machineOrder, machineOrderAmount, machineDelayTotal, workerFree, repairList, machineRepair, i, m);
        }
    }


    /////////////////////////////Print Out Result///////////////////////////// 
    for (int i = 1; i <= m; i++)
    {
        if (machineOrderAmount[i] == 0)
            cout << 0;

        else
        {
            for (int j = 1; j <= machineOrderAmount[i]; j++)
            {
                if (repairList[i][j] == 1)
                    cout << "M,";

                if (j == machineOrderAmount[i])
                    cout << machineOrder[i][j];
                else
                    cout << machineOrder[i][j] << ",";
            }
        }

        if (i != m)
            cout << "\n";
    }

    return 0;
}

/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*--    ##########    ##      ##     ##        ##    ##########   ##########    ######      ##########    ##        ##  --*/
/*--    ##            ##      ##     ####      ##    ##               ##          ##        ##      ##    ####      ##  --*/
/*--    ##            ##      ##     ##  ##    ##    ##               ##          ##        ##      ##    ##  ##    ##  --*/
/*--    #########     ##      ##     ##    ##  ##    ##               ##          ##        ##      ##    ##    ##  ##  --*/
/*--    ##            ##      ##     ##      ####    ##               ##          ##        ##      ##    ##      ####  --*/
/*--    ##            ##########     ##        ##    ##########       ##       ########     ##########    ##        ##  --*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/


void orderSwitch(int j, int* number)
{
    int temp = number[j];
    number[j] = number[j + 1];
    number[j + 1] = temp;
};


void orderDistribute(int numO, int m, int* a, int* b, int* L, int* oQ, int* oT, int* oN, int** mO, int* mOA, int* mPR, int* mA, int* mDT)
{
    /*numO                  : the index of order after sorting, which is being distributed                                  */
    /*oQ, oT,  oN           : orderQuant, orderTime, orderNumber                                                            */
    /*mO, mOA, mPR, mA, mDT : machineOrder, machineOrderAmount, machineProductionRate, machineAvailable, machineDelayTotal  */
    int* machineMightDelay = new int[m + 1];
    int* machineFinalPR = new int[m + 1];


    /////////////////////////////Calculation/////////////////////////////

    //計算任一機器生產第numO筆訂單 : "延遲時間", "訂單完成時的產能" 
    for (int i = 1; i <= m; i++)
    {
        float quant = oQ[numO];
        int   count = 0;
        int   produceRate = mPR[i];

        while (quant > 0)
        {
            count++;
            quant -= produceRate * a[i] * 0.01;

            if (produceRate - b[i] > L[i])
                produceRate -= b[i];
            else
                produceRate = L[i];
        }

        machineMightDelay[i] = mA[i] + count - oT[numO];    //val = integer (might be negative or 0) 
        machineFinalPR[i] = produceRate;
    }


    /////////////////////////////Compare/////////////////////////////

    //效能比較基準 :  a[i] * machineFinalPR[i] (i.e. 每台機器生產完後，還可以再生產多少產品)
    //machineNumber : numO這個單要排給哪一台機器
    int minDelay = machineMightDelay[1], machineNumber = 1, production = a[1] * machineFinalPR[1];
    for (int i = 1; i <= m; i++)
    {
        if (minDelay > machineMightDelay[i])
        {
            minDelay = machineMightDelay[i];
            production = a[i] * machineFinalPR[i];
            machineNumber = i;
        }
        //讓生產最少產品的機器可以完成這筆訂單(不要浪費其他可以生產很多的機器)
        else if (minDelay == machineMightDelay[i] && production > a[i] * machineFinalPR[i])
        {
            minDelay = machineMightDelay[i];
            production = a[i] * machineFinalPR[i];
            machineNumber = i;
        }

    }

    /////////////////////////////Save Results/////////////////////////////

    mPR[machineNumber] = machineFinalPR[machineNumber];
    //mA:machine結束生產的時間
    mA[machineNumber] = machineMightDelay[machineNumber] + oT[numO];
    //提前生產結束不須計入 
    if (minDelay > 0)
        mDT[machineNumber] += minDelay;
    //訂單編號存入mO、更新該機台生產的訂單數量(mOA) 
    int newLen = mOA[machineNumber] + 1;
    mO[machineNumber][newLen] = numO;
    mOA[machineNumber] += 1;


    delete[] machineMightDelay;
    delete[] machineFinalPR;
};


void machineRepairSwitch(int n1, int n2, int* mR)
{
    int temp = mR[n1];
    mR[n1] = mR[n2];
    mR[n2] = temp;
};

/*
void determineRepair_1(int numM, int numW, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* mDT, int** wF, int** rL)
{
    //numM  : the index of machine
    //numW  : the index of worker who is assigned to repair the selected machine
    int delayAfterRepair = mDT[numM];                       //the standard to determine whether to repair the machine or not
    int* repairInAdvance = new int[ mOA[numM] + 1 ];
    for(int i=1;i <= mOA[numM];i++)
        repairInAdvance[i] = 0;

    for(int i=1;i <= mOA[numM];i++)
    {
        int upperDelay = delayAfterRepair, repairTimePoint = 0;

        //Condition : 每次在一個訂單前嘗試維修, 找出減少"最新總延遲時間"最多的訂單
        for(int j=1;j <= mOA[numM];j++)
        {
            if(repairInAdvance[j] == 0)
            {
                repairInAdvance[j] = 1;
                int delayTemp = reCalculate(numM, a, b, c, p, L, oQ, oT, mO, mOA, repairInAdvance);

                if(delayTemp < upperDelay)
                {
                    upperDelay = delayTemp;
                    repairTimePoint = j;
                }

                repairInAdvance[j] = 0;
            }
        }

        if(repairTimePoint == 0)
            break;
        else
        {
            repairInAdvance[ repairTimePoint ] = 1;
            delayAfterRepair = reCalculate(numM, a, b, c, p, L, oQ, oT, mO, mOA, repairInAdvance);
        }

    }

    for(int i=1;i <= mOA[numM];i++)
        rL[numM][i] = repairInAdvance[i];

    delete [] repairInAdvance;

    //更新workerFree
    workerFreeUpdate_1(numM, numW, a, b, c, p, L, oQ, mO, mOA, wF, rL);
};
*/

/*
determineRepair_2(machineRepair[i], h, a, b, c, p, L, orderQuant, orderTime,
                              machineOrder, machineOrderAmount, machineDelayTotal, workerFree, repairList)
*/

int determineRepair_2(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO,
    int* mOA, int* mDT, int** wF, int** rL, int* mR, int sequenceInRepair, int m)
{
    int upperDelay = mDT[numM];                     //the standard to determine whether to repair the machine or not
    //int* repairInAdvance = new int[ mOA[numM] + 1 ];
    //for(int i=1;i <= mOA[numM];i++)
    //  repairInAdvance[i] = 0;

    //每次找出能減少最多延遲時間的維修方式(暫定：不回頭檢查) 
    /*
    for(int i=1;i <= mOA[numM];i++)
    {
        int upperDelay = delayAfterRepair, repairTimePoint = 0;
    */
    //Condition : 每次在一個訂單前嘗試維修, 找出減少"最新總延遲時間"最多的訂單 
    int repairTimePoint = 0;
    for (int j = 1; j <= mOA[numM]; j++)
    {
        if (rL[numM][j] == 0)
        {
            rL[numM][j] = 1;

            //是否有閒置人力？ 若有回傳總延遲時間；反之，回傳-1
            int delayTemp = tryRepair_Delay(numM, h, a, b, c, p, L, oQ, oT, mO, mOA, wF, rL);

            if (delayTemp < upperDelay && delayTemp >= 0)
            {
                upperDelay = delayTemp;
                repairTimePoint = j;
            }

            rL[numM][j] = 0;
        }
    }

    if (repairTimePoint == 0)
        return 0; //代表這個機器已經塞不下維修了 
    else
    {
        rL[numM][repairTimePoint] = 1;
        mDT[numM] = upperDelay; //更新新的維修延遲 

        for (int j = sequenceInRepair; j < m; j++)
        {
            if (mDT[j] <= mDT[j + 1])
                machineRepairSwitch(j, j + 1, mR);
        }


        //這邊應該是完成一次更新，然後要計算新的delayAfterTime並重新排順序 
    }

    //}

    //delete [] repairInAdvance;

    //更新workerFree
    workerFreeUpdate_2(numM, h, a, b, c, p, L, oQ, mO, mOA, wF, rL);
    return 1;

};


int reCalculate(int numM, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int** rL)
{
    int totalDelay = 0, time = 0, produceRate = p[numM] - b[numM];
    if (produceRate < L[numM])
        produceRate = L[numM];

    for (int i = 1; i <= mOA[numM]; i++)
    {
        int   numO = mO[numM][i];
        float quant = oQ[numO];
        int   count = 0;

        //根據repairInAdvance的資料進行維修      
        if (rL[numM][i] == 1)
        {
            time += c[numM];
            produceRate = 100;
        }

        //計算所需的生產時間 
        while (quant > 0)
        {
            count++;
            quant -= produceRate * a[numM] * 0.01;

            if (produceRate - b[numM] > L[numM])
                produceRate -= b[numM];
            else
                produceRate = L[numM];
        }

        //更新總生產時間&總延遲時間 
        time += count;
        if (time - oT[numO] > 0)
            totalDelay += time - oT[numO];
    }

    return totalDelay;
};


void workerFreeUpdate_1(int numM, int numW, int* a, int* b, int* c, int* p, int* L, int* oQ, int** mO, int* mOA, int** wF, int** rL)
{
    int time = 0, produceRate = p[numM] - b[numM];
    if (produceRate < L[numM])
        produceRate = L[numM];

    for (int i = 1; i <= mOA[numM]; i++)
    {
        int   numO = mO[numM][i];
        float quant = oQ[numO];
        int   count = 0;

        //根據repairList進行維修      
        if (rL[numM][i] == 1)
        {
            //更新維修人員的工作時間 
            for (int j = time + 1; j <= time + c[numM]; j++)
                wF[numW][j] = 0;

            time += c[numM];
            produceRate = 100;
        }

        //計算所需的生產時間 
        while (quant > 0)
        {
            count++;
            quant -= produceRate * a[numM] * 0.01;

            if (produceRate - b[numM] > L[numM])
                produceRate -= b[numM];
            else
                produceRate = L[numM];
        }

        //更新總生產時間
        time += count;
    }

};


int tryRepair_Delay(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int** wF, int** rL)
{
    int totalDelay = 0, time = 0, produceRate = p[numM] - b[numM];
    if (produceRate < L[numM])
        produceRate = L[numM];

    for (int i = 1; i <= mOA[numM]; i++)
    {
        int   numO = mO[numM][i];
        float quant = oQ[numO];
        int   count = 0;

        if (rL[numM][i] == 1)
        {
            //檢查"該次預期維修的時間點"是否有多餘的人力進行維修    
            int available = freeWorker(numM, h, time, c, wF);
            if (available == 0)
                return -1;

            time += c[numM];
            produceRate = 100;
        }

        //計算所需的生產時間 
        while (quant > 0)
        {
            count++;
            quant -= produceRate * a[numM] * 0.01;

            if (produceRate - b[numM] > L[numM])
                produceRate -= b[numM];
            else
                produceRate = L[numM];
        }

        //更新總生產時間
        time += count;
        if (time - oT[numO] > 0)
            totalDelay += time - oT[numO];
    }

    return totalDelay;
};


int freeWorker(int numM, int h, int time, int* c, int** wF)
{
    for (int i = time + 1; i <= time + c[numM]; i++)
    {
        int free = 0;
        for (int j = 1; j <= h; j++)
            free += wF[j][i];

        if (free == 0)
            return 0;
    }

    return 1;
};


void workerFreeUpdate_2(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int** mO, int* mOA, int** wF, int** rL)
{
    int time = 0, produceRate = p[numM] - b[numM];
    if (produceRate < L[numM])
        produceRate = L[numM];

    for (int i = 1; i <= mOA[numM]; i++)
    {
        int   numO = mO[numM][i];
        float quant = oQ[numO];
        int   count = 0;

        //根據repairList進行維修      
        if (rL[numM][i] == 1)
        {
            //找出閒置的員工 
            for (int j = time + 1; j <= time + c[numM]; j++)
            {
                for (int k = 1; k <= h; k++)
                {
                    if (wF[k][j] == 1)
                    {
                        wF[k][j] = 0;
                        break;
                    }
                }
            }

            time += c[numM];
            produceRate = 100;
        }

        //計算所需的生產時間 
        while (quant > 0)
        {
            count++;
            quant -= produceRate * a[numM] * 0.01;

            if (produceRate - b[numM] > L[numM])
                produceRate -= b[numM];
            else
                produceRate = L[numM];
        }

        //更新總生產時間
        time += count;
    }

};