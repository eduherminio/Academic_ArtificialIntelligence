#ifndef NIM_H_INCLUDED
#define NIM_H_INCLUDED
#include <vector>
#include <iostream>
#include <cstdlib>

class Nim
{
public:
   Nim(std::vector<int> v);
   std::vector<Nim> expandir();
   void muestra();

private:
   std::vector<int> v_pilas;
};

#endif // NIM_H_INCLUDED
