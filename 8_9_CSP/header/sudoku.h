#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include "../header/problema_csp.h"
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <cmath>

namespace sudoku
{
  class Sudoku:public csp::Problema_csp<unsigned>
  {
  public:
    Sudoku(const std::string nombre_fichero):nombre_fichero(nombre_fichero)
    {
      std::ifstream fichero(nombre_fichero);
      if(fichero)
      {
        fichero>>dim; //Dimension del Sudoku
        num_variables=dim*dim;
      }
      else
      {
        dim= 9;
      }
    }

    bool consistente(const unsigned variable,const unsigned valor) override
    {
      unsigned fil= get_fila[variable];
      unsigned col= get_columna[variable];
      unsigned cuad= get_cuadrado[variable];

      if(fila[fil].find(valor) == fila[fil].end())
      {
        if(columna[col].find(valor) == columna[col].end())
        {
          if(cuadrado[cuad].find(valor) == cuadrado[cuad].end())
          {
            return true;
          }
        }
      }
      return false;
    }

    bool consistente(const unsigned var_1,const unsigned val_1,const unsigned var_2,const unsigned val_2) override
    {
      if(val_1 != val_2)
      	return true;
      else
      	return false;
    }

    //Todas las variables relacionadas entre si en el grafo retornan true
    bool relacionadas(const unsigned var_1,const unsigned var_2) override
    {
      //Verificamos si las variables estan en la misma fila, columna o cuadrado
      if(get_fila[var_1]==get_fila[var_2] || get_columna[var_1]==get_columna[var_2] || get_cuadrado[var_1]==get_cuadrado[var_2])
        return true;
      else
        return false;
    }


    void restaura_estado(const std::pair<unsigned,unsigned> &asignacion)  override;
    void actualiza_estado(const std::pair<unsigned,unsigned> &asignacion) override;
    void inicializa_dominio() override;

  private:
    std::string nombre_fichero;
    unsigned dim;

    void calcula_get_fila()
    {
      for(unsigned i=0; i!=num_variables; ++i)
        get_fila.push_back(i/dim);
    }

    void calcula_get_columna()
    {
      for(unsigned i=0; i!=num_variables; ++i)
        get_columna.push_back(i%dim);
    }

    void calcula_get_cuadrado()
    {
      unsigned aux=static_cast<unsigned>(sqrt(dim));
      for(unsigned i=0; i!=num_variables; ++i)
        get_cuadrado.push_back(aux*((i/dim)/aux)+((i%dim)/aux));
    }

    std::vector<unsigned> get_fila;
    std::vector<unsigned> get_columna;
    std::vector<unsigned> get_cuadrado;
    std::vector<std::set<unsigned>> columna;
    std::vector<std::set<unsigned>> fila;
    std::vector<std::set<unsigned>> cuadrado;

  };

  void imprime_solucion(std::vector<std::pair<unsigned,unsigned>>& solucion);
}

#endif // SUDOKU_H_INCLUDED
