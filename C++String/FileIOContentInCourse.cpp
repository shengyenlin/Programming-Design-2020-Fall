#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(){
    ofstream myFile;
    //app: append
    //ate: at the end (can modify file content)
    //out: output (default)
    myFile.open("temp.txt", ios::app);
    //return true if the file is (not) (老師應該寫錯了) created successfully 
    if (!myFile){
        exit(1);
    }
    //can only input basic data type, otherwise you have to do operator overloading
    myFile << "123456789  \nAAA\n" << 123.45;
    myFile.close();

    //input file
    ifstream myInputFile;
    myInputFile.open("score.txt");
    if (!myInputFile.eof()){
        string name;
        int score = 0;
        int sumScore = 0;
        int scoreCount = 0;
        while (myInputFile >> name >> score){
            sumScore += score;
            scoreCount++;
        }
        if (scoreCount != 0){
            cout << static_cast<double>(sumScore) / scoreCount << endl;
        }
        else{
            cout << "no grade!" << endl;
        }
    }
    myInputFile.close();

    ifstream inputFile;
    inputFile.open("score.txt");
    string name1;
    char c = 0;
    if (inputFile){
        inputFile >> name1; //read until whitespace, \t, \n or EOF
        c = inputFile.get(); //get the value of the read-write head, and move to the next value
        cout << c << "-"; // c = whitespace
        c = inputFile.get(); // c = the next value of whitespace
        cout << c << "-";
    }
    inputFile.close();

    //input unformatted input files
    //parsing: read data as char and manually find its data types
    inputFile.open("score.txt");
    char names[20];
    char c2 = 0;
    if (inputFile){
        inputFile.getline(names, 20, ' '); //read until the delimiter and discard it
        cout << names << endl; 
        c2 = inputFile.get(); 
        cout << c2 << "-"; 
        c2 = inputFile.get(); 
        cout << c2 << "-";
    }
    inputFile.close();

    inputFile.open("score.txt");
    if (inputFile){
        string name3;
        //use C++ string as container to avoid setting the maximum character of the function
        //global function defined in <string>
        getline(inputFile, name3, ' ');
        cout << name3 << endl; 
    }
    inputFile.close();

    //updating a file
    //copy and paste
    ifstream inFile2("score.txt");
    ofstream outFile2("scoreOut.txt");
    string name3;
    int score;
    if (inFile2 && outFile2){
        while (inFile2 >> name3 >> score){
            if(name3 == "Alex"){
                name3 = "Alexander";
            }
            outFile2 << name3 << " " << score << endl;
        }
    }
    inFile2.close();
    outFile2.close();

    //mix the usage of >> and getline
    ifstream inFile3("score2.txt");
    string name4;
    int score2 = 0;
    int sumScore = 0;
    if (inFile3){
        while (!inFile3.eof()){
            //getline will read file as char, stops at one char after the delimiter
            getline(inFile3, name4, ':');
            //>> can read file as the specified type, stops at the first char not of that type
            inFile3 >> score2;
            cout << score2 << " ";
            sumScore += score2;
        }
        cout << sumScore << endl;
    }
    inFile3.close();

    
    ifstream inFile4("score3.txt");
    string name5;
    string scoreStr;
    int score3 = 0;
    int sumScore2 = 0;
    if (inFile4){
        while (!inFile4.eof()){
            getline(inFile4, name5);
            //alternative way
            //getline(inFile4, scoreStr);77777777777
            //score3 = stoi(scoreStr);
            inFile4 >> score3;
            //bypass the newline character
            inFile4.ignore();
            sumScore2 += score3;
            cout << score3 << " ";
        }
        cout << sumScore2 << endl;
    }
    inFile4.close();
    return 0;
}