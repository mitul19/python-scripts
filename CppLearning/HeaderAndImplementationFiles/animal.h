// #pragma once //Only include it onces for compiler 

#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>

enum purpose { dairy, meat, hide, pet }; 

class animal{
public:
    //Constructor to set inialization - overloading a function - public member function 
    animal(std::string name_i, int age_i, unsigned char purpose_i);
    //getter functions
    std::string get_name();
    int get_age();
    unsigned char get_purpose();
    //Setter functions.
    void set_age(int new_age);
    void set_name(std::string new_name);
    void set_purpose(unsigned char new_purpose);
private:
    std::string name;
    int age;
    unsigned char purpose;
};
#endif //ANIMAL_H