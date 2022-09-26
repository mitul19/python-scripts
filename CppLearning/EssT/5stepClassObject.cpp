/*
CH6: Classes and Objects
	Overview
		Class (custom fundamental datatypes) & object
		Object get instanciated with class - it is called class instance as well
		Class have data memebers (properties) and functions (method) in it
		Class contain Constructors (basically a member function with the same name as the class itself, 
        and it's used to initialize each of the data members) and one destructor
		by calling destructor we can remove object instances
        Allow us to create fully realized types.
            Drive Constructor
            Allocate memory
            Overload operator
            Contex-Aware Conversion
	Defining class - class.cpp
	Data Members - struct and class are kind of same. Struct have all public data member where as in class you need to define it public.
	Function member - class.cpp
	Constructors and Deconstructors - constructors.cpp
        Constructors are used to initialized and set up object
        Deconstructors are used de-allocate and reset resources when object is destroyed.
	operator overload - with member function and non member function

*/
#include <cstdio> 
#include <string>     // For Constructor and destructor demo work
#include <iostream>   // For Operator overloading 


// a very simple class
class C1 {
    int i = 0;  // data member or properties, which are private so that data is encapsulated.
public:
    void setvalue( int value ) { i = value; }  //interface or methods with implementation part
    int getvalue() { return i; }
};

// STRUCT defaults to public where as CLASS defaults to private. 
// If you just have data members its better to use struct if you have function better to use class
// Created Class Accessors which does same as S1 with accessors defined.
struct S1
{
    /* data */
    int ia; int ib; int ic;
};

class Accessors {
    int ia = 0;
    int ib = 0;
    int ic = 0;
public:
    Accessors ( int a, int b, int c ) : ia(a), ib(b), ic(c) {};
    void seta ( int a ) { ia = a; }
    void setb ( int b ) { ib = b; }
    void setc ( int c ) { ic = c; }
    int geta () const { return ia; }
    int getb () const { return ib; }
    int getc () const { return ic; }
};

// Class Demo with seperation of interface (generally in other file) 
// With demo of const qualified interfaces which are immutable. 
class C2 {
    int i = 0;
public:
    void setvalue( int value );
    int getvalue();
    int getvalue() const;
};
int C2::getvalue() {
    puts("Non Const Func");
    return i;
}

int C2::getvalue() const {
    puts("Const Func");
    return i;
}
void C2::setvalue( int value) {
    i = value;
}

// Constructor & destructor demo work begin.

const std::string unk = "unknown";
const std::string clone_prefix = "clone-";

// -- interface --
class Animal {
    std::string a_type = "";
    std::string a_name = "";
    std::string a_sound = "";
public:
    Animal();   // default constructor
    Animal(const std::string & type, const std::string & name, const std::string & sound);
    Animal(const Animal &); // copy constructor
    ~Animal();  // destructor
    Animal & operator = (const Animal &); // copy operator
    void print() const;
};

// -- implementation --
Animal::Animal() : a_type(unk), a_name(unk), a_sound(unk) {
    puts("default constructor");
}

Animal::Animal(const std::string & type, const std::string & name, const std::string & sound)
: a_type(type), a_name(name), a_sound(sound) {
    puts("constructor with arguments");
}

Animal::Animal(const Animal & a) {
    puts("copy constructor");
    a_name = clone_prefix + a.a_name;
    a_type = a.a_type;
    a_sound = a.a_sound;
}

Animal::~Animal() {
    printf("destructor: %s the %s\n", a_name.c_str(), a_type.c_str());
    a_name = "";
    a_type = "";
    a_sound = "";

}

Animal & Animal::operator = (const Animal & o) {
    puts("assignment operator");
    if(this != &o) {
        a_name = clone_prefix + o.a_name;
        a_type = o.a_type;
        a_sound = o.a_sound;
    }
    return *this;
}

void Animal::print () const {
    printf("%s the %s says %s\n", a_name.c_str(), a_type.c_str(), a_sound.c_str());
}

// Constructor & destructor demo work End.

// Operator Overloading demo begins
class Rational {
    int n = 0;
    int d = 1;
public:
    Rational ( int numerator = 0, int denominator = 1 ) : n(numerator), d(denominator) {};
    Rational ( const Rational & rhs ) : n(rhs.n), d(rhs.d) {};    // copy constructor
    ~Rational ();
    int numerator() const { return n; };
    int denominator() const { return d; };
    Rational & operator = ( const Rational & );
    Rational reduce() const;            // reduce fraction
    std::string string() const;         // return a formatted STL string
    std::string raw_string() const;     // return a non-reduced STL string
    // Member function operator overload 
    // Rational operator + ( const Rational & ) const;
    // Rational operator - ( const Rational & ) const;
    // Rational operator * ( const Rational & ) const;
    // Rational operator / ( const Rational & ) const;
};

Rational & Rational::operator = ( const Rational & rhs ) {
    if( this != &rhs ) {
        n = rhs.numerator();
        d = rhs.denominator();
    }
    return *this;
}

Rational Rational::reduce() const {
    if(n == 0 || d <= 3) return *this;
    for(int div = d - 1; div; --div) {
        if(n % div == 0 && d % div == 0) {
            return Rational(n / div, d / div );
        }
    }
    return *this;
}

std::string Rational::string() const {
    if(d == 0) return "[NAN]";
    if(d == 1 || n == 0) return std::to_string(n);

    int abs_n = abs(n);     // absolute value
    if(abs_n > d) {
        int whole = n / d;
        int remainder = abs_n % d;
        if(remainder) return std::to_string(whole) + " " + Rational(remainder, d).string();
        else return std::to_string(whole);
    }
    else {
        return reduce().raw_string();
    }
}

std::string Rational::raw_string() const {
    return std::to_string(n) + "/" + std::to_string(d);
}

// Member operator overloading for +, -, /, * which have only Right hand side object. LHS is Rational object.
// Rational Rational::operator + ( const Rational & rhs ) const {
//     return Rational((n * rhs.d) + (d * rhs.n), d * rhs.d);
// }
// 
// Rational Rational::operator - ( const Rational & rhs ) const {
//     return Rational((n * rhs.d) - (d * rhs.n), d * rhs.d);
// }

// Rational Rational::operator * ( const Rational & rhs ) const {
//     return Rational(n * rhs.n, d * rhs.d);
// }

// Rational Rational::operator / ( const Rational & rhs ) const {
//     return Rational(n * rhs.d, d * rhs.n);
// }

Rational::~Rational() {
    n = 0; d = 1;
}

// useful for std::cout
std::ostream & operator << (std::ostream & o, const Rational & r) {
    return o << r.raw_string();
}
// Operator Overloading demo Ends.
// Moving +,-,*,/ as non member overloading

Rational operator + ( const Rational & lhs, const Rational & rhs ) {
    return Rational( (lhs.numerator()*rhs.denominator()) + (lhs.denominator()*rhs.numerator()), lhs.denominator()*rhs.denominator() );
}
Rational operator - ( const Rational & lhs, const Rational & rhs ) {
    return Rational( (lhs.numerator()*rhs.denominator()) - (lhs.denominator()*rhs.numerator()), lhs.denominator()*rhs.denominator() );
}
Rational operator * ( const Rational & lhs, const Rational & rhs ) {
    return Rational( lhs.numerator()*rhs.numerator(), lhs.denominator()*rhs.denominator() );
}
Rational operator / ( const Rational & lhs, const Rational & rhs ) {
    return Rational( lhs.numerator()*rhs.denominator(), lhs.denominator()*rhs.numerator() );
}
int main() {
    int i = 47;
    C1 o1;
    
    o1.setvalue(i);
    printf("value is %d\n", o1.getvalue());

    S1 simpleStruct = {1,2,3};
    printf("Struct public data members A: %d B: %d C: %d \n", simpleStruct.ia, simpleStruct.ib, simpleStruct.ic);

    Accessors aa(1, 2, 3);
    printf("ia is %d, ib is %d, ic is %d\n", aa.geta(), aa.getb(), aa.getc());

    int iC2 = 40; 
    C2 obj1;
    obj1.setvalue(iC2);
    const C2 obj2 = obj1;
    printf("value is %d\n", obj1.getvalue());
    printf("value is %d\n", obj2.getvalue());

// Constructor and Destructor demo.
    Animal a;
    a.print();
    
    const Animal b("goat", "bob", "baah");
    b.print();
    
    const Animal c = b;
    c.print();
    
    a = c;
    a.print();
    
    puts("end of Work So destruct or it will be destructed at end of main");
    
    a.~Animal();
    b.~Animal();
    c.~Animal();

// Rational work.

    Rational aR = 7;        // 7/1
    std::cout << "aR is: " << aR << std::endl;

    Rational bR(25, 15);    // 5/3
    std::cout << "bR is: " << bR << std::endl;

    Rational cR = bR;        // copy constructor
    std::cout << "cR is: " << cR << std::endl;

    Rational dR;            // default constructor
    std::cout << "dR is: " << dR << std::endl;

    dR = cR;                // assignment operator
    std::cout << "dR is: " << dR << std::endl;

    Rational & eR = dR;     // reference
    dR = eR;                // assignment to self!
    std::cout << "eR is: " << eR << std::endl;

    std::cout << std::endl;
    std::cout << "dR is " << dR.string() << std::endl;

    std::cout << std::endl;
    std::cout << aR << " + " << bR << " = " << aR + bR << std::endl;
    std::cout << aR << " - " << bR << " = " << aR - bR << std::endl;
    std::cout << aR << " * " << bR << " = " << aR * bR << std::endl;
    std::cout << aR << " / " << bR << " = " << aR / bR << std::endl;

// Non Member overload demo
    std::cout << 14 << " + " << aR << " = " << 14 + aR << std::endl;
    std::cout << 14 << " - " << aR << " = " << 14 - aR << std::endl;
    std::cout << 14 << " * " << aR << " = " << 14 * aR << std::endl;
    std::cout << 14 << " / " << aR << " = " << 14 / aR << std::endl;


    return 0;
}
