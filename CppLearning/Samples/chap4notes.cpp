#include <iostream> 
#include <ctime>
#include <cstdlib>
using namespace std; 

/* 
Notes: Function have reusable codes 
    string lib :  int string.length()
    iomanip lib :  Setw(), Setfill(), Setprecision() 
    cctype lib : bool isdigit(char), bool isalpha(char), bool isupper(char), bool islower(char) 
    cstdlib lib :  rand(), srand(int)

How to write Function:
    <Return Data Type> functionName (Parameter List with data types)
    {
        Function body code
        return value;
    } 
    void printReceipt(string companyName, float total)
    {
        fuction body code
    }
    Can be added above main/below main. can be added in diff. file but you need to include that file
    if you specify it below make sure above main declare function prototype
    return is must if its not void 
    you can return only one value

Function Parameter must match up by type order and number
    1. Pass by value - regular datatypes
    2. Pass by reference using & - Arrays always  
    
Scope - how long variable will leave 
    Local  - passed by value variables , variable inside main or other function have local scope
    Global - passed by ref. variable from main, declared at top of main


*/
//fuction prototypes so complier knows that its there after main()
void PrintHBD();
void PrintReceipt(string comName, float& total);
int ReturnAge(string name);
int main() 
{
    PrintHBD();
    PrintHBD();
    cout << "Happy birthday dear user \n";
    PrintHBD();
    float total = 2.57;
    string comName = "Pizza Bounty";

    cout << "Total before function: $" << total << endl;
    PrintReceipt(comName, total);
    cout << "your total now : $ " << total << endl;
    
    string name = "user007";
    int out = ReturnAge(name);
    cout <<  name << " your age supplied is : " << out << endl;

    return 0;
}

void PrintHBD()
{
    cout << "Happy Birthday to you \n";
}

void PrintReceipt(string comName, float& total)
{
    cout << "Thanks you for Purchase from " << comName << endl;
    total = total * 10;
}

int ReturnAge(string name)
{
    int age = 0;
    cout << name << " Would you provide your age: \n";
    cin >> age;
    return age;
}