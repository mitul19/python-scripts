//FILE IO Demo.

#include <iostream>
#include <string>
#include <fstream>  //fstream header - part if input output lib.
#include "records.cpp" //Exercise work to read student record 
#include <vector>

using namespace std;

ifstream inFile;
string str;
int num;
char letter;

//Writing related items
ofstream outFile;
float a = 4.333f, b = 5.302f;

//Exercise work
StudentRecords SR;
int id;
void initialize();  //In function initialization.
void initialize(ifstream&);  //File reading 

int main(){
    //Reading file and manipulation
    inFile.open("people.txt");
    if(inFile.fail())
        cout << endl << "File Not found!" << endl;
    else {
        while (!inFile.eof())
        {
            getline(inFile, str);
            cout << str << ", ";
            getline(inFile, str);
            num = stoi(str);
            cout << num << ", ";
            getline(inFile,str);
            letter = str[0];
            cout << letter << endl;
        }
        inFile.close();        
    }

    
    // Wrting inside file
    outFile.open("cal.txt");
    if(outFile.fail())
        cout << endl << "Couldn't open the file" <<endl;
    else {
        outFile << "a = " << a << endl;
        outFile << "b = " << b << endl;
        outFile << "a + b = " << a+b << endl;
        outFile << "a * b = " << a*b << endl;  
        outFile.close();
        cout << endl << "File Written successfully" <<endl;              
    }

    //Exercise work 
	initialize(inFile);
    initialize();
    SR.report_file(outFile);

    cout << "Enter a student ID: ";
    cin >> id;
    SR.report_card(id,cout);
    return(0);
}

void initialize(ifstream& inFile) {
    string inStr, name;
    int sid, cid;
    unsigned char credits;
    char grade;
    int count = 0;

    //Readind students 
    inFile.open("students.txt");
    if(inFile.fail())
        cout << endl << "File students.txt Not found!" << endl;
    else {
        while (!inFile.eof())
        {
            getline(inFile, inStr);
            sid = stoi(inStr);
            getline(inFile, name);
            SR.add_student(sid,name);
            count++;
        }
        inFile.close();   
        cout << "Found " << count << " students" << endl;     
    }

    //reading courses
    count = 0;
    inFile.open("courses.txt");
    if(inFile.fail())
        cout << endl << "File courses.txt Not found!" << endl;
    else {
        while (!inFile.eof())
        {
            getline(inFile, inStr);
            cid = stoi(inStr);
            getline(inFile, name);
            getline(inFile, inStr);
            credits = stoi(inStr);
            SR.add_course(cid,name,credits);
            count++;
        }
        inFile.close();   
        cout << "Found " << count << " Courses" << endl;     
    }

    //reading grades
    count = 0;
    inFile.open("grades.txt");
    if(inFile.fail())
        cout << endl << "File grades.txt Not found!" << endl;
    else {
        while (!inFile.eof())
        {
            getline(inFile, inStr);
            sid = stoi(inStr);
            getline(inFile, inStr);
            cid = stoi(inStr);
            getline(inFile, inStr);
            grade=inStr[0];
            SR.add_grade(sid,cid,grade);
            count++;
        }
        inFile.close();   
        cout << "Found " << count << " Grades" << endl;     
    }

}

void initialize(){
	SR.add_student(3, "Mitul Patel");
	SR.add_student(4,"Shivani");

	SR.add_course(1, "Algebra", 5);
	SR.add_course(2, "Physics", 4);
	SR.add_course(3, "English", 3);
	SR.add_course(4,"Economics",4);

	SR.add_grade(3, 1, 'B');
	SR.add_grade(3, 2, 'A');
	SR.add_grade(3, 3, 'B');
	SR.add_grade(4, 1, 'A');
	SR.add_grade(4, 3, 'A'); 
	SR.add_grade(4, 4, 'A');
}