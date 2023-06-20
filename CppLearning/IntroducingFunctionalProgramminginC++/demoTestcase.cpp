/* Multi line comment 
Introducing Functional Programming in C++ : Troy Miles
1. Pure functions are easier to understand
2. Uncomplicated debugging and testing
3. Mutlithreading is achievable 

immutable variables (constant)
recursion over loops
we avoid makinng changes to program state 
Expressions preferred over stattement 
Currying manages how arguments are passed to functions
*/

//pre processor directives

// 01_04 Unit Testing FP


// Tells Catch to provide a main()
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// a pure function without side effects
int fibonacci(int n) {
  if (n <= 1) {
    return (n);
  }
  return (fibonacci(n - 1) + fibonacci(n - 2));
}

TEST_CASE("Fibonacci series", "[fibonacci]") {
  REQUIRE(fibonacci(0) == 0);
  REQUIRE(fibonacci(1) == 1);
  REQUIRE(fibonacci(2) == 1);
  REQUIRE(fibonacci(3) == 2);
  REQUIRE(fibonacci(4) == 3);
  REQUIRE(fibonacci(5) == 5);
  REQUIRE(fibonacci(12) == 144);
}