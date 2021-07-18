#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX_LEN_CARDS = 100;
const int NUM_PLAYER = 5;
const int NUM_TYPE = 5;
const int NUM_CARDS = 6;

struct Randomizer
{
    int a;
    int b;
    int c;
    int cur;
    int rand();
};

struct Card
{
    char suit;
    int rank;
    bool isA();
    bool init(char cardStr[]);
    void print();
};

struct Deck
{
    Card* cards; //指到每一個玩家的cardArray
    int cardCnt;
    int* suitNum; //紀錄四種花色出現幾次
    int* delArray; //已經被算過的卡片
    //member functions
    void addCard(int pos, Card c); //把牌加到每位玩家的第幾個位置
    int getPoint();
    //bubble sort :先按照花色再依照數字sort小到大
    void sortCard();
    //計算每個player每個花色有幾張卡
    void countSuit();
    bool hasStraight();
    bool hasSameColor();
    int* countTwoAndThree();

};

/*
input s, a, b, c
Randomizer r1 = {a, b, c, s}; // this is exactly following the C++ syntax
S, H, D, C
Card cards[] = {"SA", "S2", "S3", ..., "CK"}
for i from 0 to 19:
r = r1.rand() % 52;
swap cards[i] and cards[r]
for i from 0 to 19:
add cards[i] to the deck owned by player (i % 4 + 1)
// further tasks ...

*/

int main()
{
    int s = 0, a = 0, b = 0, c = 0;
    cin >> s >> a >> b >> c;
    Randomizer r1 = { a, b, c, s };
    cin.ignore();
    int r = 0;
    char cardsAllUnit[100] = { 0 };
    int cardsAllNum[100] = { 0 };
    for (int i = 0; i < 52; i++)
    {
        if (i < 13)
            cardsAllUnit[i] = 'S';
        else if (i < 26)
            cardsAllUnit[i] = 'H';
        else if (i < 39)
            cardsAllUnit[i] = 'D';
        else
            cardsAllUnit[i] = 'C';
    }

    for (int i = 0; i < 52; i++)
    {
        if ((i + 1) % 13 != 0)
            cardsAllNum[i] = (i + 1) % 13;
        else
            cardsAllNum[i] = 13;
    }


    for (int i = 0; i < 20; i++)
    {
        r = r1.rand() % 52;
        int tempNum = cardsAllNum[r];
        cardsAllNum[r] = cardsAllNum[i];
        cardsAllNum[i] = tempNum;

        char tempUnit = cardsAllUnit[r];
        cardsAllUnit[r] = cardsAllUnit[i];
        cardsAllUnit[i] = tempUnit;
    }

    Deck* player = new Deck[NUM_PLAYER];
    int* playerScore = new int[NUM_PLAYER];
    for (int i = 1; i <= 4; i++)
    {
        //先做出一個Array之後丟入牌
        player[i] = { nullptr, NUM_CARDS, nullptr, nullptr };
        player[i].cards = new Card[6]();
    }

    int cardPos = 1;
    for (int i = 0; i < 20; i++)
    {
        //現在發給第幾位玩家第幾張牌
        int playerPos = (i % 4) + 1;
        player[playerPos].cards[cardPos] = { cardsAllUnit[i], cardsAllNum[i] };
        if (i % 4 == 3)
            cardPos += 1;
    }
    /*
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            player[i].cards[j].print();
        }

        for (int j = 1; j <= 4; j++)
        {
            cout << player[i].suitNum[j] << " ";
        }

        cout << "\n";
    }
    */

    for (int i = 1; i <= 4; i++)
    {
        //bubble sort :先按照花色再依照數字sort小到大
        player[i].sortCard();
        //計算每個player每個花色有幾張卡
        player[i].countSuit();
        //
        int finalScore = player[i].getPoint();
        playerScore[i] = finalScore;

    }
    /*
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            player[i].cards[j].print();
        }

        for (int j = 1; j <= 4; j++)
        {
            cout << player[i].suitNum[j] << " ";
        }
        cout << "\n";
    }

    for (int i = 1; i <= 4;i++)
    {
        cout << playerScore[i] << " ";
    }
    */
    int maxScore = playerScore[1];
    int winner = 1;
    for (int i = 1; i <= 4; i++)
    {
        if (playerScore[i] > maxScore)
        {
            maxScore = playerScore[i];
            winner = i;
        }
    }

    cout << winner << ',' << maxScore;

    return 0;

}

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

void Deck::addCard(int pos, Card c)
{
    cards[pos] = c;
}

void Deck::sortCard()
{
    for (int i = 4; i >= 1; i--)
    {

        for (int j = 1; j <= i; j++)
        {
            if (cards[j].rank > cards[j + 1].rank)
            {
                int tempRank = cards[j].rank;
                cards[j].rank = cards[j + 1].rank;
                cards[j + 1].rank = tempRank;

                char tempSuit = cards[j].suit;
                cards[j].suit = cards[j + 1].suit;
                cards[j].suit = tempSuit;
            }


        }
    }
}


void Deck::countSuit()
{
    //四種花色
    suitNum = new int[NUM_TYPE]();
    //C, D, H, S
    //1, 2, 3, 4
    int seen[6] = { 0 };
    for (int i = 1; i <= 5; i++)
    {
        if (seen[i] == 0)
        {
            if (cards[i].suit == 'C')
                suitNum[1] += 1;
            else if (cards[i].suit == 'D')
                suitNum[2] += 1;
            else if (cards[i].suit == 'H')
                suitNum[3] += 1;
            else if (cards[i].suit == 'S')
                suitNum[4] += 1;

            for (int j = 1; j <= 5 - i; j++)
            {
                if (cards[i].suit == cards[i + j].suit)
                {
                    seen[i + j] = 1;
                    if (cards[i].suit == 'C')
                        suitNum[1] += 1;
                    else if (cards[i].suit == 'D')
                        suitNum[2] += 1;
                    else if (cards[i].suit == 'H')
                        suitNum[3] += 1;
                    else if (cards[i].suit == 'S')
                        suitNum[4] += 1;
                }
            }
        }
    }
}


bool Deck::hasStraight()
{
    bool straight = false;
    int count = 0;
    for (int i = 1; i <= 4; i++)
    {
        if ((cards[i].rank + 1) == cards[i + 1].rank)
            count += 1;
    }

    if (count == 4)
    {
        straight = true;
    }

    else if (cards[1].rank == 1 && cards[2].rank == 10 && cards[3].rank == 11 && cards[4].rank == 12 && cards[5].rank == 13)
    {
        straight = true;
    }

    return straight;

}

bool Deck::hasSameColor()
{
    bool allSameColor = false;
    for (int i = 1; i <= 4; i++)
    {
        if (suitNum[i] == 5)
            allSameColor = true;
    }
    return allSameColor;
}

int* Deck::countTwoAndThree()
{
    int two = 0;
    int three = 0;
    //紀錄這副牌裡面出現幾次兩張一樣的，幾次三張一樣的
    // 位置0 : 兩張一樣的出現幾次, 位置1 : 三張一樣的出現幾次
    int* twoThreeArray = new int[2]();
    //紀錄算過的位置
    delArray = new int[6]();
    for (int i = 1; i <= 5; i++)
    {
        int countSame = 0;
        if (delArray[i] == 0)
        {
            for (int j = 1; j <= 5 - i; j++)
            {
                if (cards[i].rank == cards[i + j].rank)
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

    twoThreeArray[0] = two;
    twoThreeArray[1] = three;
    return &twoThreeArray[0];
}

int Deck::getPoint()
{
    int score = 0;
    bool isSame = hasSameColor();
    bool isStraight = hasStraight();
    int* twoThreeArray = countTwoAndThree();
    //開始判斷是哪種牌型
    if (isSame == true)
    {
        //同花順:100
        if (isStraight == true)
        {
            score = 100;
        }

        //同花:20
        else
        {
            score = 20;
        }
    }
    //順:50
    else if (isStraight == true)
    {
        score = 50;
    }

    //葫蘆
    else if (twoThreeArray[0] == 1 && twoThreeArray[1] == 1)
    {
        score = 40;
    }

    //一對、A要同時處理，算出得到的最高分數
    else
    {
        //計算所有A的數量
        int countAllA = 0;
        for (int i = 1; i <= 5;i++)
        {
            if (cards[i].isA() == true)
                countAllA += 1;
        }
        //三個A以外的相同數字 or 兩個相同數字 + 其他三個不同數字
        if (twoThreeArray[0] == 1 || twoThreeArray[1] == 1)
            score += 5;
        //3個A，兩個不同數字
        if (twoThreeArray[1] == 1 && countAllA == 3)
            score += 1;
        //5個A
        else if (countAllA == 5)
            score += 11;
        //四個相同的數字
        else if (twoThreeArray[0] == 2)
            score += 10;

        //加入剩下的A(沒有被算過的)
        int countLeftA = 0;
        for (int i = 1; i <= 5;i++)
        {
            if (delArray[i] == 0)
            {
                if (cards[i].isA() == true)
                    countLeftA += 1;
            }
        }

        score += countLeftA;
    }

    return score;
}

int Randomizer::rand()
{
    cur = (a * cur + b) % c;
    return cur;
}

/*
901 101 10001 32767

S4,CA,H7,HQ,H10
H4,DA,S8,C7,CK
HJ,S6,H9,DK,S3
CJ,SQ,C5,C2,S10

1,1

325 101 10001 32767

HJ,D8,H6,S9,D7
H7,C10,HA,H5,D4
D10,H3,SA,S2,DA
C8,SJ,H10,DJ,C5

3,5

*/



/*
for (int i = 1; i <= 5; i++)
{
    cout << cardsArray[i].suit << " " << cardsArray[i].rank << "\n";
}
*/


/*
for (int i = 1; i <= 4; i++)
{
    cout << countSuit[i] << " ";
}
*/