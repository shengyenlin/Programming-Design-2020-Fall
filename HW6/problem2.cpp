#include <iostream>
using namespace std;
int main()
{

    int productivity = 0, repairLen = 0, totalTime = 0;
    int decreaseRate = 0, Rate0 = 0, lbRate = 0;
    cin >> productivity >> decreaseRate >> repairLen >> Rate0 >> totalTime >> lbRate;

    int maxProduct = 0, maxTime = 0;
    //迭代所有可能的維修時間
    for (int j = 0; j <= totalTime; j++)
    {
        int stoptime = j, totalProduct = 0;
        if (stoptime == 0)
        {
            for (int i = 1; i <= totalTime; i++)
            {
                int currentRate = Rate0 - i * decreaseRate;
                if (currentRate <= lbRate)
                {
                    currentRate = lbRate;
                }
                int product = productivity / 100 * currentRate;
                totalProduct += product;
            }
        }

        else
        {
            //summation total product before repair
            for (int i = 1; i < stoptime; i++)
            {
                int currentRate = Rate0 - i * decreaseRate;
                if (currentRate <= lbRate)
                {
                    currentRate = lbRate;
                }
                int product = productivity / 100 * currentRate;
                totalProduct += product;
            }
            //summation total product after repair
            for (int k = 0; k < totalTime - (stoptime + repairLen) + 1; k++)
            {

                int currentRate = 100 - k * decreaseRate;
                if (currentRate <= lbRate)
                {
                    currentRate = lbRate;
                }
                int product = productivity / 100 * currentRate;
                totalProduct += product;
            }
        }

        if (totalProduct > maxProduct)
        {
            maxProduct = totalProduct;
            maxTime = j;
        }

        //如果兩個時段維修都可以有最大產量，則印出較早的時間
        else if ((totalProduct == maxProduct) && (j < maxTime))
        {
            maxProduct = totalProduct;
            maxTime = j;
        }
    }

    cout << maxTime << "," << maxProduct;
    return 0;
}