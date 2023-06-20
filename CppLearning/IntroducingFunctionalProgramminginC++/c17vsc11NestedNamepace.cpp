/*

If you build with c++14 then warning

    Starting build...
    /usr/bin/clang++ -fdiagnostics-color=always -std=c++14 -Wall -g /Users/mpatel/git/mitul19/python-scripts/CppLearning/IntroducingFunctionalProgramminginC++/c17vsc11NestedNamepace.cpp -o /Users/mpatel/git/mitul19/python-scripts/CppLearning/IntroducingFunctionalProgramminginC++/c17vsc11NestedNamepace
    /Users/mpatel/git/mitul19/python-scripts/CppLearning/IntroducingFunctionalProgramminginC++/c17vsc11NestedNamepace.cpp:3:12: warning: nested namespace definition is a C++17 extension; define each namespace separately [-Wc++17-extensions]
    namespace A::B::C {
            ^~~~~~
                { namespace B { namespace C
    1 warning generated.

    Build finished with warning(s).

*/

#include <iostream>

namespace A::B::C {
    int i;
}

int main() {
    A::B::C::i = 42;
    std::cout << "Nested namespaces are available: " << A::B::C::i << std::endl;
    return 0;
}