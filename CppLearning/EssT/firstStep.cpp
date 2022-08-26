#include <cstdio>
#include <iostream> // STD template 



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
    std::cout << "Hello, World!" << std::endl;

    
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
		primitive array is guaranteed to be stored contiguosly 
    */
    /*
	Conditional Statement 
	while.cpp edited with details
    */
    return 0;


}