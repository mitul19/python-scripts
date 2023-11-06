/*
mpatel@blr-mpd67 git % git clone --recursive https://github.com/ReactiveX/RxCpp.git;cd RxCpp
Cloning into 'RxCpp'...
remote: Enumerating objects: 12717, done.
remote: Counting objects: 100% (376/376), done.
remote: Compressing objects: 100% (232/232), done.
remote: Total 12717 (delta 204), reused 236 (delta 108), pack-reused 12341
Receiving objects: 100% (12717/12717), 61.60 MiB | 12.31 MiB/s, done.
Resolving deltas: 100% (7075/7075), done.
Submodule 'ext/catch' (https://github.com/philsquared/Catch.git) registered for path 'ext/catch'
Cloning into '/Users/mpatel/git/RxCpp/ext/catch'...
remote: Enumerating objects: 38101, done.        
remote: Counting objects: 100% (919/919), done.        
remote: Compressing objects: 100% (432/432), done.        
remote: Total 38101 (delta 571), reused 770 (delta 487), pack-reused 37182        
Receiving objects: 100% (38101/38101), 28.45 MiB | 11.15 MiB/s, done.
Resolving deltas: 100% (26949/26949), done.
Submodule path 'ext/catch': checked out '216713a4066b79d9803d374f261ccb30c0fb451f'
mpatel@blr-mpd67 RxCpp %

*/

#include "/Users/mpatel/git/RxCpp/Rx/v2/src/rxcpp/rx.hpp"

namespace Rx {
  using namespace rxcpp;
  using namespace rxcpp::sources;
  using namespace rxcpp::operators;
  using namespace rxcpp::util;
}
using namespace Rx;

#include <iostream>

int main() {
  std::vector<int> ages{9, 20, 13, 4, 5, 6, 10, 28, 19, 15, 60, 23, 47, 12, 19, 99};
  auto values = rxcpp::observable<>::iterate(ages).
    filter([](int age) {return age >= 21;}).
    count().
    subscribe(
        [](int count){std::cout << "Numbbers over 21 = " << count << std::endl;},
        [](){std::cout << "OnCompleted" << std::endl;}
        );
  auto values_1 = rxcpp::observable<>::iterate(ages).
    filter([](int age){return age >= 13 && age <= 19;}).
    subscribe(
      [](int age){std::cout << age << std::endl;},
      [](){std::cout << "OnCompleted" << std::endl;}
    );
  return 0;
}