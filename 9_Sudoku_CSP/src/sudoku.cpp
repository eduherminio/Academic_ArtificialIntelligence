#include "../header/sudoku.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace sudoku
{
  void Sudoku::inicializa_dominio()
  {
    dominio = std::vector<std::vector<unsigned>>(num_variables,std::vector<unsigned>(dim,0));
    for(unsigned i=0; i!=num_variables; ++i)
    {
      for(unsigned j=0; j!=dim; ++j)
      {
        dominio[i].at(j)=j+1;
      }
    }
    for(unsigned i=0; i!=dim; ++i)
    {
      columna.push_back(std::set<unsigned>());
      fila.push_back(std::set<unsigned>());
      cuadrado.push_back(std::set<unsigned>());
    }
    //LOOK UP TABLES para c�lculo r�pido de la fila, columna y cuadrado
    //correspondiente a una variable
    calcula_get_fila();
    calcula_get_columna();
    calcula_get_cuadrado();

    try
    {
      std::ifstream fichero(nombre_fichero);
      if(fichero)
      {
        fichero>>dim; //Dimension del Sudoku
        unsigned contador=0;
        unsigned valor;
        for(unsigned i=0; i!=num_variables; ++i)
        {
          fichero>>valor;
          if(valor!=0)
          {
            dominio[contador].clear();
            dominio[contador].push_back(valor);

          }
          ++contador;
        }
      }
      else
      {
        throw std::invalid_argument("No existe el fichero Sudoku.\nSe resolvera un Sudoku vacio 9x9.\n");
      }
    }
    catch(const std::invalid_argument &mensaje)
    {
      std::cout<<mensaje.what()<<std::endl;
    }


  }

  void Sudoku::actualiza_estado(const std::pair<unsigned,unsigned> &asignacion)
  {
    auto variable=asignacion.first;
    auto valor=asignacion.second;
    fila[get_fila[variable]].insert(valor);
    columna[get_columna[variable]].insert(valor);
    cuadrado[get_cuadrado[variable]].insert(valor);
  }

  void Sudoku::restaura_estado(const std::pair<unsigned,unsigned> &asignacion)
  {
    auto variable=asignacion.first;
    auto valor=asignacion.second;
    fila[get_fila[variable]].erase(valor);
    columna[get_columna[variable]].erase(valor);
    cuadrado[get_cuadrado[variable]].erase(valor);
  }

  void imprime_solucion(std::vector<std::pair<unsigned,unsigned>>& solucion)
  {
    auto dim=sqrt(solucion.size());
    std::sort(solucion.begin(),solucion.end());
    unsigned contador=0;
    for(auto v:solucion)
    {
      std::cout<<v.second<<" ";
      if(++contador==dim)
      {
        contador=0;
        std::cout<<std::endl;
      }
    }
  }
}
