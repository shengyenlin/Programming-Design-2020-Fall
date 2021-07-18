#include <iostream>
#include <cstdlib>
using namespace std;

void orderSwitch(int j, int* number);
void orderDistribute(int numO, int m, int* a, int* b, int* L, int* oQ, int* oT, int* oN, int** mO, int* mOA, int* mPR, int* mA, int* mDT);
void machineRepairSwitch(int n1, int n2, int* mR);
void determineRepair_1(int numM, int numW, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* mDT, int** wF, int** rL);
void determineRepair_2(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* mDT, int** wF, int** rL);
void workerFreeUpdate_1(int numM, int numW, int* a, int* b, int* c, int* p, int* L, int* oQ, int** mO, int* mOA, int** wF, int** rL);
void workerFreeUpdate_2(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int** mO, int* mOA, int** wF, int** rL);

int reCalculate(int numM, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* rIA);
int tryRepair_Delay(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int** wF, int* rIA);
int freeWorker(int numM, int h, int time, int* c, int** wF);



int main() {

	//INPUT嚙畿嚙緲 
	int m = 0, n = 0, h = 0;
	cin >> m >> n >> h;

	int* a = new int[m + 1];
	int* b = new int[m + 1];
	int* c = new int[m + 1];
	int* p = new int[m + 1];
	int* L = new int[m + 1];

	for (int i = 1;i <= m;i++)
		cin >> a[i] >> b[i] >> c[i] >> p[i] >> L[i];

	int* orderQuant = new int[n + 1];
	int* orderTime = new int[n + 1];

	for (int i = 1;i <= n;i++)
		cin >> orderQuant[i] >> orderTime[i];


	/////////////////////////////Order Sorting/////////////////////////////

	//Condition : 1.嚙碾嚙誰剁蕭嚙踝蕭V嚙箴嚙踝蕭 2.嚙緬嚙踝蕭q嚙碾嚙篌嚙碾嚙箴嚙踝蕭 (bubble sorting method)

	int* orderNumber = new int[n + 1];			//record the serial number of each order 
	for (int i = 1;i <= n;i++)
		orderNumber[i] = i;

	for (int i = 1;i < n;i++)
	{
		for (int j = 1;j < n;j++)
		{
			int n1 = orderNumber[j], n2 = orderNumber[j + 1];

			if (orderTime[n1] > orderTime[n2])
				orderSwitch(j, orderNumber);

			else if (orderTime[n1] == orderTime[n2] && orderQuant[n1] < orderQuant[n2])
				orderSwitch(j, orderNumber);
		}
	}


	/////////////////////////////Order Distribution/////////////////////////////

	//Goal : 嚙諒照訂嚙賣順嚙褒歹蕭嚙緣嚙練嚙碼嚙璀嚙踝蕭嚙踝蕭嚙綞 
	//Condition : 1.嚙諒小嚙複抬蕭嚙踝蕭伅嚙�/嚙褕佗蕭嚙踝蕭嚙踝蕭嚙緬嚙踝蕭 2.嚙踝蕭亄嚙踝蕭嚙諒低嚙踝蕭嚙踝蕭嚙綞(嚙褕塚蕭嚙瑾嚙誼迎蕭嚙踝蕭嚙緘) 

	int** machineOrder = new int* [m + 1];			//machineOrder[i] : orders which are ditributed to the ith machine
	for (int i = 1;i <= m;i++)
		machineOrder[i] = new int[n + 1];

	int* machineOrderAmount = new int[m + 1];		//machineOrderAmount[i]	: the amount of orders for the ith machine
	for (int i = 1;i <= m;i++)
		machineOrderAmount[i] = 0;

	int* machineProductionRate = new int[m + 1];		//Production Rate when the last order complete
	int* machineAvailable = new int[m + 1];		//Time Point   when the machine complete the last order
	int* machineDelayTotal = new int[m + 1];

	//嚙踝蕭l嚙踝蕭 machineProductionRate,  machineAvailable, machineDelayTotal
	for (int i = 1;i <= m;i++)
	{
		machineProductionRate[i] = p[i] - b[i];
		if (machineProductionRate[i] < L[i])
			machineProductionRate[i] = L[i];

		machineAvailable[i] = 0;
		machineDelayTotal[i] = 0;
	}

	for (int i = 1;i <= n;i++)
	{
		orderDistribute(orderNumber[i], m, a, b, L, orderQuant, orderTime, orderNumber,
			machineOrder, machineOrderAmount, machineProductionRate, machineAvailable, machineDelayTotal);
	}


	/////////////////////////////Repair Decision/////////////////////////////

	//Goal : 嚙踝蕭嚙緣嚙踝蕭嚙論人嚙踝蕭嚙趣不嚙瞑嚙踝蕭嚙踝蕭嚙綞
	//Condition : 1. 嚙窯嚙踝蕭嚙踝蕭伅嚙踝蕭怞h嚙踝蕭嚙踝蕭嚙綞 2. 嚙緬嚙踝蕭q嚙諒大嚙踝蕭嚙踝蕭嚙綞 3. 嚙瘠嚙緘嚙褕莎蕭嚙緬(a)嚙諒大嚙踝蕭嚙踝蕭嚙綞

	//嚙緩嚙複橘蕭嚙綞嚙踝蕭嚙踝蕭嚙論塚蕭嚙踝蕭
	int* machineRepair = new int[m + 1];				//the serial number of machine to be repaired 
	for (int i = 1;i <= m;i++)
		machineRepair[i] = i;
	for (int i = 1;i < m;i++)
	{
		for (int j = 1;j <= (m - i);j++)
		{
			if (machineDelayTotal[j] < machineDelayTotal[j + 1])
				machineRepairSwitch(j, j + 1, machineRepair);

			else if (machineDelayTotal[j] == machineDelayTotal[j + 1])
			{
				int sum1 = 0, sum2 = 0;
				for (int k = 1;k <= machineOrderAmount[j];k++)
					sum1 += orderQuant[machineOrder[j][k]];

				for (int k = 1;k <= machineOrderAmount[j + 1];k++)
					sum2 += orderQuant[machineOrder[j + 1][k]];

				if (sum1 < sum2)
					machineRepairSwitch(j, j + 1, machineRepair);

				else if (sum1 == sum2 && a[j] < a[j + 1])
					machineRepairSwitch(j, j + 1, machineRepair);
			}
		}

	}

	//嚙瞋嚙踝蕭 maxProductionTime 嚙瞑嚙稻 workerFree 嚙課需配嚙練嚙踝蕭嚙褊態嚙瞌嚙踝蕭嚙踝蕭j嚙緘 
	int maxProductionTime = 0;
	for (int i = 1;i <= m;i++)
	{
		if (maxProductionTime < machineAvailable[i])
			maxProductionTime = machineAvailable[i];
	}
	int** workerFree = new int* [h + 1];
	for (int i = 1;i <= h;i++)
	{
		//嚙論免嚙瞌嚙踝蕭嚙踝蕭韃嚙踝蕭嚙踝蕭嚙� 嚙瘦嚙緣嚙練 maxProductionTime + 10000 嚙踝蕭嚙褐塚蕭 
		workerFree[i] = new int[maxProductionTime + 10001];
		for (int j = 1;j <= maxProductionTime + 10000;j++)
			workerFree[i][j] = 1;
	}

	//嚙踝蕭嚙緣嚙踝蕭嚙論人嚙踝蕭
	int** repairList = new int* [m + 1];				//repairList[i][j] = 1 
													//if needed to be "REPAIR" before the jth order produced by the ith machine  
	for (int i = 1;i <= m;i++)
	{
		repairList[i] = new int[machineOrderAmount[i] + 1];
		for (int j = 1;j <= machineOrderAmount[i];j++)
			repairList[i][j] = 0;
	}

	for (int i = 1;i <= m;i++)
	{
		if (i <= h && machineDelayTotal[machineRepair[i]] > 0)
		{
			determineRepair_1(machineRepair[i], i, a, b, c, p, L, orderQuant, orderTime,
				machineOrder, machineOrderAmount, machineDelayTotal, workerFree, repairList);
		}

		else if (machineDelayTotal[machineRepair[i]] > 0)
		{
			determineRepair_2(machineRepair[i], h, a, b, c, p, L, orderQuant, orderTime,
				machineOrder, machineOrderAmount, machineDelayTotal, workerFree, repairList);
		}
	}


	/////////////////////////////Print Out Result///////////////////////////// 
	for (int i = 1;i <= m;i++)
	{
		if (machineOrderAmount[i] == 0)
			cout << 0;

		else
		{
			for (int j = 1;j <= machineOrderAmount[i];j++)
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
/*--	##########	  ##      ## 	 ##		   ##	 ##########   ##########	######		##########	  ##	    ##	--*/
/*--	##		  	  ##      ##	 ####	   ##	 ##		  	   	  ##		  ##		##		##	  ####	    ##	--*/
/*--    ##			  ##      ##	 ##	 ##	   ##	 ##		  		  ##		  ##		##		##	  ##  ##    ##	--*/
/*--    #########	  ##      ##	 ##	   ##  ##	 ##		  		  ##		  ##		##		##	  ##	##  ##	--*/
/*--    ##			  ##      ##	 ##		 ####	 ##		  		  ##		  ##		##		##	  ##	  ####	--*/
/*--    ##			  ##########	 ##		   ##	 ##########		  ##	   ########		##########	  ##		##	--*/
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
	/*numO					: the index of order after sorting, which is being distributed									*/
	/*oQ, oT,  oN			: orderQuant, orderTime, orderNumber															*/
	/*mO, mOA, mPR, mA, mDT	: machineOrder, machineOrderAmount, machineProductionRate, machineAvailable, machineDelayTotal	*/
	int* machineMightDelay = new int[m + 1];
	int* machineFinalPR = new int[m + 1];


	/////////////////////////////Calculation/////////////////////////////

	//嚙緘嚙踝蕭嚙踝蕭@嚙踝蕭嚙踝蕭嚙談莎蕭嚙踝蕭numO嚙踝蕭嚙緬嚙踝蕭 : "嚙踝蕭嚙踝蕭伅嚙�", "嚙緬嚙賣完嚙踝蕭嚙褕迎蕭嚙踝蕭嚙踝蕭" 
	for (int i = 1;i <= m;i++)
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

		machineMightDelay[i] = mA[i] + count - oT[numO];	//val = integer (might be negative or 0) 
		machineFinalPR[i] = produceRate;
	}


	/////////////////////////////Compare/////////////////////////////

	//嚙衝荔蕭嚙踝蕭嚙踝蕭嚙� :  a[i] * machineFinalPR[i]
	int minDelay = machineMightDelay[1], machineNumber = 1, production = a[1] * machineFinalPR[1];
	for (int i = 1;i <= m;i++)
	{
		if (minDelay > machineMightDelay[i])
		{
			minDelay = machineMightDelay[i];
			production = a[i] * machineFinalPR[i];
			machineNumber = i;
		}
		else if (minDelay == machineMightDelay[i] && production > a[i] * machineFinalPR[i])
		{
			minDelay = machineMightDelay[i];
			production = a[i] * machineFinalPR[i];
			machineNumber = i;
		}

	}

	/////////////////////////////Save Results/////////////////////////////

	mPR[machineNumber] = machineFinalPR[machineNumber];
	mA[machineNumber] = machineMightDelay[machineNumber] + oT[numO];
	//嚙踝蕭嚙箴嚙談莎蕭嚙踝蕭嚙踝蕭嚙踝蕭嚙踝蕭嚙緘嚙皚 
	if (minDelay > 0)
		mDT[machineNumber] += minDelay;
	//嚙緬嚙踝蕭s嚙踝蕭嚙編嚙皚mO嚙畿嚙踝蕭s嚙諉橘蕭嚙綞嚙談莎蕭嚙踝蕭嚙緬嚙踝蕭�量(mOA) 
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


void determineRepair_1(int numM, int numW, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* mDT, int** wF, int** rL)
{
	/*numM	: the index of machine 																			*/
	/*numW  : the index of worker who is assigned to repair the selected machine							*/
	int delayAfterRepair = mDT[numM];						//the standard to determine whether to repair the machine or not
	int* repairInAdvance = new int[mOA[numM] + 1];
	for (int i = 1;i <= mOA[numM];i++)
		repairInAdvance[i] = 0;

	for (int i = 1;i <= mOA[numM];i++)
	{
		int upperDelay = delayAfterRepair, repairTimePoint = 0;

		//Condition : 嚙瘠嚙踝蕭嚙箭嚙瑾嚙諉訂嚙踝蕭e嚙踝蕭嚙調綽蕭嚙踝蕭, 嚙踝蕭X嚙踝蕭嚙�"嚙諒新嚙窯嚙踝蕭嚙踝蕭伅嚙�"嚙諒多嚙踝蕭嚙緬嚙踝蕭 
		for (int j = 1;j <= mOA[numM];j++)
		{
			if (repairInAdvance[j] == 0)
			{
				repairInAdvance[j] = 1;
				int delayTemp = reCalculate(numM, a, b, c, p, L, oQ, oT, mO, mOA, repairInAdvance);

				if (delayTemp < upperDelay)
				{
					upperDelay = delayTemp;
					repairTimePoint = j;
				}

				repairInAdvance[j] = 0;
			}
		}

		if (repairTimePoint == 0)
			break;
		else
		{
			repairInAdvance[repairTimePoint] = 1;
			delayAfterRepair = reCalculate(numM, a, b, c, p, L, oQ, oT, mO, mOA, repairInAdvance);
		}

	}

	for (int i = 1;i <= mOA[numM];i++)
		rL[numM][i] = repairInAdvance[i];

	delete[] repairInAdvance;

	//嚙踝蕭sworkerFree
	workerFreeUpdate_1(numM, numW, a, b, c, p, L, oQ, mO, mOA, wF, rL);
};


void determineRepair_2(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* mDT, int** wF, int** rL)
{
	int delayAfterRepair = mDT[numM];						//the standard to determine whether to repair the machine or not
	int* repairInAdvance = new int[mOA[numM] + 1];
	for (int i = 1;i <= mOA[numM];i++)
		repairInAdvance[i] = 0;

	//嚙瘠嚙踝蕭嚙踝蕭X嚙踝蕭嚙誰最多嚙踝蕭嚙踝蕭伅嚙踝蕭嚙踝蕭嚙踝蕭蚺閬�(嚙褓定嚙瘦嚙踝蕭嚙稷嚙磐嚙誼查) 
	for (int i = 1;i <= mOA[numM];i++)
	{
		int upperDelay = delayAfterRepair, repairTimePoint = 0;

		//Condition : 嚙瘠嚙踝蕭嚙箭嚙瑾嚙諉訂嚙踝蕭e嚙踝蕭嚙調綽蕭嚙踝蕭, 嚙踝蕭X嚙踝蕭嚙�"嚙諒新嚙窯嚙踝蕭嚙踝蕭伅嚙�"嚙諒多嚙踝蕭嚙緬嚙踝蕭 
		for (int j = 1;j <= mOA[numM];j++)
		{
			if (repairInAdvance[j] == 0)
			{
				repairInAdvance[j] = 1;

				//嚙瞌嚙稻嚙踝蕭嚙踝蕭嚙練嚙瘡嚙瞌嚙瘡 嚙磐嚙踝蕭嚙稷嚙踝蕭嚙窯嚙踝蕭嚙踝蕭伅嚙踝蕭F嚙誕歹蕭嚙璀嚙稷嚙踝蕭-1
				int delayTemp = tryRepair_Delay(numM, h, a, b, c, p, L, oQ, oT, mO, mOA, wF, repairInAdvance);

				if (delayTemp < upperDelay && delayTemp >= 0)
				{
					upperDelay = delayTemp;
					repairTimePoint = j;
				}

				repairInAdvance[j] = 0;
			}
		}

		if (repairTimePoint == 0)
			break;
		else
		{
			repairInAdvance[repairTimePoint] = 1;
			delayAfterRepair = reCalculate(numM, a, b, c, p, L, oQ, oT, mO, mOA, repairInAdvance);
		}

	}

	for (int i = 1;i <= mOA[numM];i++)
		rL[numM][i] = repairInAdvance[i];

	delete[] repairInAdvance;

	//嚙踝蕭sworkerFree
	workerFreeUpdate_2(numM, h, a, b, c, p, L, oQ, mO, mOA, wF, rL);

};


int reCalculate(int numM, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int* rIA)
{
	int totalDelay = 0, time = 0, produceRate = p[numM] - b[numM];
	if (produceRate < L[numM])
		produceRate = L[numM];

	for (int i = 1;i <= mOA[numM];i++)
	{
		int   numO = mO[numM][i];
		float quant = oQ[numO];
		int   count = 0;

		//嚙誹橘蕭repairInAdvance嚙踝蕭嚙踝蕭�進嚙踝蕭嚙踝蕭嚙�		
		if (rIA[i] == 1)
		{
			time += c[numM];
			produceRate = 100;
		}

		//嚙緘嚙踝蕭珨搌嚙踝蕭芠嚙踝蕭伅嚙� 
		while (quant > 0)
		{
			count++;
			quant -= produceRate * a[numM] * 0.01;

			if (produceRate - b[numM] > L[numM])
				produceRate -= b[numM];
			else
				produceRate = L[numM];
		}

		//嚙踝蕭s嚙窯嚙談莎蕭嚙褕塚蕭&嚙窯嚙踝蕭嚙踝蕭伅嚙� 
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

	for (int i = 1;i <= mOA[numM];i++)
	{
		int   numO = mO[numM][i];
		float quant = oQ[numO];
		int   count = 0;

		//嚙誹橘蕭repairList嚙箠嚙踝蕭嚙踝蕭嚙�		
		if (rL[numM][i] == 1)
		{
			//嚙踝蕭s嚙踝蕭嚙論人嚙踝蕭嚙踝蕭嚙線嚙瑾嚙褕塚蕭 
			for (int j = time + 1;j <= time + c[numM];j++)
				wF[numW][j] = 0;

			time += c[numM];
			produceRate = 100;
		}

		//嚙緘嚙踝蕭珨搌嚙踝蕭芠嚙踝蕭伅嚙� 
		while (quant > 0)
		{
			count++;
			quant -= produceRate * a[numM] * 0.01;

			if (produceRate - b[numM] > L[numM])
				produceRate -= b[numM];
			else
				produceRate = L[numM];
		}

		//嚙踝蕭s嚙窯嚙談莎蕭嚙褕塚蕭
		time += count;
	}

};


int tryRepair_Delay(int numM, int h, int* a, int* b, int* c, int* p, int* L, int* oQ, int* oT, int** mO, int* mOA, int** wF, int* rIA)
{
	int totalDelay = 0, time = 0, produceRate = p[numM] - b[numM];
	if (produceRate < L[numM])
		produceRate = L[numM];

	for (int i = 1;i <= mOA[numM];i++)
	{
		int   numO = mO[numM][i];
		float quant = oQ[numO];
		int   count = 0;

		if (rIA[i] == 1)
		{
			//嚙誼查"嚙諉佗蕭嚙緩嚙踝蕭嚙踝蕭嚙論迎蕭嚙褕塚蕭嚙瘢"嚙瞌嚙稻嚙踝蕭嚙篁嚙締嚙踝蕭嚙瘡嚙瞌嚙箠嚙踝蕭嚙踝蕭嚙�	
			int available = freeWorker(numM, h, time, c, wF);
			if (available == 0)
				return -1;

			time += c[numM];
			produceRate = 100;
		}

		//嚙緘嚙踝蕭珨搌嚙踝蕭芠嚙踝蕭伅嚙� 
		while (quant > 0)
		{
			count++;
			quant -= produceRate * a[numM] * 0.01;

			if (produceRate - b[numM] > L[numM])
				produceRate -= b[numM];
			else
				produceRate = L[numM];
		}

		//嚙踝蕭s嚙窯嚙談莎蕭嚙褕塚蕭
		time += count;
		if (time - oT[numO] > 0)
			totalDelay += time - oT[numO];
	}

	return totalDelay;
};


int freeWorker(int numM, int h, int time, int* c, int** wF)
{
	for (int i = time + 1;i <= time + c[numM];i++)
	{
		int free = 0;
		for (int j = 1;j <= h;j++)
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

	for (int i = 1;i <= mOA[numM];i++)
	{
		int   numO = mO[numM][i];
		float quant = oQ[numO];
		int   count = 0;

		//嚙誹橘蕭repairList嚙箠嚙踝蕭嚙踝蕭嚙�		
		if (rL[numM][i] == 1)
		{
			//嚙踝蕭X嚙踝蕭嚙練嚙踝蕭嚙踝蕭嚙線 
			for (int j = time + 1;j <= time + c[numM];j++)
			{
				for (int k = 1;k <= h;k++)
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

		//嚙緘嚙踝蕭珨搌嚙踝蕭芠嚙踝蕭伅嚙� 
		while (quant > 0)
		{
			count++;
			quant -= produceRate * a[numM] * 0.01;

			if (produceRate - b[numM] > L[numM])
				produceRate -= b[numM];
			else
				produceRate = L[numM];
		}

		//嚙踝蕭s嚙窯嚙談莎蕭嚙褕塚蕭
		time += count;
	}

};
