#include "animal.h"

//Constructor to set inialization - overloading a function - public member function 
animal::animal(std::string name_i, int age_i, unsigned char purpose_i){
    name = name_i;
    age = age_i;
    purpose = purpose_i;
}   
//getter functions
std::string animal::get_name(){
    return name;
}
int animal::get_age(){
    return age;
}
unsigned char animal::get_purpose(){
    return purpose;
}
//Setter functions.
void animal::set_age(int new_age){
    age = new_age;
}
void animal::set_name(std::string new_name){
    name = new_name;
}
void animal::set_purpose(unsigned char new_purpose){
    purpose = new_purpose;
}