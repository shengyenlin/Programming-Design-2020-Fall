#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <time.h>

using namespace sf;
using namespace std;

int N = 20, M = 16;
int size = 64;
int w = size * N;
int h = size * M;
int scoreNum[3];
int whichHead;

int dir, num = 4;
int last = 10;
int score = 0;

class Virus
{
public:
    int x, y;
};

class People
{
public:
    int x, y;
};

Virus s[1000];
People p;


///////////////////////////////////////
bool isOverlap()
{
    for (int i = 0;i < num;i++)
    {
        if (s[i].x == p.x && s[i].y == p.y)
            return true;
    }
    return false;
}

void Tick(int& whichHead)
{
    //Update the location of "Bodies"
    for (int i = num;i > 0;i--)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    //Update the location of "Head"
    if (dir == 0)
        s[0].y += 1;

    if (dir == 1)
        s[0].x -= 1;

    if (dir == 2)
        s[0].x += 1;

    if (dir == 3)
        s[0].y -= 1;

    //Boundary Problem ?
    if (s[0].x > N - 1)
        s[0].x = 0;

    if (s[0].x < 0)
        s[0].x = N - 1;

    if (s[0].y > M - 1)
        s[0].y = 0;

    if (s[0].y < 0)
        s[0].y = M - 1;

    //Give the location of the Food
    if ((s[0].x == p.x) && (s[0].y == p.y))
    {
        num++;
        score++;
        int overlap = 1;
        while (overlap == 1)
        {
            p.x = rand() % N;
            p.y = rand() % M;
            overlap = isOverlap();
            whichHead = rand() % 4;
            //cout << rand()%4;
        }
    }

}

void scoreCal()
{
    scoreNum[2] = score / 100;
    scoreNum[1] = (score - 100 * scoreNum[2]) / 10;
    scoreNum[0] = score - 100 * scoreNum[2] - 10 * scoreNum[1];
}

bool gameOver()
{
    for (int i = 1;i < num;i++)
    {
        if (s[0].x == s[i].x && s[0].y == s[i].y)
            return false;
    }
    return true;
}

///////////////////////////////////////////////////////////
int main()
{

    sf::Music music;
    //music.openFromFile("C:\\Users\\joy\\Documents\\C++\\Final - Copy\\Final\\Mainmusic.wav");

    if (!music.openFromFile("C:\\Users\\joy\\Documents\\C++\\Final_music\\Final\\MainMusic.wav"))
    {
        std::cout << "error" << std::endl;
    }

    sf::Music music2;
    //music.openFromFile("C:\\Users\\joy\\Documents\\C++\\Final - Copy\\Final\\Mainmusic.wav");

    if (!music2.openFromFile("C:\\Users\\joy\\Documents\\C++\\Final_music\\Final\\gameOver.wav"))
    {
        std::cout << "error" << std::endl;
    }

    music.setLoop(true);
    music.play();

    srand(time(0));

    RenderWindow window(VideoMode(w + 8 * size, h), "Virus Game!");

    Texture t1, t2, t4, t5, b1, b2, b3, b4;
    t1.loadFromFile("C:\\Users\\joy\\Desktop\\image\\28time37.jpg");
    t2.loadFromFile("C:\\Users\\joy\\Desktop\\image\\virus_smallest.png");
    t4.loadFromFile("C:\\Users\\joy\\Desktop\\image\\b.png");
    t5.loadFromFile("C:\\Users\\joy\\Desktop\\image\\score.png");

    b1.loadFromFile("C:\\Users\\joy\\Desktop\\image\\bystander.png");
    b2.loadFromFile("C:\\Users\\joy\\Desktop\\image\\bystander2.png");
    b3.loadFromFile("C:\\Users\\joy\\Desktop\\image\\bystander3.png");
    b4.loadFromFile("C:\\Users\\joy\\Desktop\\image\\bystander4.png");


    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Sprite spriteB1(b1);
    Sprite spriteB2(b2);
    Sprite spriteB3(b3);
    Sprite spriteB4(b4);


    Clock clock;
    float timer = 0, delay = 0.1;

    p.x = 5;
    p.y = 5;

    int val = 0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        last = dir;
        if (Keyboard::isKeyPressed(Keyboard::Left) && last != 2)  dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right) && last != 1)  dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up) && last != 0)  dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down) && last != 3)  dir = 0;

        if (timer > delay) { timer = 0; Tick(whichHead); }

        ////// draw  ///////
        window.clear();

        Sprite sprite4(t4), sprite5(t5);
        sprite4.setPosition(N * size, 0);
        window.draw(sprite4);
        sprite5.setPosition((N + 2.5) * size, 3 * size);
        window.draw(sprite5);

        sprite1.setPosition(0, 0);
        window.draw(sprite1);

        switch (whichHead)
        {
        case 0:
            spriteB1.setPosition(p.x * size, p.y * size);
            window.draw(spriteB1);
            break;
        case 1:
            spriteB2.setPosition(p.x * size, p.y * size);
            window.draw(spriteB2);
            break;
        case 2:
            spriteB3.setPosition(p.x * size, p.y * size);
            window.draw(spriteB3);
            break;
        case 3:
            spriteB4.setPosition(p.x * size, p.y * size);
            window.draw(spriteB4);
            break;
        default:
            break;
        }


        for (int i = 0;i < num;i++)
        {
            sprite2.setPosition(s[i].x * size, s[i].y * size);
            window.draw(sprite2);
        }


        ///Score///
        scoreCal();
        std::string s1 = "", s2 = "", s3 = "";
        s1 = "C:\\Users\\joy\\Desktop\\image\\" + std::to_string(scoreNum[2]) + ".png";
        s2 = "C:\\Users\\joy\\Desktop\\image\\" + std::to_string(scoreNum[1]) + ".png";
        s3 = "C:\\Users\\joy\\Desktop\\image\\" + std::to_string(scoreNum[0]) + ".png";
        Texture tScore1, tScore2, tScore3;
        tScore1.loadFromFile(s1);
        tScore2.loadFromFile(s2);
        tScore3.loadFromFile(s3);

        Sprite sprite_Score1(tScore1);
        Sprite sprite_Score2(tScore2);
        Sprite sprite_Score3(tScore3);

        sprite_Score1.setPosition((N + 1.4) * size, 10 * size);  window.draw(sprite_Score1);
        sprite_Score2.setPosition((N + 3.4) * size, 10 * size);  window.draw(sprite_Score2);
        sprite_Score3.setPosition((N + 5.4) * size, 10 * size);  window.draw(sprite_Score3);

        if (score > 0 && gameOver() == false)
        {
            music.stop();
            music2.play();

            string path = "";
            if (score <= 30)
                path = "C:\\Users\\joy\\Desktop\\image\\shitty.png";
            else if (score > 30 && score <= 60)
                path = "C:\\Users\\joy\\Desktop\\image\\decent.png";

            Texture tEnd;
            tEnd.loadFromFile(path);
            Sprite sprite_End(tEnd);
            while (Keyboard::isKeyPressed(Keyboard::Enter) == false)
            {
                sprite_End.setPosition(0, 0);
                window.draw(sprite_End);
                window.display();
            }

            break;
        }

        if (score >= 100)
        {
            music.stop();
            music2.play();
            string path = "C:\\Users\\joy\\Desktop\\image\\super.png";

            Texture tEnd;
            tEnd.loadFromFile(path);
            Sprite sprite_End(tEnd);
            while (Keyboard::isKeyPressed(Keyboard::Enter) == false)
            {
                sprite_End.setPosition(0, 0);
                window.draw(sprite_End);
                window.display();
            }

            break;
        }

        window.display();
    }

    return 0;
}
