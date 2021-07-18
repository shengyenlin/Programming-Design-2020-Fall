#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

const int MAX_STRING_LENGTH = 1001;

using namespace std;
int main()
{
    int move = 0;
    cin >> move;
    char word[MAX_STRING_LENGTH] = { 0 };
    cin.ignore();
    cin.getline(word, MAX_STRING_LENGTH);
    for (int i = 0; i < strlen(word); i++)
    {
        //是英文字母的話
        if (isalpha(word[i]) != 0)
        {
            int fin = int(word[i]) + move;
            if (fin > 122)
            {
                word[i] = static_cast< char >(96 + (fin - 122));
            }
            else
            {
                word[i] = static_cast< char >(fin);
            }
        }
        cout << word[i];
    }


    return 0;
}