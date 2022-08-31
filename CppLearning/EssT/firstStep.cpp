#include <cstdio>
#include <iostream> // STD template 

//Struct example
struct firstStepStruct
{
    int i;
    double d;
    const char * s;
};

//Function example
void func(int i) {
    printf("this is func(%i)\n",i);
}

// Simple Class example:
// Members defaults to private in class where as they default to public in Struct
// public function member servers as interface and allows you to access private member. So it can encapsulate the private integer i.
class C_firstStep {
    int i = 0;
public:
    void setvalue( int value ) { i = value; }
    int getvalue() { return i; }
};

//Print is differently 
const char Exercise_string[] = "This is a null-terminated string.";


int main()
{

// CH1: Intro
    /*
    Distinct parts of c++
        C langauge  - Basis 
        C preprocessor - 
        Classes and objects  - object oriented Programming
        Templates - Generic programming
        Standard Template Library - Part of c++ standard  
    Compiled langauge : Source code -> preprocessor -> Compiler -> linker -> run 
    */
    puts("Hello, World!");
    // 	std::cout is part of standard template it requires STL, it has unique syntax, we will use puts and printf which is cleaner. 
    // cout is actually a class, it loads bitwise left shift "<<" operator to stream of char to terminal 
    // cout takes in STL related code when you compile and it take extra memory and size.
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Hello, World!" << 2 * 7 << " another string" << std::endl;

    
//CH2: Basic Syntax 
    /*
    Functions, Statements [ends with semicolon ;] and expressions [returns a value]
	varible must be decalred before it is used
    white spaces are ignored, but it will be taken up for function, variable etc declaration
	statement is unit of code and terminated with semicolon
    Identifiers
		26 ISO Latin alphabets (both upper and lower) + 10 western Arabic numerals + ASCII underscore _ 
		73 reserved keywords and 11 alternative tokens
		case sensitive 
		can be of any length but first 63 chars checked for uniqueness anf first 31 chars for external indentifiers 
		initial underscrore _privateIdentifier (global names reserved) and more that one underscrore __systemLevelIdenifiers
	Variable
		Strongly typed - token representing variable represent both its value and its type.
		qualifier can added to make is non changing. 
    */

    int x;
    x = 42;
    printf("x is %d\n", x);
    printf("x is %d\n", x = 73);

    /*
	pointers and references
		pointer to a value, as opposed to carrying value it self.
		always const references so that you dont modify variables by mistake. 
		c doesnt have reference only cpp have it.
    */
    int y = 42;
    int * ip = &x;
    printf("The value of x is %d\n", x);
    printf("The value of y is %d\n", y);
    printf("The value of *ip is %d\n", *ip);

    /*
	primitive array or c type array 
		defined as part of langauge
		array is fixed size container with same data types 
			int ia[5]; 
			ia[0] = 1; or *ia = 1; 
			// now you can use integer pointer, you can increment pointer and it will point to next element as they know size of datatype it has. 
			int *ip = ia; ++ip; *ip = 3; *(++ip) = 4;
			//declare and assigns cpp11 onwards 
			int ia[5] = {1,2,3,4,5}
    */
    int array[] = { 1, 2, 3, 4, 5 };
    for(int i : array) {
        printf("%d ", i);
    }
    puts("");

    /*
	primitive string or c-string 
		primitive array is guaranteed to be stored contiguosly and terminated with null character 
    */
    char sa[] = {'s','t','r','i','n','g',0};
    char sb[] = "string";
    printf("s is %s\n",sa);
    printf("s is %s\n",sb);
    char sc[] = "string";
    for(int i = 0; sc[i] != 0; ++i) {
        printf("char is %c\n", sc[i]);
    }
    for(char * cp = sc; *cp != 0; ++cp){
        printf("char is %c\n", *cp);
    }

    /*
    Conditional Statements    - O -> FALSE 
    */
    printf("Value of %d\n",x<y);
    if(x<y) puts("condition is true");
    else puts("condition is false");

    const int iONE = 1;
    const int iTWO = 2;
    const int iTHREE = 3;
    const int iFOUR = 4;
    
    int xx = 3;
    
    switch(xx) {
        case iONE:
            puts("one");
            break;
        case iTWO:
            puts("two");
            break;
        case iTHREE:
            puts("three");
            break;
        case iFOUR:
            puts("four");
            break;
        default:
            puts("default");
            break;
    }

    int arrayWhile[] = { 1, 2, 3, 4, 5 };
    int i = 0;
    
    while(i < 5) {
        if(i == 4) break;
        if(i == 2) { ++i; continue; }
        printf("element %d is %d\n", i, arrayWhile[i]);
        ++i;
    }
    int j = 0;
    do {
        printf("element %d is %d\n", j, arrayWhile[j]);
        ++j;
    } while (j<5);

    int arrayFor[] = { 1, 2, 3, 4, 5 };

    for(int i = 0; i < 5; ++i) {
        printf("element %d is %d\n", i, arrayFor[i]);
    }
    // Look at c-string example for other FOR loop work. 
    // Range based for loop , knows size of array 
    int arrayRange[] = { 1, 2, 3, 4, 5 };
    for(int i : arrayRange) {
        printf("i is %d\n", i);
    }
    //for c-string 
    char sRange[] = "sRange";
    for (char c : sRange) {
        if (c == 0 ) break; //Null terminator check 
        printf("c is %c\n",c);
    }

    //Struct is aggregated variable its a way of collecting a number of disparate varibles.
    firstStepStruct s1 = { 3, 47.9, "string one" };
    printf("s1: %d, %f, %s\n", s1.i, s1.d, s1.s);

    
    //Function is standlone block of code, it may and may not have parameters were returns value which makes not distinction between function and procedure.
    //defination include return type, parameter are optional
    func(47);

    // CLASS is building block for objects in OOP.
    int ci = 47;
    C_firstStep o1, o2, o3;
    o1.setvalue(ci); o2.setvalue(ci*3);o3.setvalue(ci/2);
    printf("value is %d\n", o1.getvalue());
    printf("value is %d\n", o2.getvalue());
    printf("value is %d\n", o3.getvalue());

    //Challenge 
    int challengeCount = 0;
    for (char c : Exercise_string) {
        if (c == 0) break;
        ++challengeCount;
    }
    printf("The number of characters is: %d using for as char array\n", challengeCount);
    
    for (challengeCount=0; Exercise_string[challengeCount]; ++challengeCount);
    printf("The number of characters is: %d using for loop\n", challengeCount);

    challengeCount=0;
    while (Exercise_string[challengeCount]) 
    {
        ++challengeCount;
    }
    printf("The number of characters is: %d using while loop\n", challengeCount);




    return 0;
}