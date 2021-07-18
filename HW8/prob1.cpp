#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX_LEN_CARDS = 100;

struct Card
{
    char suit;
    int rank;
    bool isA();
    bool init(char cardStr[]);
    void print();
};
//check is A or not
bool Card::isA()
{
    if (rank == 1)
        return true;
    else
        return false;
}
//initialization
bool Card::init(char cardStr[])
{
    int len = strlen(cardStr);
    for (int i = 0; i < len; i++)
    {
        if (isalnum(cardStr[i] == 0))
            return false;
    }
    suit = cardStr[0];
    //num = 10
    if (len == 3)
    {
        rank = atoi(&cardStr[1]);
    }

    else if (isalpha(cardStr[1]) != 0)
    {
        if (cardStr[1] == 'J')
            rank = 11;
        if (cardStr[1] == 'Q')
            rank = 12;
        if (cardStr[1] == 'K')
            rank = 13;
        if (cardStr[1] == 'A')
            rank = 1;
    }

    else
    {
        rank = atoi(&cardStr[1]);
    }
    return true;
}

void Card::print()
{
    cout << suit << rank << " ";
}

int main()
{
    char cards[100] = { 0 };
    cin.getline(cards, MAX_LEN_CARDS);
    //切割每張牌

    char* p1 = &cards[0];
    char* p2 = strchr(cards, ',');
    char* end = strchr(cards, '\0');
    Card cardsArray[6] = { 0 };

    int position = 0;
    for (int i = 1; i <= 5; i++)
    {
        char card[10] = { 0 };
        bool stop = false;
        if (p2 == nullptr)
        {
            for (int j = 0; j < end - p1; j++)
            {
                card[j] = cards[position];
                position += 1;
                stop = true;
            }
        }
        else
        {
            for (int j = 0; j < p2 - p1; j++)
            {
                card[j] = cards[position];
                position += 1;
            }
        }

        Card cardTemp;
        cardTemp.init(card);
        cardsArray[i] = cardTemp;
        //cardsArray[i].print();

        if (stop == true)
            break;
        p1 = p2 + 1;
        p2 = strchr(p1, ',');
        position += 1;

    }

    //bubble sort :先按照花色再依照數字sort小到大
    for (int i = 4; i >= 1; i--)
    {

        for (int j = 1; j <= i; j++)
        {
            if (cardsArray[j].rank > cardsArray[j + 1].rank)
            {
                //cout << cardsArray[j].suit << " " << cardsArray[j + 1].suit << "\n";
                int tempRank = cardsArray[j].rank;
                cardsArray[j].rank = cardsArray[j + 1].rank;
                cardsArray[j + 1].rank = tempRank;

                char tempSuit = cardsArray[j].suit;
                cardsArray[j].suit = cardsArray[j + 1].suit;
                cardsArray[j].suit = tempSuit;
            }

            /*
            else if (cardsArray[j].rank > cardsArray[j + 1].rank && cardsArray[j].suit == cardsArray[j + 1].suit)
            {
                int tempRank = cardsArray[j].rank;
                cardsArray[j].rank = cardsArray[j + 1].rank;
                cardsArray[j + 1].rank = tempRank;

                char tempSuit = cardsArray[j].suit;
                cardsArray[j].suit = cardsArray[j + 1].suit;
                cardsArray[j].suit = tempSuit;
            }
            */
        }
    }

    /*
    for (int i = 1; i <= 5; i++)
    {
        cout << cardsArray[i].suit << " " << cardsArray[i].rank << "\n";
    }
    */
    int countSuit[5] = { 0 };
    //C, D, H, S
    //1, 2, 3, 4
    int seen[6] = { 0 };
    for (int i = 1; i <= 5; i++)
    {
        if (seen[i] == 0)
        {
            if (cardsArray[i].suit == 'C')
                countSuit[1] += 1;
            else if (cardsArray[i].suit == 'D')
                countSuit[2] += 1;
            else if (cardsArray[i].suit == 'H')
                countSuit[3] += 1;
            else if (cardsArray[i].suit == 'S')
                countSuit[4] += 1;

            for (int j = 1; j <= 5 - i; j++)
            {
                if (cardsArray[i].suit == cardsArray[i + j].suit)
                {
                    seen[i + j] = 1;
                    if (cardsArray[i].suit == 'C')
                        countSuit[1] += 1;
                    else if (cardsArray[i].suit == 'D')
                        countSuit[2] += 1;
                    else if (cardsArray[i].suit == 'H')
                        countSuit[3] += 1;
                    else if (cardsArray[i].suit == 'S')
                        countSuit[4] += 1;
                }
            }
        }
    }

    /*
    for (int i = 1; i <= 4; i++)
    {
        cout << countSuit[i] << " ";
    }
    */

    //check 同花順->順->葫蘆->同花->一對->A
    //同花順
    //唯一跨越的只有10 11 12 13 1

    //check有沒有同花
    bool allSameColor = false;
    for (int i = 1; i <= 4; i++)
    {
        if (countSuit[i] == 5)
            allSameColor = true;
    }

    //check有沒有順子
    bool flush = false;
    int count = 0;
    for (int i = 1; i <= 4; i++)
    {
        if ((cardsArray[i].rank + 1) == cardsArray[i + 1].rank)
            count += 1;
    }

    if (count == 4)
    {
        flush = true;
    }

    else if (cardsArray[1].rank == 1 && cardsArray[2].rank == 10 && cardsArray[3].rank == 11 && cardsArray[4].rank == 12 && cardsArray[5].rank == 13)
    {
        flush = true;
    }

    //check有沒有兩個一樣和三個一樣的數字
    int two = 0;
    int three = 0;
    bool gourd = false;
    //紀錄算過的位置
    int delArray[6] = { 0 };
    int countA = 0;
    for (int i = 1; i <= 5; i++)
    {
        int countSame = 0;
        if (cardsArray[i].rank == 1)
            countA += 1;
        if (delArray[i] == 0)
        {
            for (int j = 1; j <= 5 - i; j++)
            {
                if (cardsArray[i].rank == cardsArray[i + j].rank)
                {
                    countSame += 1;
                    delArray[i] = 1;
                    delArray[i + j] = 1;
                }
            }
        }
        if (countSame == 1)
            two += 1;
        else if (countSame == 2)
            three += 1;
        else if (countSame == 3)
            two += 2;
    }


    if (two == 1 && three == 1)
    {
        gourd = true;
    }

    //output
    if (allSameColor == true)
    {
        //同花順:100
        if (flush == true)
        {
            cout << 100;
        }

        //同花:20
        else
        {
            cout << 20;
        }
    }
    //順:50
    else if (flush == true)
    {
        cout << 50;
    }

    //葫蘆
    else if (gourd == true)
    {
        cout << 40;
    }

    //一對、A要同時處理，算出得到的最高分數
    else
    {
        int score = 0;
        //有幾對
        if (two == 1 || three == 1)
            score += 5;
        //3個A，兩個不同數字
        if (three == 1 && countA == 3)
            score += 1;
        else if (two == 2)
            score += 10;

        for (int i = 1; i <= 5;i++)
        {
            if (delArray[i] == 0)
            {
                if (cardsArray[i].isA() == true)
                    score += 1;
            }
        }
        cout << score;
    }

    return 0;
}

/*
SA,D2,C3,H4,S5
50

SK,HK,DK,S4,H4
40

DJ,DQ,DK,DA,D2
20
*/

/*
2 : 6
3 : 11
10 : 5
14 : 11

SA,HA,DA,SA,H6
SA,H3,D3,S3,H3
SA,HA,D7,S5,H5
SA,HA,D8,S6,H5
*/