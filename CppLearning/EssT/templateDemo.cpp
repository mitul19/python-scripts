/*
C++ templates are marvelously simple and powerful. 
This is the C++ feature that supports generic programming. 
Generic programming refers to code that works independent of type while C++ is a strongly typed language, 
there's still great benefit in being able to write functions and classes that are type agnostic, that is, 
they operate on objects without concern for the type of these objects. 
Because C++ supports defining your own types through classes and operator overloading, 
it is possible to do a great deal of generic programming in templates, 
while leaving the implementation details to the classes and operators. 
Template declarations look just like normal function or class declarations with one distinction. 
They are preceded by the template keyword, and a set of type identifiers. 
These type identifiers are used as placeholders by the template code to be replaced during compilation with actual types. 
When a function or class is used from a template, the compiler generates a specialization specifically suited to the types 
identified in the instantiation. This specialization is generated at compile time, and one specialization is created for each 
combination of data types for each template. 
Templates are widely used in the C++ standard library, which is why parts of the library are commonly called the standard template library
The generic nature of templates makes them a perfect fit for use with container classes. 
Template programming is not entirely without its downsides, there are some issues you'll need to be aware of. 
    Because the compiler must generate specializations for every type context of a template, the amount of code to support that template can grow rapidly with use. 
    Compilers tend to have a difficult time generating sensible error messages with templates, so debugging can be challenging. 
    Because templates tend to live in header files, changes to code with templates can lead to recompilation of larger portions of your code than would otherwise be necessary. 

C++ templates are a powerful feature that is also simple to implement and support. 
They have great advantages over generic programming solutions, including preprocessor macros and they're widely used to implement containers and other generic objects in the C++ standard library. 
*/
#include <iostream>
#include <string>
#include <exception>  

template <typename T>
T maxof ( T a, T b ) {
    return ( a > b ? a : b );
}

// Template class implementation
// simple exception class
class BWEx : public std::exception {
    const char * msg;
    BWEx();    // no default constructor
public:
    explicit BWEx(const char * s) throw() : msg(s) { }
    const char * what() const throw() { return msg; }
};

// simple fixed-size LIFO stack template
template <typename T>
class Stack {
    static const int defaultSize = 10;
    static const int maxSize = 1000;
    int S_size;
    int S_top;
    T * stackPtr;
public:
    explicit Stack(int s = defaultSize);
    ~Stack() { if(stackPtr) delete[] stackPtr; }
    T & push( const T & );
    T & pop();
    bool isEmpty() const { return S_top < 0; }
    bool isFull() const { return S_top >= S_size - 1; }
    int top() const { return S_top; }
    int size() const { return S_size; }
};

// Stack<T> constructor
template <typename T>
Stack<T>::Stack ( int s ) {
    if(s > maxSize || s < 1) throw BWEx("invalid stack size");
    else S_size = s;
    stackPtr = new T[S_size];
    S_top = -1;
}

template <typename T>
T & Stack<T>::push ( const T & i ) {
    if(isFull()) throw BWEx("stack full");
    return stackPtr[++S_top] = i;
}

template <typename T>
T & Stack<T>::pop () {
    if(isEmpty()) throw BWEx("stack empty");
    return stackPtr[S_top--];
}

// Challenge 
template <typename T>
T factorial (T n) {
    T rc = n;
    while (n > 1)
    {
        rc *= --n;
    }
    return rc;
}

int main() {
    std::cout << maxof<int>( 7, 9 ) << std::endl;
    std::cout << maxof<const char *>("b","a") << std::endl;  //comparing char pointer value.
    std::cout << maxof<std::string>("a","b") << std::endl;  //STRING class used from header and string comparision 
    std::cout << maxof( 7, 9 ) << std::endl;  // Template argument deduction takes care 

// Template Class Implementation demo
    try {

        Stack<int> si(5);
        
        std::cout << "si size: " << si.size() << std::endl;
        std::cout << "si top: " << si.top() << std::endl;
        
        for ( int i : { 1, 2, 3, 4, 5 } ) {
            si.push(i);
        }
        
        std::cout << "si top after pushes: " << si.top() << std::endl;
        std::cout << "si is " << ( si.isFull() ? "" : "not " ) << "full" << std::endl;
        
        while(!si.isEmpty()) {
            std::cout << "popped " << si.pop() << std::endl;
        }

        Stack<std::string> ss(5);
        
        std::cout << "ss size: " << ss.size() << std::endl;
        std::cout << "ss top: " << ss.top() << std::endl;
        
        for ( const char * s : { "one", "two", "three", "four", "five" } ) {
            ss.push(s);
        }
        
        std::cout << "ss top after pushes: " << ss.top() << std::endl;
        std::cout << "ss is " << ( ss.isFull() ? "" : "not " ) << "full" << std::endl;
        
        while(!ss.isEmpty()) {
            std::cout << "popped " << ss.pop() << std::endl;
        }

    } catch (BWEx & e) {
        std::cout << "Stack error: " << e.what() << std::endl;
    }

// Factorial demo
    printf("Integer demo: %d\n", factorial<int>(5));
    printf("float demo: %0.2f\n", factorial<float>(7));
    long long unsigned int llui = 15;
    printf("%lld! is %lld\n", llui, factorial(llui));
    long double ld = 25;
    printf("%.3Lf! is %-4.10Lg\n", ld, factorial(ld));


    return 0;
}