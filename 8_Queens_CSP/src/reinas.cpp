#include "../header/reinas.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace reinas
{
  void Reinas::inicializa_dominio() {
    dominio = std::vector<std::vector<unsigned>> (num_variables, std::vector<unsigned> (num_variables, 0)); // (num_variables) element, each one with (num_variables) possible values (all = 0)
    for(unsigned i=0; i!=num_variables; ++i)
    {
      for(unsigned j=0; j!=num_variables; ++j)
      {
        dominio[i].at(j)= j;
      }
    }

    columna.clear();
    diag_45.clear();
    diag_135.clear();
  }

// Cada tipo de problema (reinas, sudoku) tendra sus funciones actualiza_Estado y restaura_Estado();
// Por eso en problema_csp.h son virtuales
// DONE: add 'override' specifier in function declarations
  void Reinas::actualiza_estado(const std::pair<unsigned,unsigned> &asignacion)   {   // variable: fila, valor: columna
    auto variable=  asignacion.first;
    auto valor=     asignacion.second;

    columna.insert(valor);
    diag_45.insert(variable + valor);
    diag_135.insert(num_variables + variable-valor);
  }

  void Reinas::restaura_estado(const std::pair<unsigned,unsigned> &asignacion)   {    // cuando una solucion no vale
    auto variable=  asignacion.first;
    auto valor=     asignacion.second;

    columna.erase(valor);
    diag_45.erase(variable + valor);
    diag_135.erase(num_variables + variable - valor);
  }

  void imprime_solucion(std::vector<std::pair<unsigned,unsigned>>& solucion)  {
    std::sort(solucion.begin(),solucion.end());

    // for(auto v:solucion)
    //   std::cout<<"("<<v.first<<","<<v.second<<")"<<std::endl;
    for(const auto& queen : solucion)
    {
      for(unsigned i=0; i< solucion.size(); ++i)
      {
        if(i==queen.second)
          std::cout<<"Q ";
        else
          std::cout<<"- ";
      }
      std::cout<<std::endl;
    }
  }
}
