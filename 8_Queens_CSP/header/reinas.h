#ifndef REINAS_H_INCLUDED
#define REINAS_H_INCLUDED

#include "problema_csp.h"
#include <vector>
#include <set>
#include <cstdlib>

namespace reinas
{
  class Reinas:public csp::Problema_csp<unsigned>
  {
  public:
    Reinas(const unsigned dim)
    {
      num_variables=dim;
    }
    void restaura_estado(const std::pair<unsigned,unsigned> &asignacion) override;
    void actualiza_estado(const std::pair<unsigned,unsigned> &asignacion) override;
    //intentamos que sea inline para aumentar velocidad
    bool consistente(const unsigned variable,const unsigned valor) override
    {
      if(columna.find(valor) == columna.end())
      {
        if(diag_45.find(variable+valor) == diag_45.end())
        {
          if(diag_135.find(num_variables+variable-valor) == diag_135.end())
          {
            return true;
          }
        }
      }
      return false;
    }
    //intentamos que sea inline para aumentar velocidad
    bool consistente(const unsigned var_1,const unsigned val_1,const unsigned var_2,const unsigned val_2) override
    {
      if((val_1==val_2) || (abs(val_1-static_cast<int>(val_2))==abs(var_1-static_cast<int>(var_2))))
      {
        return false;
      }
      return true;
    }
    //Par alas reinas, todas las variables relacionadas entre si en el grafo
    bool relacionadas(const unsigned var_1,const unsigned var_2) override
    {
      return true;
    }
    void inicializa_dominio();
  private:
    std::set<unsigned> columna;
    std::set<unsigned> diag_45;
    std::set<unsigned> diag_135;
  };

  void imprime_solucion(std::vector<std::pair<unsigned,unsigned>>& solucion);

}

#endif // REINAS_H_INCLUDED
