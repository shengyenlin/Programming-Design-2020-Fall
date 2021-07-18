#include <iostream>
using namespace std;

int main()
{
	int n = 0, m = 0, bsum = 0, csum = 0, airlineN = 0, profit = 0, builtN = 0;
	cin >> n >> m;

	int* cost = new int[n + 1]();
	int* allCostBft = new int[n + 1]();//for each airport, add up all cost and benefit
	int* boolBuilt = new int[n + 1](); //for each airport, store 1 or 0 (built or not) 

	for (int i = 1; i < n + 1; i++)
	{
		cin >> cost[i];
	}

	//to save two airport indice and their benefits				
	int** airlineArray = new int* [m];
	for (int i = 0; i < m; i++)
		airlineArray[i] = new int[3]();

	for (int i = 0; i < m; i++)
	{
		int first = 0, second = 0, b = 0;
		cin >> first >> second >> b;
		if (b <= 0)
			continue;

		airlineArray[airlineN][0] = first;
		airlineArray[airlineN][1] = second;
		airlineArray[airlineN][2] = b;

		//counting how many effective airline
		airlineN++;

		//add up benefits for each airport
		allCostBft[first] += b;
		allCostBft[second] += b;

		bsum += b;

		//the airports are built
		boolBuilt[first] = 1;
		boolBuilt[second] = 1;
	}

	//to count how many airports are built
	for (int i = 1; i < n + 1; i++)
		if (boolBuilt[i] == 1)
			builtN++;

	//finish initialization
	for (int i = 1; i < n + 1; i++)
	{
		allCostBft[i] -= cost[i] * boolBuilt[i];
		csum += cost[i] * boolBuilt[i];
	}

	//caculate initial profit
	profit = bsum - csum;

	//cout << csum << ',' << bsum << ',' << profit;

	//storing indice of airports built
	int* indexBuilt = new int[builtN]();
	int count = 0;
	for (int i = 1; i < n + 1; i++)
		if (boolBuilt[i] == 1)
		{
			indexBuilt[count] = i;
			count++;
		}

	//we have built builtN airports, and we eliminate one by one to maximize profit
	//the worst case is that we eliminate all the airports
	for (int i = 0; i < builtN; i++)
	{
		int maxLoss = 0, rev = 0, save = 0; //rev: the index of the airport to be removed

		//run each current built airports to find the airport brings biggest loss and eliminate that airport		
		for (int j = 0; j < builtN; j++)
		{
			int airport = indexBuilt[j];
			//the airport is cuttently built
			//the airport brings net loss and losses more money than current recorded max loss
			if (airport != -1 and maxLoss > allCostBft[airport])
			{
				maxLoss = allCostBft[airport];
				rev = airport;
				save = j;
			}
		}

		//if no airport brings net loss, profit can not be improved
		//jump out the loop
		if (maxLoss == 0)
			break;
		//otherwise, remove the airport and corry on
		profit -= maxLoss;
		indexBuilt[save] = -1;
		allCostBft[rev] = 0;

		//delete corresponding airports(the airport that has correction with the removed airport)
		for (int i = 0; i < m; i++)
		{
			int neighbor = 0;
			//when there are not effective airline to check
			if (airlineArray[i][2] == 0)
				break;

			if (airlineArray[i][0] != rev and airlineArray[i][1] != rev)
				continue;
			else if (airlineArray[i][0] == rev)
			{
				neighbor = airlineArray[i][1];
				allCostBft[neighbor] -= airlineArray[i][2];
			}
			else if (airlineArray[i][1] == rev)
			{
				neighbor = airlineArray[i][0];
				allCostBft[neighbor] -= airlineArray[i][2];
			}
		}
	}

	//result
	int* result = new int[builtN]();
	int resultcnt = 0;
	for (int i = 0; i < builtN; i++)
	{
		if (indexBuilt[i] != -1)
		{
			result[resultcnt] = indexBuilt[i];
			resultcnt++;
		}
	}
	for (int i = 0; i < resultcnt; i++)
	{
		if (i == (resultcnt - 1))
			cout << result[i] << ';' << profit;
		else
			cout << result[i] << ',';
	}
}

/*
5 6
5 10 15 20 10
1 3 20
1 4 0
2 3 12
3 5 3
2 1 0
3 4 0

3 2
5 15 30
1 2 20
1 3 25
*/

/*	//print out to test if we correctly read in data
	//cost
	for (int i  = 0; i < n+1; i++)
	{
		if (i == n)
			cout << cost[i] << '\n';
		else
			cout << cost[i] << ' ';
	}
	//allCostBft
	for (int i  = 0; i < n+1; i++)
	{
		if (i == n)
			cout << allCostBft[i] << '\n';
		else
			cout << allCostBft[i] << ' ';
	}
	//boolBuilt
	for (int i  = 0; i < n+1; i++)
	{
		if (i == n)
			cout << boolBuilt[i] << '\n';
		else
			cout << boolBuilt[i] << ' ';
	}
	//airlineArray
	for (int i  = 0; i < m; i++)
	{
		if (i == n)
			cout << airlineArray[i][0] <<  airlineArray[i][1] <<  airlineArray[i][2] << '\n';
		else
			cout << airlineArray[i][0] <<  airlineArray[i][1] <<  airlineArray[i][2] << ' ';
	}
	//indexBuilt
	for (int i  = 0; i < builtN; i++)
	{
		if (i == n)
			cout << indexBuilt[i] << '\n';
		else
			cout << indexBuilt[i] << ' ';
	}
*/
