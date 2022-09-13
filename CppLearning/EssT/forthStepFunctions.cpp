#include <cstdio>
#include "funch.h" // Common practice to do all declaration in header file. and implementation somewhere else.
#include <string>  // To work on string object for passByRefBig.
#include <cstdarg> // To work on Variadic args. 

// Functions are fundamental to C++,
// Functions are basis of class methods
// It allows you to generalize and modularize your code by creating containers for logical subsets of code.
// Argument can pass by value, and callers copy remains same.
void passByValue(int a) {
    ++a;
    printf("value of a: %d\n", a);
}
// Pass by refrence carries dangers if not implemented properly
void passByRef(int *p) {
    ++(*p);  //We need to deref pointer to do increment 
}
// Very common in CPP, you can use CONST modifier so that function dont change values. 
// Its used to make sure we dont copy larger value in stack
void passByRefImplicit(int &p) {   
    ++p;
}
void passByRefBig(const std::string & s) {
    printf("Value: %s\n",s.c_str());
}
// Even return values are sent to stack so be sensitive to so avoid it via ref. 
const std::string & returnByRef() {
    const static std::string s = "This is returned from returnByRef" ; 
    return s;
}

// Func Signature 
// The return type, the name of the function, and the types of the function arguments are all combined to form the function signature
// This is called function overloading as based on function signature compiler selects functions
long volume( long a, long b, long c) {
    return a*b*c;
}
double volume(double r, int h) {
    return 3.14159 * r * r * h;
}
double volume( double a ) {
    return a * a * a;
}

// Variadic args. 
// first argument -- int count of remaining args
// remaining args -- doubles for average
double average(const int count, ...)
{
    va_list ap;  // va_list is type def
    int i;
    double total = 0.0;
    
    va_start(ap, count);
    for(i = 0; i < count; ++i) {
        total += va_arg(ap, double);
    }
    va_end(ap);
    return total / count;
}

// message works like printf, format plus args
// sends newline after message
int message(const char * fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int rc = vfprintf(stdout, fmt, ap);
    puts("");
    va_end(ap);
    return rc;
}

// Example function: 
// For each recursion mem allocated for parameters and local variable, return value annd for other function called overhead etc on stack  
// Buffer overflow can occur is there are many recursions
unsigned long factorial(unsigned long n) {
    if (n<2) return 1;
    return factorial(n-1)*n;
}
// Without Recursion
unsigned long nonRecursionFact(unsigned long n) {
    unsigned long rc = n;
    while (n>1){
       rc *= --n;
    }
    return rc;
}

//Example of declaration and writing it later 
void func();

// Varibles declared in function defaults to automatic storage. Other storage options are also available. 
// Automatic storage is not carried over after invocation and stays in stack.
// You can specify it to store it in static memory so it gets saved there for all invocations.
void funcStorage() {
    static int a = 1; int b = 1;
    printf("static a: %d, auto b: %d\n",a++,b++);
}

int main()
{
    puts("Hello, World!");
    puts("this is main()");
    func();
    funch();
    int factorialTest = 5, passByTest = 2;
    printf("Factorial of %d :  %ld\n",factorialTest,factorial((long int)factorialTest));
    passByValue(passByTest); // value of passByTest doesn't change
    printf("passByValue: %d\n", passByTest);
    passByRef(&passByTest);  //Pass by ref and we may have side effects, you pass pointer to passByTest variable.
    printf("passByRef: %d\n", passByTest);
    passByRefImplicit(passByTest);
    printf("passByRefImplicit: %d\n", passByTest);
    std::string s = "This is very long object string which is available for string header and we pass it by reference to avoid writing to much on stack";
    passByRefBig(s);
    const std::string sR = returnByRef();
    printf("sR: %s\n", sR.c_str());

//Signature test
    long a = 2; long b = 3; long c = 4;
    printf("Volume of cuboid l=%ld, b=%ld, h=%ld is (Long Int Return) : %ld\n",a,b,c,volume(a,b,c));
    double r = 1.5; int h = 7;
    printf("Volume of cylinder radius=%.2lf, height=%d (Double Return) : %lf\n",r,h,volume(r,h));
    printf("cube of %.2lf length (double return) : %.2lf\n", r, volume(r));

//Function variable storage test
    funcStorage();
    funcStorage();
    funcStorage();
    funcStorage();

//Function Pointers - its ambiguous not much recommended. See JumpTable.cpp
    void (*pFunc)() = func;
    (*pFunc)();
    long int uLintA = 6;
    unsigned long (*pFact)(unsigned long) = factorial;
    printf("Function Pointer demo: %ld\n", (*pFact)(uLintA));

// Variable number of args.
    message("This is a message");
    message("Average: %lf", average(5, 25.0, 35.7, 50.1, 127.6, 75.0));

//Non recursive function call
    printf("Factorial of %d :  %ld\n",factorialTest,nonRecursionFact((long int)factorialTest));

    return 0;
}

void func()
{
    puts("this is func()");
}
void funch()
{
    puts("this is funch() declared in funch.h and implemented here.");
}