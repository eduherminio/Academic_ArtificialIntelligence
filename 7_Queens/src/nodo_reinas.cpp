#include "../header/nodo_reinas.h"

namespace nodo_reinas
{

  //////////////////////////// SIN SET /////////////////////////////////////////////////////////
  bool Nodo_reinas::columna_valida(const unsigned fil_hijo,const unsigned col_hijo) const {
    bool exito=true;
    for(unsigned fil_padre=0; fil_padre!=fil_hijo; ++fil_padre)
    {
      auto col_padre=posicion.at(fil_padre);
      if(col_hijo==col_padre)
      {
        exito=false;
        break;
      }
      else
      {
        unsigned dif_fil,dif_col;
        if(col_padre>col_hijo)
        dif_col=col_padre-col_hijo;
        else
        dif_col=col_hijo-col_padre;

        if(fil_padre>fil_hijo)
        dif_fil=fil_padre-fil_hijo;
        else
        dif_fil=fil_hijo-fil_padre;
        if(dif_fil==dif_col)
        {
          exito=false;
          break;
        }
      }
    }
    return exito;
  }
  vector<Nodo_reinas> Nodo_reinas::expandir() const {
    // Si llevo 7 reinas colocadas, la nueva la coloco en la fila 7
    auto fil_hijo=posicion.size();
    vector<Nodo_reinas>lista_hijos;

    for(unsigned col_hijo=0; col_hijo!=dim; ++col_hijo) // Todas las posibles columnas
    {
      if(columna_valida(fil_hijo,col_hijo))
      {
        auto hijo=*this;
        hijo.posicion.push_back(col_hijo);
        lista_hijos.push_back(hijo);
      }
    }
    return lista_hijos;
  }
  bool Nodo_reinas::sucesor_aleatorio(std::mt19937& rng)  {
    auto fil_hijo=posicion.size();
    vector<unsigned>columnas;

    for(unsigned col_hijo=0; col_hijo!=dim; ++col_hijo) //Todas las posibles columnas
    {
      if(columna_valida(fil_hijo,col_hijo))
      {
        columnas.push_back(col_hijo);
      }
    }
    if(!columnas.empty())
    {
      std::uniform_int_distribution<unsigned>aleatorio(0,columnas.size()-1);
      posicion.push_back(columnas[aleatorio(rng)]);   // Añado sólo el hijo seleccionado aleatoriamente, no todos
      return true;
    }
    return false;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////// CON SET /////////////////////////////////////////////////////////
  bool Nodo_reinas_set::columna_valida(const unsigned fil_hijo,const unsigned col_hijo) const {
    if(columna.find(col_hijo) == columna.end()) //La columna no est� ocupada
    if(diag_45.find(col_hijo+fil_hijo) == diag_45.end()) //Diagonal 45 no est� ocupada
    if(diag_135.find(col_hijo-fil_hijo) == diag_135.end()) //Diagonal 135 no est� ocupada
    return true;
    return false;
  }
  vector<Nodo_reinas_set> Nodo_reinas_set::expandir() const {
    vector<Nodo_reinas_set>lista_hijos;
    // TO-DO
    return lista_hijos;
  }

  bool Nodo_reinas_set::sucesor_aleatorio(std::mt19937& rng)  {
    // TO-DO
    return false;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////
}
