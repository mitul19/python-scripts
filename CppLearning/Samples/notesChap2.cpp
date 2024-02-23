#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;
/*
        <datatype> <variable name>;
        <datatype> <variable name> = <value>;

        Integer - whole numbers (int myVar;) - 4 bytes
        Float - decimal number (float mySalary;) - 4 bytes
        double - decimal num (double mySalary;) - 8 bytes
        char - single charactor - (char midInitial = "A";) - based on ASCII value
        string - series of chars - (string firstName = "Mitul";)
        bool isValid = TRUE; - boolean datatype

        another way in cpp11 is
                int y = x * 5
                double y = x * 3.5

        Naming conventions:
                can't start with special chars or numbers
                only allowed special char is underscore (_) and used for separate word if camel casing is not used  (emp_first_name or empFirstName)
                variable start with lowercase letters, and names are indictive to use variable

        Complier doesnt clear out data when you declare varible so it good to assign starting value.
        int age = 0;
        double salaryPerMonth = 0;
        string name = "";

        Storing data:
                int numEggs = 3;
                cout << (numEggs * 1.5); //console will say 4.5 but if we save it in int will be 4.
                cout << static_cast<int> (numEggs * 1.5) ; // casting
        rand() ; //generated num between 0 to 1
        srant(time(0)); // this is to seed generation with different values
        order of priority - any decimal num and int will default to double as double have 8 bytes to store
        Compiler moves sequentially so make sure you do calculation after getting values.
        Constants:
        Constants are a type of variable that make easy for programs that use calculations multiple times.
        Arrays:
        any datatype array can be created
        string playerName[2] = {"Mitul", "Max"};

 */
const int MAX_CHIPS = 100;
const float TAX_RATE = 0.04;
int main()
{
        int numEggs = 6;    //
        int taxRate = 4.67; //
        float bankBal = 10023.3454;
        cout << (numEggs * 1.7) << endl;                 // console will say 10.2 but if we save it in int will be 10.
        cout << static_cast<int>(numEggs * 1.5) << endl; // this will casted datatype int so 10
        cout << floor(taxRate) << " Floor Example rounds num down from cmath lib \n";
        cout << ceil(taxRate) << " ceil Example rounds num up from cmath lib \n";
        cout << (numEggs % 2) << " Modulo operator example \n";
        cout << pow(numEggs, 2) << " Pow cmath function example : pow(numEggs, 2) \n";
        cout << sqrt(numEggs) << " square root cmath function example : sqrt(numEggs) \n";
        cout << abs(taxRate) << " absolute int value cmath function example : abs(taxRate) \n";
        cout << fabs(bankBal) << " fabs: absolute float value cmath function example : fabs(bankBal) \n";

        int r = rand() % 6; // this will give num between 0-5, number generation start at same point
        srand(time(0));     // seeding current time - ctime is lib
        cout << r << " Example: int r = rand()%6;  with out supplying srand \n ";
        cout << rand() % 6 << " Example rand()%6 with supplying srand() \n";
        cout << " Example of Constant: " << (rand() % MAX_CHIPS) << " will be between 0-100 \n";
        float price = 4.50;
        int qty = 4;
        cout << "Your tax charged is: $ " << setprecision(2) << (price * qty * TAX_RATE) << " example of setprecision from iomanip lib - [setprecision(2) << (price * qty * TAX_RATE) ]\n";

        // Array
        string playerName[2] = {"Mitul", "Max"};

        return 0;
}