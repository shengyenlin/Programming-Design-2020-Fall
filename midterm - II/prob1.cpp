#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

using namespace std;
int main()
{

    int num = 0;
    cin >> num;
    int valueArray[100] = { 0 };

    for (int i = 1; i <= num; i++)
    {
        int value = 0;
        cin >> value;
        valueArray[i] = value;
    }

    int maxlength = 1;

    //如果每一個數字都大於前一個則不用交換
    bool complete = true;
    for (int i = 1; i < num; i++)
    {
        if (valueArray[i] > valueArray[i + 1])
        {
            complete = false;
        }
    }

    if (complete == true)
        maxlength = num;

    //如果有數字小於前面的數字則交換
    //交換方法:窮舉
    else
    {

        for (int i = 1; i < num;i++)
        {
            for (int j = i; j < num; j++)
            {
                //每次都重新讀陣列進來
                int compareArray[100] = { 0 };
                for (int k = 1; k <= num; k++)
                {
                    compareArray[k] = valueArray[k];
                }

                //交換
                int temp = compareArray[i];
                compareArray[i] = compareArray[j + 1];
                compareArray[j + 1] = temp;


                for (int k = 1; k <= num; k++)
                {
                    cout << compareArray[k];
                }

                cout << " ";

                //計算最長遞增數列的長度
                int length = 1;
                for (int k = 1; k < num; k++)
                {
                    if (compareArray[k] < compareArray[k + 1])
                    {
                        length++;
                    }

                    else
                    {
                        length = 1;
                    }

                    if (length > maxlength)
                    {
                        maxlength = length;
                    }

                }
                cout << maxlength << " ";
            }
            cout << "\n";
        }
    }
    cout << maxlength;
    return 0;
}