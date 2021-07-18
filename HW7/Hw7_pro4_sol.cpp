#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

//match an airport's name to a corresponding index in airport array
int nameToInt(int n, char name[], char** airport)
{
	int nameInt = 0;
	for (int i = 0; i < n; i++)
	{
		//cout <<  name;
		if (name[0] == airport[i][0] and name[1] == airport[i][1] and name[2] == airport[i][2])
			nameInt = i + 1;
	}
	return nameInt;
}

void swapPtr(char*& p1, char*& p2)
{
	char* temp = p1;
	p1 = p2;
	p2 = temp;
}

int main()
{
	int n = 0, m = 0, bsum = 0, csum = 0, airlineN = 0, profit = 0, builtN = 0;
	cin >> n >> m;

	char** airport = new char* [n];
	for (int i = 0; i < n; i++)
	{
		airport[i] = new char[4];
		cin >> airport[i];
	}


	int* cost = new int[n + 1]();
	for (int i = 1; i < n + 1; i++)
	{
		cin >> cost[i];
	}

	//to save two airport indice and their benefits				
	int** airlineArray = new int* [m];
	for (int i = 0; i < m; i++)
		airlineArray[i] = new int[3]();

	int* allCostBft = new int[n + 1]();//for each airport, add up all cost and benefit
	int* boolBuilt = new int[n + 1](); //for each airport, store 1 or 0 (built or not) 

	char eachLine[50];
	cin.ignore();
	for (int i = 0; i < m; i++)
	{
		cin.getline(eachLine, 50);
		//cout << eachLine << '!';

		int seperation = 0, cnt1 = 0, cnt2 = 0, cnt3 = 0, benefit = 0;
		char firstName[3] = { 0 }, secondName[3] = { 0 };

		//a temporary type-char container to save the benefits
		char* container = new char[strlen(eachLine) - 11]();

		//read a character by a character
		for (int j = 0; j < strlen(eachLine); j++)
		{
			if (eachLine[j] == ' ')
				continue;
			if (eachLine[j] == '\"')
			{
				seperation++;
				continue;
			}
			else if (seperation == 1)
			{
				eachLine[j] = static_cast< char >(toupper(eachLine[j]));//to upper class
				firstName[cnt1] = eachLine[j];//store the first airport
				cnt1++;
			}
			else if (seperation == 3)
			{
				eachLine[j] = static_cast< char >(toupper(eachLine[j]));
				secondName[cnt2] = eachLine[j];
				cnt2++;
			}
			else if (seperation == 4)
			{
				container[cnt3] = eachLine[j];
				cnt3++;
			}

			if (j == (strlen(eachLine) - 1))
			{
				//cout << '!';//
				benefit = atoi(container);

			}
		}

		if (benefit <= 0)
			continue;

		int first = nameToInt(n, firstName, airport);
		int second = nameToInt(n, secondName, airport);

		airlineArray[airlineN][0] = first;
		airlineArray[airlineN][1] = second;
		airlineArray[airlineN][2] = benefit;

		//counting how many effective airline
		airlineN++;

		//add up benefits for each airport
		allCostBft[first] += benefit;
		allCostBft[second] += benefit;

		bsum += benefit;

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

		//delete corresponding airports (the airport that has correction with the removed airport)
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

	//result: pointers
	char* result[builtN] = { 0 };
	int resultcnt = 0;
	for (int i = 0; i < builtN; i++)
	{
		if (indexBuilt[i] != -1)
		{
			result[resultcnt] = airport[indexBuilt[i] - 1];
			resultcnt++;
		}
	}

	//bubble sort
	//sortResult: pointers
	char* sortResult[resultcnt] = { 0 };
	for (int i = 0; i < resultcnt; i++)
	{
		sortResult[i] = result[i];
	}

	for (int i = 0; i < resultcnt; i++)
		for (int j = 0; j < resultcnt - i - 1; j++)
			if (strcmp(sortResult[j], sortResult[j + 1]) > 0)
				swapPtr(sortResult[j], sortResult[j + 1]);


	for (int i = 0; i < resultcnt; i++)
	{
		if (i == (resultcnt - 1))
			cout << sortResult[i] << ';' << profit;
		else
			cout << sortResult[i] << ',';
	}
	return 0;
}

/*
3 2
TPE SFO LAX
5 15 30
"TPE" "SF o" 20
"t p e" "l a x" 25

3 3
TPE SFO LAX
5 10 15
"TPE" "SFO" 20
"TPE" "La X" 20
"s f o" "LAX" 5
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
