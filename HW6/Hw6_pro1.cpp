#include <iostream>

using namespace std;

int main()
{
	int nNum = 0, edgeNum = 0, start = 0, end = 0, checkNum = 0, point = 0, result = 0;
	cin >> nNum >> edgeNum;

	int** nArray = new int* [nNum]();
	for (int i = 0; i < nNum; i++)
		nArray[i] = new int[nNum]();

	int** multi = new int* [nNum]();
	for (int i = 0; i < nNum; i++)
		multi[i] = new int[nNum]();

	int** temp = new int* [nNum]();
	for (int i = 0; i < nNum; i++)
		temp[i] = new int[nNum]();

	for (int i = 0; i < edgeNum; i++)
	{
		cin >> start >> end;
		nArray[start - 1][end - 1] = 1;
	}

	//    for (int i  = 0; i < nNum; i++)
	//	{
	//	    for (int j  = 0; j < nNum; j++)
	//		{
	//		if (j == (nNum-1))
	//			cout << nArray[i][j] << '\n';
	//		else
	//			cout << nArray[i][j] << ',';
	//		}
	//	}

		//checkArray with points that can be a cycle, length checkNum
	cin >> checkNum;
	int* checkArray = new int[checkNum]();

	for (int i = 0; i < checkNum; i++)
	{
		cin >> point;
		checkArray[i] = point;
		//cout << checkArray[i] <<',';
	}


	//take out all the number not in check array to non-check array
	int* boolArray = new int[nNum]();//{0,0,0,0,0}
	int* noncheckArray = new int[nNum - checkNum]();//{0,0}

	for (int i = 0; i < checkNum; i++)//checkArray = {1,2,4}
	{
		boolArray[checkArray[i] - 1] = 1;//{1,1,0,1,0}
	}

	int count = 0;
	for (int i = 0; i < nNum; i++)
	{
		if (boolArray[i] == 0)
		{
			noncheckArray[count] = i + 1;
			count += 1;
		}
		//non-checkarray = {3,5}
	}

	//	for (int i  = 0; i < (nNum-checkNum); i++)
	//	{
	//		cout << noncheckArray[i] <<',';
	//	}

		//change all the row and column of the non-check array to 0
	for (int i = 0; i < (nNum - checkNum); i++)
	{
		int deleteIndex = noncheckArray[i] - 1;
		for (int j = 0; j < nNum; j++)
		{
			nArray[j][deleteIndex] = 0;
			nArray[deleteIndex][j] = 0;
		}
	}

	//	for (int i  = 0; i < nNum; i++)
	//	{
	//	    for (int j  = 0; j < nNum; j++)
	//		{
	//		if (j == (nNum-1))
	//			cout << nArray[i][j] << '\n';
	//		else
	//			cout << nArray[i][j] << ',';
	//		}
	//	}

		//multi arrays
	for (int i = 0; i < nNum; i++)
	{
		for (int j = 0; j < nNum; j++)
		{
			multi[i][j] = nArray[i][j];
		}
	}

	//normal array * normal arrays for checkNum times
	for (int i = 0; i < (checkNum + 1); i++)
	{
		//temp = multi*narray
		for (int j = 0; j < nNum; j++)
			for (int t = 0; t < nNum; t++)
				for (int k = 0; k < nNum; k++)
					temp[j][t] += multi[j][k] * nArray[k][t];

		for (int j = 0; j < nNum; j++)
		{
			for (int t = 0; t < nNum; t++)
			{
				multi[j][t] = temp[j][t];
				temp[j][t] = 0;
			}

			if (multi[j][j] != 0)
			{
				result = 1;
			}
		}


		//		for (int t  = 0; t < nNum; t++)
		//		{
		//		    for (int j  = 0; j < nNum; j++)
		//			{
		//			if (j == (nNum-1))
		//				cout << multi[t][j] << '\n';
		//			else
		//				cout << multi[t][j] << ',';
		//			}
		//		}		
	}
	//check all index on [1][1], [2][2]... are 0 or not
//	for (int i = 0; i < nNum; i++)
//	{
//     	if (multi[i][i] == 1)
//	    {
//        	result = 1;
//        }
//	}
	cout << result;


	return 0;
}



/*
4 5
1 2
2 3
3 1
3 4
4 2
3
1 2 3

5 6
1 2
2 3
3 1
3 4
4 2
5 1
3
1 2 4

5 9
1 2
1 3
1 5
2 3
3 4
4 1
4 2
5 2
5 3
4
1 2 3 4


int a[2][3] = {1, 1, 1, 2, 2, 2};
int b[3][4] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
int c[2][4] = {0};
for(int i = 0; i < 2; i++)
	for(int j = 0; j < 4; j++)
		for(int k = 0; k < 3; k++)
			c[i][j] += a[i][k] * b[k][j];

*/

//checkNum log2 + round
//https://www.geeksforgeeks.org/log2-function-in-c-with-examples/
//https://www.programiz.com/cpp-programming/library-function/cmath/ceil
