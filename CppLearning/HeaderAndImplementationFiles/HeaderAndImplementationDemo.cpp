// Header and Implementation Files source code

#include <iostream>
#include <string>
#include "animal.cpp"  //Functions are defined there. 

using namespace std;

int a = 37;
int *ptr;
animal *my_cow;  //Dynamic allocation of memory when class constructor is called.

int main(){
    animal my_goat("Hildy",7,pet);
    cout << endl;
    cout << my_goat.get_name() << " is a type-" << (int)my_goat.get_purpose() << " goat." << endl;
    cout << my_goat.get_name() << " is " << my_goat.get_age() << " years old." << endl;
    my_goat.set_name("lola");
    my_goat.set_age(10);
    my_goat.set_purpose(hide);
    
    cout << "Printing newer values set via setter" <<endl;
    cout << my_goat.get_name() << " is a type-" << (int)my_goat.get_purpose() << " goat." << endl;
    cout << my_goat.get_name() << " is " << my_goat.get_age() << " years old." << endl;

// POINTER Examples.
    ptr = &a;

    cout << endl;
    cout << "           The content of a is " << a << endl;
    cout << "    ptr is pointing to address " << ptr << endl;
    cout << "           The address of a is " << &a << endl;
    cout << "Where ptr is pointing, we have " << *ptr << endl;
    cout << "         The address of ptr is " << &ptr << endl;
    cout << endl;

    my_cow = new animal("gertie",3, pet);  //Calling cronstructor to set memory for pointer. 
    cout << my_cow->get_name() << " is a type-" << (int)my_cow->get_purpose() << " cow." << endl;  // (->) used member of pointer to get details.  (*my_cow).get_name 
    cout << my_cow->get_name() << " is " << my_cow->get_age() << " years old." << endl;
    //you can derefence pointer and then use (.) as well. it can get messy if you derefence it in trees or linked list.
    cout << (*my_cow).get_name() << " is a type-" << (int)(*my_cow).get_purpose() << " cow." << endl; 
    cout << (*my_cow).get_name() << " is " << (*my_cow).get_age() << " years old." << endl;

    
    delete my_cow;   // calls a class destructor to free dynamically allocated memory 
   
    return (0);
}




