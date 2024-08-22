#include <iostream>

#include "Functions.h"

using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::begin;
using std::end;
using std::vector;

#include <algorithm>
using std::count;
using std::sort;

int main()
{
    printf("Hello\n");
    float i = 4.9;
    int j = 9;
    cout << i << " " << j << endl;

    int firstnumber;
    int secondnumber;
    bool keepgoing = true;
    int loopanswer;

    while (keepgoing)
    {
        /* code */
        cout << "Enter a Number:";
        cin >> firstnumber;
        cout << "You entered " << firstnumber << ". Enter another number: ";
        cin >> secondnumber;

        if (firstnumber < secondnumber)
        {
            cout << "The first number, " << firstnumber << ", is less than the second number, " << secondnumber << endl;
        }
        else
        {
            cout << "The first number, " << firstnumber << ", is not less than the second number, " << secondnumber << endl;
        }
        if (firstnumber > secondnumber)
        {
            cout << "The first number, " << firstnumber << ", is greater than the second number, " << secondnumber << endl;
        }
        if (firstnumber == secondnumber)
        {
            cout << "The first number, " << firstnumber << ", is equal to the second number, " << secondnumber << endl;
        }
        cout << "Compare another pair? 0 means no, any other number means yes: ";
        cin >> loopanswer;
        if (loopanswer == 0)
        {
            keepgoing = false;
        }
    }

    int guessnum = 5;
    int guess;
    bool notguessed = true;
    while (notguessed)
    {
        /* code */
        cout << "Guess My number [1-10]: ";
        cin >> guess;
        if (guess == guessnum)
        {
            cout << "Yes!" << endl;
            notguessed = false;
        }
        if (guess < guessnum)
        {
            cout << "Low value guess .." << endl;
        }
        if (guess > guessnum)
        {
            cout << "High value number .." << endl;
        }
    }

    int total = add(3, 4);
    cout << "3 + 4 is " << total << '\n';

    double another = add(1.2, 3.4);

    cout << '\n';
    cout << "1.2 + 3.4 is " << another;
    cout << '\n';

    auto totalofthree = add(1.1, 2.2, 3.3);
    cout << "1.1 + 2.2 + 3.3 is " << totalofthree;
    cout << '\n';

    add(0, 0, 0);

    if (test(true))
    {
        cout << "true passes the test" << '\n';
    }
    if (test(3.2))
    {
        cout << "3.2 passes the test" << '\n';
    }

    // How types can be problem see with uncomment
    // if (test(3))
    // {
    //     cout << "3 passes the test" << '\n';
    // }

    string demoname;
    cout << "who are you? ";
    cin >> demoname;
    string greeting = "Hello, " + demoname;
    if (demoname == "Mitul")
    {
        greeting += ", I know you!";
    }
    cout << greeting << '\n';

    int l = greeting.length();
    cout << "\"" + greeting + "\" is " << l << " characters long." << '\n';
    string beginning = greeting.substr(greeting.find(' ') + 1);
    cout << beginning << '\n';
    if (beginning == demoname)
    {
        cout << "expected result." << '\n';
    }

    string phrase1;
    string phrase2;
    cout << "Enter a Phrase: ";
    // cin.ignore() function is used which is used to ignore or clear one or more characters from the input buffer.
    cin.ignore(); // If user inputs a space before \n in previous cin before getline, only ignore itself wouldn't be enough so you have to use this code instead of ignore()
    getline(cin, phrase1);
    // cin >> phrase1; // it just reads one word

    cout << "Enter another Phrase: ";
    cin.ignore();
    getline(cin, phrase2);
    // cin >> phrase2;
    if (phrase1.length() == phrase2.length())
    {
        cout << "They are same length phrase" << endl;
    }
    if (phrase1.length() > phrase2.length())
    {
        cout << "Phrase 1 is bigger than Phrase 2" << endl;
    }
    if (phrase1.length() < phrase2.length())
    {
        cout << "Phrase 1 is smaller than Phrase 2" << endl;
    }

    vector<int> nums;
    for (int i = 0; i < 10; i++)
    {
        nums.push_back(i);
    }
    for (auto item : nums)
    {
        cout << item << " ";
    }
    cout << endl;

    vector<string> words;

    cout << "enter three words ";
    for (int i = 0; i < 3; i++)
    {
        string s;
        cin >> s;
        words.push_back(s);
    }
    for (auto item : words)
    {
        cout << item << " ";
    }
    cout << endl;
    cout << "int vector nums has " << nums.size() << " elements." << '\n';
    cout << "string vector nums has " << words.size() << " elements." << '\n';

    nums[5] = 3;
    nums[6] = -1;
    nums[1] = 99;

    for (auto item : nums) // range based for
    {
        cout << item << " ";
    }
    cout << endl;

    for (unsigned int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
    for (auto i = begin(nums); i != end(nums); i++) // iterator based loop
    {
        cout << *i << " ";
    }
    cout << endl;

    sort(begin(words), end(words));
    for (auto item : words)
    {
        cout << item << " ";
    }
    cout << endl;

    int threes = count(begin(nums), end(nums), 3);
    cout << "vector of ints has " << threes << " elements with value 3" << '\n';

    int tees = count(begin(words[0]), end(words[0]), 't');
    cout << "first word has " << tees << " letter t's" << '\n';

    return 0;
}
