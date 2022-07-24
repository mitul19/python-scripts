/* Multi line comment 
Learning C++ 
Case sensitive 
identing is important to make code readable. complier dont require identation 
*/

//pre processor directives
#include <iostream> //contains classes, object to print and receive data from keystrokes
#include <string>  // to get string related classes 
#include <typeinfo> //to print via operator typeid
#include <cstdint> //c header file made available in cpp
#include <cstring> //include function to handle char array strings 
#include "mylib.cpp"  //Directive to include my libraries and header

#define CAPACITY 5000 
#define DEBUG  //Comment MACROS then debug cout will not be printed. 
using namespace std; //cout, endl are member ot std namespace so we can specify it use as default

int a, b ,c ; //global variables should be 0 by default

// Array related global CONSTs and variables. we can use #define AGE_LENGTH 4 MACRO as well
const int AGE_LENGTH = 4;
int age[AGE_LENGTH];
float temperature[] = {31.5, 32.7, 38.9};

// String related global, consts 
const int LENGTH1 = 25;
char array_str1[LENGTH1] = "Hey guys! ";
char array_str2[] = "What's up?";
string std_str1 = "Hi everybody! ";
string std_str2 = "How's the going?";

int main() //must return integer as defined
{

//Hello world Program 
    std::cout << "Hi There!" << std::endl;

    string str;
    cout << "Enter your name: ";
    cin >> str;  // it take only one word only without spaces.
    cout << "Nice to meet you. " << str << endl;
    
//Data Type demo
    bool my_flag;
    a = 7;
    my_flag = false;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "flag = " << my_flag << endl;  //FLASE is printed as 0 
    my_flag = true;
    cout << "flag = " << my_flag << endl;
    cout << "a+b = " << a+b << endl;
    cout << "b-a = " << b-a << endl;
    unsigned int positive;
    positive = b - a;
    cout << "b-a (unsigned) = " << positive << endl; // 2^32 -7 will be printed 

// Auto Type inference 
    auto a = 8;
    auto b = 12345678901;
    auto c = 3.14f;
    auto d = 3.14;
    auto e = true;
    auto f = 'd';
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    cout << typeid(c).name() << endl;
    cout << typeid(d).name() << endl;
    cout << typeid(e).name() << endl;
    cout << typeid(f).name() << endl;

//Preprocessor directives usages
    int32_t large = CAPACITY;
    uint8_t small = 37;
#ifdef DEBUG
    cout << "[About to perform the addition]" << endl;
#endif
    large += small; // shorthand for large = large + small
    cout << "The large integer is " << large << endl;
    myfunc(); //using function from user defined code.

//Arrays demo.
    age[0] = 25;
    age[1] = 20;
    age[2] = 19;
    age[3] = 19;

    cout << "The Age array has " << AGE_LENGTH << " elements" << endl;
    cout << "Age[0] = " << age[0] << endl;
    cout << "Age[1] = " << age[1] << endl;
    cout << "Age[2] = " << age[2] << endl;
    cout << "Age[3] = " << age[3] << endl;
    cout << endl;
    cout << "Temp[0] = " << temperature[0] << endl;
    cout << "Temp[1] = " << temperature[1] << endl;
    cout << "Temp[2] = " << temperature[2] << endl;  

//Strings demos.
    //cstring strcat function to concat. and store it on first string.
    strcat(array_str1, array_str2);
    // strcat_s(array_str1, LENGTH1, array_str2); it may be asked to use strcat_s on VS code.
    cout << array_str1 << endl;
    //operator overloading via + to concat and none of the operand gets modified 
    cout << std_str1 + std_str2 << endl;
    
    return(0);
}