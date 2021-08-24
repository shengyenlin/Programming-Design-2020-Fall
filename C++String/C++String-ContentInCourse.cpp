#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

int main(){
    string myStr;
    string yourStr = "your string";
    string herStr =(yourStr);

    //length / size of string
    cout << myStr.length() << endl;
    cout << yourStr.size() << endl;
    //max size of string
    cout << myStr.max_size() << endl;

    //assignment
    myStr = yourStr = "change string!";
    //can also assign C string to C++ string
    char hisString[100] = "oh ya";
    myStr = hisString;
    cout << myStr << endl;

    //string concatentaion
    string concatString = yourStr + myStr;
    cout << concatString << endl;
    //string indexing
    char a = concatString[0];
    cout << a << endl;

    //string input: use cin >> or getline(cin, stringObject, delimiter)
    string inString;
    //white space is the delimiter
    // cin >> inString;
    // cout << inString << endl;
    // string getString;
    // getline(cin, getString, '&');
    // cout << getString << endl;
    
    //slice string: substr(start, end = end)
    // cout << getString.substr(2, 5) << endl;

    //find a string: find() and return the beginning position, if no substring, return npos
    string string1 = "123456789";
    if (string1.find("456") != string::npos){
        cout << string1.find("456") << endl;
    }
    cout << string1.find("0") << endl;
    
    //use >, >=, <=, ... to compare string (operator overloading)
    string str2 = "abc";
    string str3 = "edf";
    cout << (str3 > str2) << endl;

    //useful functions: insert, replace, erase
    string str4 = "abcdefghi";
    str4.insert(5, "limit");
    cout << str4 << endl;
    str4.replace(5, 3, "abc");
    cout << str4 << endl;
    str4.erase(5, 7);
    cout << str4 << endl;
    //convert to C string: string.c_str()
    //convert to int/float/double: stoi(), stof(), stod()
    //number to C++ string: string = to_string(int)

    //we use two bytes to represent a chinese character
    //we need to change the encoding of compiler to Big5, otherwise it will show non sense
    string str5 = "¤j®a¦n";
    cout << str5 << endl;
    cout << str5.length() << endl; //6
    char char1[100] = "³á°Õ";
    cout << char1 + 2 << endl;

    //reverse a chinese string, need to do it two-by-two
    int n = str5.length();
    string t = str5;
    for (int i = 0; i < n - 1; i = i + 2){
        t[n - i - 2] = str5[i];
        t[n - i - 1] = str5[i + 1];
    }
    cout << t << endl;
    return 0;
}