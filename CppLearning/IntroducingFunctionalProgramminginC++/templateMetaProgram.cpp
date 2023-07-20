/*
Template Metaprogramming or TMP is a form of C++ programming. 
TMP is a Turing complete, functional programming language built-in to C++. 
TMP variables are always immutable. 
TMP doesn't have loops, so we must use recursion. 
TMP doesn't have branching, so we use specialization.

The Standard Template Library is a subset of the C++ Standard Library. 
To make the library flexible and able to work with a wide variety of types, 
it is implemented using both template metaprogramming and generic programming. 
The STL consists of four components, algorithms, containers, functions, and iterators. 
Before you write a new algorithm, you should check here first to see if it already exists in the STL. 
One anti-pattern you should avoid in your code is raw loops. Odds are that there are already an STL algorithm which provides the same function and is more performant and more thoroughly debugged. 
Remember the STL is your friend.

Hana provides support for heterogeneous collections in tuples, and it has a large number of functional methods
*/

#include <iostream>
#include <string>
#include <vector>
#include <boost/hana.hpp>
using namespace std;

// instantiate at compile time - generic Programing - another word is that create function in runtime
template<typename T> T cube(const T& value) {
    return value * value * value;
};

// No return in TMP - toCube is immutable. -- everything done at compile time 
template<int toCube> struct Cube {
    enum {
        value = toCube * toCube * toCube
    };
};

//Factorial using recursive 
int factorial(const int input, const int sum = 1){
    if(input>1){
        return factorial(input - 1, sum * input);
    }
    return sum;
}

//Factorial using TMP
template<int input, int sum = 1> 
struct Factorial : Factorial<input - 1, input * sum>
{
};
//Specialization with factorial<1, sum> will take precedence over generic template thats how it will break recursion by invoking specialized Template.
template<int sum> 
struct Factorial<1, sum>
{
    enum {
        value = sum
    };
};

//Fibonacci via TMP
template<int n> struct fib { 
    enum { value = fib<n - 1>::value + fib<n - 2>::value };
};
template<> struct fib<0> {
    enum { value = 0 };
};

template<> struct fib<1> {
    enum { value = 1 };
};

//Hana
namespace hana = boost::hana;
using namespace hana::literals;

struct Truck {
    std::string name;
    double bed_length;
};
struct Car {
    string name;
};
struct Motorcycle {
    string name;
};

int main() {
    cout << "8 cubed = " << cube(8) << endl;
    //Scope resolution happens compile time 
    cout << "5 cubed = " << Cube<5>::value << endl;  

//Factorial via TMP and generic demo.
    cout << "5! = " << factorial(5) << endl;
    cout << "Factorial<4> " << Factorial<4>::value << endl;
    cout << "Factorial<5> " << Factorial<5>::value << endl;

//TMP fibonacci
    cout << "fib(0) = " << fib<0>::value << endl;
    cout << "fib(1) = " << fib<1>::value << endl;
    cout << "fib(2) = " << fib<2>::value << endl;
    cout << "fib(3) = " << fib<3>::value << endl;
    cout << "fib(4) = " << fib<4>::value << endl;
    cout << "fib(11) = " << fib<11>::value << endl;
    cout << "fib(12) = " << fib<12>::value << endl;
    cout << "fib(45) = " << fib<45>::value << endl;

//Hana demo.
    auto vehicles = hana::make_tuple(Truck{"F-150",8.5}, Car{"Volt"}, Motorcycle{"Ninja"});
    auto has_bed_length = hana::is_valid(
        [](auto &&x) -> decltype((void) x.bed_length){}
    );
    auto trucks = hana::filter(vehicles, has_bed_length);
    auto nontrucks = hana::filter(vehicles, hana::compose(hana::not_, has_bed_length));
    
    hana::for_each(trucks, [](auto &vehicle) {
        cout << "Truck = " << vehicle.name << ", bed length = " << vehicle.bed_length << endl;
    });
    hana::for_each(nontrucks, [](auto &vehicle){
    cout << "Vehicle = " << vehicle.name << endl;
    });
    return 0;
}