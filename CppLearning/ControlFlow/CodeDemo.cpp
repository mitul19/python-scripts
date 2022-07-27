// Learning C++ 
// Exercise 04_01
// If Statements, by Eduardo Corpeño 

#include <iostream>
#include <vector>
#include "../HeaderAndImplementationFiles/records.cpp"  //We will use Student Grade and cource from other folders headers

using namespace std;

int a = 1023;
bool flag = false;
char letter = 'd';

float operand_1,  operand_2, result;
char operation;

vector<int> numbers = {12,25,31,47,58};      // cpp 11 allows that use  -std=c++11 in argument (via tasks.json in vs Code) 
vector<char> letters = {'M','I','T','U','L'};
float average;

//using gloabal variables to populate student data with included records.cpp 

vector<Student> students = {Student(1,"George P. Burdell"),
							Student(2,"Nancy Rhodes")};

vector<Course> courses = {Course(1,"Algebra",5),
						  Course(2,"Physics",4),
						  Course(3,"English",3),
						  Course(4,"Economics",4)};

vector<Grade> grades = {Grade(1,1,'B'),	Grade(1,2,'A'),	Grade(1,3,'C'),
						Grade(2,1,'A'),	Grade(2,2,'A'), Grade(2,4,'B')};

float GPA = 0.0f;
int id;

int main(){
    if (a > 1000)
        cout << "Warning: a is over 1000." << endl;

    if (a % 2)
        cout << "a is odd" << endl;
    else
        cout << "a is even" << endl;

    cout << "The letter " << letter << " is ";
    if (letter != 'a' && letter != 'e' && letter != 'i' && letter != 'o' && letter != 'u' &&
        letter != 'A' && letter != 'E' && letter != 'I' && letter != 'O' && letter != 'U')
        cout << "not ";
    cout << "a vowel." << endl;

    if (flag)
        cout << "The flag is true!" << endl;

// Switch 
    cout << endl;
    cout << "Enter Operand 1: " << endl;
    cin >> operand_1;
    cout << "Enter Operand 2: " << endl;
    cin >> operand_2;
    cout << "Choose Operation: + - * /" << endl;
    cin >> operation;
    switch (operation)
    {
    case '+':
        result = operand_1 + operand_2;
        break;
    case '-':
        result = operand_1 - operand_2;
        break;
    case '*':
        result = operand_1 * operand_2;
        break;
    case '/':
        result = operand_1 / operand_2;
        break;
    default:
        result = operand_1 + operand_2;
        break;
    }    
    cout << "The result is " << result << endl;

// While  
    cout << endl;
    vector<int>::iterator ptr_1 = numbers.begin();  // you can use auto key word as well.
    auto ptr_2 = letters.begin();

    while (ptr_1 != numbers.end()){
        cout << *ptr_1 << " ";
        ptr_1=next(ptr_1,1);
    }
    cout << endl;
    int i = 0;
    do {
        cout << letters[i];
        i++;
    } while (i < letters.size());
    
    cout << endl;

    do { 
        cout << *ptr_2; 
        ptr_2=next(ptr_2,1);
    } while (ptr_2 != letters.end());
    cout << endl;

// FOR Loop
    cout << endl;
    average = 0.0f;
    for (int i = 0; i < numbers.size(); i++)
        average += numbers[i];
    average /= numbers.size();
    cout << "Average: " << average << endl;

    average = 0.0f;
    // Another way to traverse inside for loop 
    for (auto x : numbers) //read as for each x in numbers. it will copy each value when traversing so for object it is better to use references 
        average += x;
    average /= numbers.size();
    cout << "Average: " << average << endl;


// Practic Work to get GPA from student. 
    cout << endl;
	cout << "Enter a student ID: ";
	cin >> id;

	float points = 0.0f, credits = 0.0f;  
    for (Grade& grd : grades)  // references done to avoid copying object  
        if(grd.get_student_id() == id) {
            float num_grd;
            switch (grd.get_grade())
            {
            case 'A': num_grd = 4.0f; break;
            case 'B': num_grd = 3.0f; break;
            case 'C': num_grd = 2.0f; break;
            case 'D': num_grd = 1.0f; break;
            case 'E': num_grd = 0.0f; break;
            default: num_grd = 0.0f; break;
            };
            int j=0; //Caclulate GPA
            while (j < courses.size() && courses[j].get_id() != grd.get_course_id()) 
                j++;
            credits += courses[j].get_credits();
            points += num_grd * courses[j].get_credits();
        }
    GPA = points/credits;

    string student_str;
    int z = 0;

    while ( z < students.size() && students[z].get_id() != id) 
        z++;
    student_str = students[z].get_name();
    cout << "The GPA for " << student_str << " is " << GPA << endl;
    return (0);
}














