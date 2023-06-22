/*
Arity --> number of argument function takes.
std::bind 
1. Manipulate a function and its parameters
2. Reorder the function's arguments
3. bind values to arguments 

Std::function also comes from the functional header. 
It is a wrapper for invokable objects which includes functions, function objects, also known as functors, and lambdas. 
We can also store wrapped invokable objects in a vector of function objects. 

Lambdas were introduced to the language with C++11, they are unnamed function objects which can create a closure over the invoking scope
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <functional>
using namespace std;

auto greter_than(int first, int second){
    return first >= second;
}

void demoFunction(){
  cout << "Called demoFunction" << endl;
}

void adder(int a, int b){
  cout << "Called adder, a + b = " << a+b << endl;
}

class functor {
public:
  void operator()() const {
    cout << "Called functor" << endl;
  }
};

auto addCurry = [](auto a) {
  return [a](auto b) {
    return [a, b] (auto c){
      return a+b+c;
    };
  };
};

auto incrementer = []() {
  auto increment = 0;
  return [increment]() mutable {
    return increment++;
  };
};

auto continuousAdd = [](int initial, int addBy){
  auto total = initial;
  return [total, addBy]() mutable {
    total += addBy;
    return total;
  };
};

int main(){
    vector<int> ages{9, 20, 13, 4, 5, 6, 10, 28, 19, 15, 60, 23, 47, 12, 19, 99};
    int over21 = 0;
    for (int age : ages) {
        if (age >= 21) {
        over21++;
        }
    }
    cout << "Number over 21 = "<< over21 << endl;

    auto num_over21 = count_if(ages.begin(), ages.end(), bind(&greter_than, placeholders::_1, 21));

    cout << "New Number over 21 = "<< num_over21 << endl;

//std::function demo
    vector<function<void()>> funcs;
    funcs.push_back(demoFunction);
    functor functorInstance;
    funcs.push_back(functorInstance);
    funcs.push_back([](){cout << "Called anonymous lambda "<< endl;});
    funcs.push_back(bind(&adder, 10, 11));

    for(auto &f: funcs){
        f();
    }

// currying 
    auto added1 = addCurry(1);
    auto added2 = added1(10);
    auto addResults = added2(100);
    cout << "results: " << addResults << endl; 
    
    // We dont need to wait on return function.
    auto allAtOnce = addCurry(990000)(9900)(99);
    cout << "All results: " << allAtOnce << endl;

// Lambda usage example.
    auto myInc = incrementer();
    cout << "myInc = " << myInc() << endl;
    cout << "myInc = " << myInc() << endl;
    cout << "myInc = " << myInc() << endl;
    cout << "myInc = " << myInc() << endl;

//challenge work
  auto x = continuousAdd(1000, 10);
  cout << x() << endl;
  cout << x() << endl;
  cout << x() << endl;
  cout << x() << endl;
  cout << x() << endl;

    return 0;
}