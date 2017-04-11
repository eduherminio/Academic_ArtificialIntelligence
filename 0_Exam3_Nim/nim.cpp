#include <iostream>
#include "header/nim.h"

int main()
{
  std::cout<<"It compiles, that's something"<<std::endl;
    
  // std::vector<int> a{1,2,3,4};
  // Nim nim(a);
  Nim nim({3,6,7,8});

  auto hijos=nim.expandir();
  nim.muestra();

  for(auto x:hijos)
    x.muestra();
}
