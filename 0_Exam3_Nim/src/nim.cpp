#include "../header/nim.h"

Nim::Nim(std::vector<int> v)
{
  v_pilas=v;
}
std::vector<Nim> Nim::expandir()
{
  // TO-DO
    std::vector<Nim> hijos;

    for(int i=0; i<v_pilas.size(); ++i)
    {
      int pila_vieja= v_pilas[i];
      for(int cubitos_quitados=1; cubitos_quitados<(v_pilas[i]+1)/2; cubitos_quitados++) // hint: subdivide till < (num_bloques+1)/2
      {
        if( cubitos_quitados!= pila_vieja-cubitos_quitados )  // cubitos_quitados!= i-cubitos_quitados)
        {
          Nim new_Nim(v_pilas);
          new_Nim.v_pilas[i]-= cubitos_quitados;
          new_Nim.v_pilas.push_back(cubitos_quitados);

          hijos.push_back(new_Nim);
        }
      }
    }
    return hijos;
}

void Nim::muestra()
{
  for(const auto& pila:v_pilas)
    std::cout<<pila<<" ";
  std::cout<<std::endl;
    //Completar
}
