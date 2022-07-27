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
#include <vector>  //STL addition 

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

float flt = -7.44f;
int32_t sgn;
uint32_t unsgn;

// Structure related items
enum purpose { dairy, meat, hide, pet };

// enum cow_purpose { dairy, meat, hide, pet }; //hiding this to keep single purpose enum
struct cow{
    string name;
    int age;
    unsigned char purpose;
};

//Class related Items:
// enum goat_purpose { dairy, meat, hide, pet }; //hiding this to keep single purpose enum
class goat{
public:
    //Constructor to set inialization - overloading a function - public member function 
    goat(string name_i, int age_i, unsigned char purpose_i){
        name = name_i;
        age = age_i;
        purpose = purpose_i;
    }   
    //getter functions
    string get_name(){
        return name;
    }
    int get_age(){
        return age;
    }
    unsigned char get_purpose(){
        return purpose;
    }
    //Setter functions.
    void set_age(int new_age){
        age = new_age;
    }
    void set_name(string new_name){
        name = new_name;
    }
    void set_purpose(unsigned char new_purpose){
        purpose = new_purpose;
    }
private:
    string name;
    int age;
    unsigned char purpose;
};

vector<int> primes;

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
    cout << endl;
    cout << array_str1 << endl;
    //operator overloading via + to concat and none of the operand gets modified 
    cout << std_str1 + std_str2 << endl;

//Type casting 
    sgn = flt; //implecit type conversion or casting.
    unsgn = sgn; //-ve will be 2^32 - 7 
    cout << endl;
    cout << " float: " << flt << endl;
    cout << " int32: " << sgn << endl;
    cout << "uint32: " << unsgn << endl;

    int fahrenheit = 100; //length of int will be implementation dependant 
    int celsius;

    celsius = (5 / 9) * (fahrenheit - 32); //INT div will yield INT Quotient 
    cout << endl;
    cout << "Fahrenheit: " << fahrenheit << endl;
    cout << "Celsius   : " << celsius << endl;

    celsius = ((float)5 / 9.0) * (fahrenheit - 32);  //Expression convert to largest type present so it will be float
    cout << endl;
    cout << "Fahrenheit: " << fahrenheit << endl;
    cout << "Celsius   : " << celsius << endl;

    float weight = 10.99;  //Extracting float
    
    cout << endl;
    cout << "Float          : " << weight << endl;
    cout << "Integer part   : " << (int) weight << endl;
    cout << "Fractional part: " << (int)((weight - (int)weight) * 10000) << endl;  //Floating point num representation.

    double d_weight = 10.99;  //Extracting double
    
    cout << endl;
    cout << "Float          : " << d_weight << endl;
    cout << "Integer part   : " << (int) d_weight << endl;
    cout << "Fractional part: " << (int)((d_weight - (int)d_weight) * 10000) << endl;  //double give better fractional representation.

//PRACTICAL Work. 
	int nums[5] = {1,23,32,24,337};
	float result; 
    result = (float)(nums[0] + nums[1] + nums[2] + nums[3] + nums[4])/5.0; 
    cout << endl;
	cout << "The average is " << result << endl;

//STRUCTURE Work.
    cow my_cow;
    my_cow.age = 5;
    my_cow.name = "Betsy";
    my_cow.purpose = dairy;
    cout << endl;
    cout << my_cow.name << " is a type-" << (int)my_cow.purpose << " cow." << endl;
    cout << my_cow.name << " is " << my_cow.age << " years old." << endl;

//CLASS 
    goat my_goat("Hildy",7,pet);
    cout << endl;
    cout << my_goat.get_name() << " is a type-" << (int)my_goat.get_purpose() << " goat." << endl;
    cout << my_goat.get_name() << " is " << my_goat.get_age() << " years old." << endl;
    my_goat.set_name("lola");
    my_goat.set_age(10);
    my_goat.set_purpose(hide);
    
    cout << "Printing newer values set via setter" <<endl;
    cout << my_goat.get_name() << " is a type-" << (int)my_goat.get_purpose() << " goat." << endl;
    cout << my_goat.get_name() << " is " << my_goat.get_age() << " years old." << endl;

//VECTOR STL
    primes.push_back(2);
    primes.push_back(3);
    primes.push_back(5);
    primes.push_back(7);
    primes.push_back(11);
    cout << endl;
    cout << "The vector has " << primes.size() << " elements." << endl;
    cout << "The element at index 2 is " << primes[2] << endl;
    primes[2] = 13;
    cout << "The element at index 2 is " << primes[2] << endl;
    cout << endl;

    vector<goat> cattle;
    cattle.push_back(goat("Betty", 6, meat));
    cattle.push_back(goat("Libby", 4, hide));
    cattle.push_back(goat("Trudy", 5, pet));
    cattle.push_back(goat("Betsy", 2, dairy));

    cout << "The first goat is " << cattle.begin()->get_name() << endl;
    cout << "At index 1 we have " << cattle[1].get_name() << endl;
    cout << "Next to last is " << prev(cattle.end(), 2)->get_name() << endl;
    cout << "The last goat is " << (cattle.end() - 1)->get_name() << endl;

    return(0);

}