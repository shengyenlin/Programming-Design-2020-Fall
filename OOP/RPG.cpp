#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//abstract class: can't (not recommended) be used to construct an object
class Character{
    protected:
        static const int EXP_LV = 100;
        string name;
        int level;
        int exp;
        int power;
        int knowledge;
        int luck;
        void levelUp(int pInc, int kInc, int lInc);
    public:
        Character(string n, int lv, int po, int kn, int lu);
        //virtual function: the invocation priority will be lower than child override function
        virtual void print();
        //pure virtual function: should not be called by anyone, but we still need this function to tell the compiler that
        //our children may need to invoke it (their override version)
        //we cannot create Character object now!
        virtual void beatMonster(int exp) = 0;
        string getName();
};

//concrete class: can be used to create an object
class Warrior:public Character{
    private:
        static const int PO_LV = 10;
        static const int KN_LV = 5;
        static const int LU_LV = 5;
    public:
        Warrior(string n, int lv = 1);
        void print();
        void beatMonster(int exp);
};

class Wizzard:public Character{
    private:
        static const int PO_LV = 4;
        static const int KN_LV = 9;
        static const int LU_LV = 7;
    public:
        Wizzard(string n, int lv = 1);
        void print();
        void beatMonster(int exp);
};

//class with polymorphism
class Team{
    private:
        int memberCount;
        Character* member[10];
    public:
        Team();
        ~Team();
        void addWarrior(string name, int lv);
        void addWizzard(string name, int lv);
        void memberBeatMonster(string name, int exp);
        void printMember(string name);
};

// void printInitial(Character c);

int main(){
    Warrior alice("Alice", 10);
    //polymorphism: we can use parent container to store child object!
    //early binding: type will be set at COMPILATION TIME, may discard value
    // Character c = alice;
    //cout << c.getName() << endl;

    //late binding: type will be set at RUN TIME, does not discard value
    Character* cPtr = &alice;
    cout << cPtr->getName() << endl;

    Wizzard bob("Bob", 8);
    // printInitial(alice);
    // printInitial(bob);

    //polymorphism is useful with arrays
    Character* charPtr[3];
    charPtr[0] = new Warrior("Alice", 10);
    charPtr[1] = new Wizzard("Sophie", 8);
    charPtr[2] = new Warrior("Amy", 7);
    for (int i = 0; i < 3; i++){
        charPtr[i]->print();
    }
    for (int i = 0; i < 3; i++){
        delete charPtr[i];
    }
    return 0;
}

Character::Character(string n, int lv, int po, int kn, int lu)
    :name(n), level(lv), exp(pow(lv - 1, 2) * EXP_LV), power(po),
    knowledge(kn), luck(lu){
}

void Character::print(){
    cout << this-> name
         << ": Level " << this->level
         << " (" << this->exp << "/" << pow(this->level, 2) * EXP_LV <<  "), "
         << this->power << "-" << this->knowledge << "-" << this->luck << "\n";
}

string Character::getName(){
    return this->name;
}

void Character::beatMonster(int exp){
    this->exp += exp;
    while(this->exp >= pow(this->level, 2) * EXP_LV){
        this->levelUp(0, 0, 0); 
    }
}

void Character::levelUp(int pInc, int kInc, int lInc){
    this->level++;
    this->power += pInc;
    this->knowledge += kInc;
    this->luck += lInc;
}

Warrior::Warrior(string n, int lv):
     Character(n, lv, lv * PO_LV, lv * KN_LV, lv * LU_LV){}

void Warrior::print(){
    cout << "Warrior ";
    Character::print(); 
}

void Warrior::beatMonster(int exp){
    this->exp+=exp;
    while(this->exp >= pow(this->level, 2) * EXP_LV){
        this->levelUp(PO_LV, KN_LV, LU_LV); 
    }
}

Wizzard::Wizzard(string n, int lv):
     Character(n, lv, lv * PO_LV, lv * KN_LV, lv * LU_LV){}

void Wizzard::print(){
    cout << "Wizzard ";
    Character::print(); 
}

void Wizzard::beatMonster(int exp){
    this->exp+=exp;
    while(this->exp >= pow(this->level, 2) * EXP_LV){
        this->levelUp(PO_LV, KN_LV, LU_LV); 
    }
}

Team::Team(){
    memberCount = 0;
    for (int i = 0; i < 10; i++){
        member[i] = nullptr;
    }
}

Team::~Team(){
    for (int i = 0; i < memberCount; i++){
        delete member[i];
    }
}

void Team::addWarrior(string name, int lv){
    if (memberCount < 10){
        member[memberCount] = new Warrior(name, lv);
        memberCount++;
    }
}

void Team::addWizzard(string name, int lv){
    if (memberCount < 10){
        member[memberCount] = new Wizzard(name, lv);
        memberCount++;
    }
}

void Team::memberBeatMonster(string name, int exp){
    for (int i = 0; i < memberCount; i++){
        if (member[i]->getName() == name){
            member[i]->beatMonster(exp);
            break;
        }
    }
}

void Team::printMember(string name){
    for (int i = 0; i < memberCount; i++){
        if (member[i]->getName() == name){
            member[i]->print();
            break;
        }
    }
}

//polymorphism is useful with functions
//you don't need to take careful specific child class
// void printInitial(Character c){
//     string name = c.getName();
//     cout << name[0] << endl;
// }