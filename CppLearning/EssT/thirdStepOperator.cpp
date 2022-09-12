#include <cstdio>
#include <cstdint>  //for uint8_t varible. 
#include <new>  //New Delete work 
#include <typeinfo> //for typeid work

void printp8(uint8_t *p) {
    printf("pointer is %p, value is %d\n", p, *p);
}

void printp16(uint16_t *p) {
    printf("pointer is %p, value is %d\n", p, *p);
}

const char * u8_to_bstr(const uint8_t & u8) {
    static char s[9];   // space for 8-char string
    s[8] = 0;           // terminate string
    char * sp = s;
    for (uint8_t xbit = 0b10000000; xbit > 0; xbit >>= 1) {
        *(sp++) = ((u8 & xbit) == xbit) ? '1' : '0';
    }
    return s;
}
const long int count = 1024;

struct A { int x; };
struct B { int x; };
A a1;
A a2;
B b1;
B b2;

int main()
{
    puts("Hello, World!");
    int x = 47; //assignment opertor -copying right side to left 
    int y = 5; 
    // x = y; 
    int z = x % y; // remainder will be copied to z 
    printf("x is %d\n", x);
    printf("y is %d\n", y);
    printf("z is %d\n", z);
    
// compound operator, y is evaluated once, it may make difference when using it for objects 
// but in general they are convinient, safe and more efficient.
    y *= x; 
    printf("y is %d\n", y);

//increment and decrement unary operator 
    printf("x is %d\n", ++x); //pre increment
    printf("x is %d\n", ++x);
    printf("x is %d\n", x--); //post decrement
    printf("x is %d\n", --x);
    printf("x is %d\n", --x);

//This unary increment and decrement work via pointer
//unit8_t will require one byte where as unit16_t will require 2 bytes.
//preincrement is slightly more efficient compare to post as it dont require to make copy
    uint8_t arr8[5] = { 1, 2, 3, 4, 5 };
    uint8_t *p8 = arr8;
    printp8(p8++);
    printp8(p8++);
    printp8(p8++);

    uint16_t arr16[5] = { 1, 2, 3, 4, 5 };
    uint16_t *p16 = arr16;
    printp16(p16++);
    printp16(p16++);
    printp16(p16++);

//Comparison - relational operator
//They return logical value 0 and 1. 
//They work on any scale or type.
    if (x == y ) puts("TRUE");
    else puts("FALSE");
    printf("logical value is %d\n",x ==y);
    if (x <= y ) puts("TRUE");
    else puts("FALSE");
    printf("logical value is %d\n",x <=y);

// Boolean Logical operator  
// XOR is not implemented it is superfluous,  you can use aB != bB
    bool aB = true;
    bool bB = false;
    printf("aB is %d\n", aB);
    printf("bB is %d\n", bB);
    printf("size of %zd\n",sizeof(aB)*8); //to print bit requirement of 8 bit
    if (aB && bB) puts(" && True");
    else puts("&& False");
    if (aB || bB) puts("|| True");
    else puts("|| False");
    if (!bB) puts(" ! True");
    else puts("! False");

// Bitwise operators 
// Standard Printf doesnt provide so u8_to_bstr() written here   
    uint8_t aBit = 5;
    uint8_t bBit = 10;
    uint8_t cBit = aBit | bBit;
    
    printf("x is %s\n", u8_to_bstr(aBit));
    printf("y is %s\n", u8_to_bstr(bBit));
    printf("OR: result is %s\n", u8_to_bstr(cBit));
    printf("NOT: result is %s\n", u8_to_bstr(~cBit)); // NOT operator 
    printf("SHIFT: result is %s\n", u8_to_bstr(bBit<<2)); // shift operator 
    printf("AND: result is %s\n", u8_to_bstr(aBit & bBit)); // AND operator 
    printf("XOR: result is %s\n", u8_to_bstr(aBit ^ bBit)); // XOR operator 

//Ternary Operator Example
    const char * sTernary =  x > y ? "yes" : "No"; 
    puts(sTernary);

//Dynamic Memory Operator: New and Delete
    printf("allocate space for %lu long int at *ip with new\n", count);
    
    long int * ip; // allocate array
    try {
        ip = new long int [count];
    } catch (std::bad_alloc & ba) {
        fprintf(stderr, "Cannot allocate memory (%s)\n", ba.what());
        return 1;
    }
    for( long int i = 0; i < count; i++ ) {
        ip[i] = i; // initialize array
    }
    delete [] ip; // deallocate array else mem leaks and vulnerabilities  
    puts("space at *ip deleted");

    // With out using try catch block so we need to tell std::nothrow in new. 
    // Try and catch is recommended way
    long int * ipNothrow;  
    ipNothrow = new(std::nothrow) long int [count];
    if(!ip) {
        fputs("Can't allocate memory\n", stderr);
        return 1;
    }
    for( long int i = 0; i < count; i++ ) {
        ipNothrow[i] = i; // initialize array
    }
    delete [] ipNothrow; // deallocate array else mem leaks and vulnerabilities  
    puts("space at *ipThrow deleted");


// Type Cast 
// Implicit conversion (int to long long int) promotion is okay but Long long int to int is not allowed 
// So you can tell comlier to cast. 
    int xC = 5;
    long long int yC;
    const char * sC = "String"; //you can't cast other type like int to string, only compatible types can be casted 
    yC = xC; // implicit , but you cant do xC=yC; 
    printf("xC is %d\n",xC);
    printf("yC is %lld\n",yC);
    printf("Cast (int) is %d", (int) yC);

//Size of operator 
    int xS = 5;
    size_t yS = sizeof xS; //TypeDef 
    printf("Size of x is %zd\n", yS);
    printf("Size of y is %zd\n", sizeof(int16_t));
    struct sOfStruct
    {
        int a; int b; int c;
        char x; char d; char e;
        long int f; long long int g;
    };
    printf("Size of Struct is %zd\n", sizeof(sOfStruct));

//typeid 

    if(typeid(a1) == typeid(B)) puts("same");
    else puts("different");
    printf("Type is %s\n", typeid(B).name());

//Prime no solution
    puts("Prime Numbers(1-100): ");
    bool primeFlag;
    for(unsigned int num = 2; num < 100; ++ num){
        primeFlag = true;
        for(unsigned int factor = 2; factor < num; ++factor){
            if(num%factor == 0 ) primeFlag = false;
            break;
        }
        if(primeFlag) printf("%d ",num);
    }
    puts("");

    return 0;
}