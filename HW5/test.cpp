#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int x = 50;
    int y = 100;
    cout << " min = " << min<int>(x, y) << endl;
    cout << " max = " << max<int>(x, y) << endl;
    return 0;
}
