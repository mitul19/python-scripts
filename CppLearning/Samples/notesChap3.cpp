#include <iostream> 
#include <ctime>
#include <cstdlib>
using namespace std; 

/*
    if (condition is true)
    {
        <do this body of code>
    }
    else if 
    {
        <do this body of code for else if > 
    }
    else
    {
        <do this else body of code>
    }
    if statement alone is enough,
    if you have one line you dont need curly braces 
    else is for catch all 
    top down compilation and execution  - we can have only one TRUE condition 
    Boolean operator will evaluate to TRUE or FALSE [ <, > , ==, <=, >= , !=, AND (&&), OR (||)]

    Switch statements:
    swith(test variable)
    {
        case 1:
        case 2:
            break;
        default:
            break:
    }
    break is need other wise it keep executing it.
    Check DiceRoll.cpp

    For Loops
*/

int main()
{
    // Array 
    string playerName[2] = {"Mitul", "Max"};
    // bool 
    bool player1Turn = false;

    // if else example:
    if(player1Turn)
    {
        cout << playerName[0] << " you need to play now \n" ;
    }
    else cout << playerName[1] << " player2 need too play \n" ; 

    // Switch case for rolling dice : 
    int dice = 0;
    //seed the random number generator
    srand(time(0));
	dice = (rand() % 6) + 1;
  	cout << "You rolled a " << dice << endl;;
    switch (dice)
    {
    	case 1: //if (dice == 1)
    		cout << "One \n";
    		break;
    	case 2:
    		cout << "Two \n";
    		break;
    	case 3:
    		cout << "Three \n";
    		break;
    	case 4:
    		cout << "Four \n";
    		break;
    	case 5:
    		cout << "Five \n";
    		break;
    	case 6:
    		cout << "Six \n";
    		break;
    	default:
    		cout << "Invalid \n";
    		break;    	
	}

    // for loop great when we know how many time we need to loop over 
    for(int i =0; i<5; i++)
    {
        cout << "Hello World " << i << endl;
    }

    int userChoice = 1;
    while (userChoice == 1)
    {
  		cout << "Hello welcome to my menu\n";
  		cout << "Please choose one of the following options \n";
  		cout << "1. continue\n";
  		cout << "2. quit\n";
  		cin >> userChoice;
	} 
    int m = 0;
    
    do 
    {
        cout << "hello world " << m << endl;
        m++;
    } while (m <5);
   
    

}