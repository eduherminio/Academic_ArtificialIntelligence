#ifndef NODO_REINAS_H_INCLUDED
#define NODO_REINAS_H_INCLUDED

#include <cstddef>
#include <vector>
#include <set>
#include <iostream>
#include <random>

namespace nodo_reinas
{
  using std::vector;
  using std::set;
  class Nodo_reinas
  {
  public:
    Nodo_reinas(const unsigned dim,const vector<unsigned>& posicion):dim(dim),posicion(posicion)
    {}
      vector<unsigned> get_posicion() const
      {
        return posicion;
      }
      vector<Nodo_reinas> expandir() const;
      bool sucesor_aleatorio(std::mt19937& rng);
      bool prueba_meta() const
      {
        return(posicion.size()==dim);
      }
    protected:
      unsigned dim;               // Dimension del tablero
      vector<unsigned> posicion;  // Permutacion que describe parcialmente el tablero
    private:
      bool columna_valida(const unsigned fil,const unsigned col) const;
    };

    class Nodo_reinas_set:public Nodo_reinas
    {
    public:
      Nodo_reinas_set(const unsigned dim,const vector<unsigned>& posicion):Nodo_reinas(dim,posicion)
      {}
        vector<Nodo_reinas_set> expandir() const;  // Sobreescritura
        bool sucesor_aleatorio(std::mt19937& rng); // Sobreescritura
      private:
        set<unsigned> columna;
        set<unsigned> diag_45;
        set<unsigned> diag_135;
        bool columna_valida(const unsigned fil,const unsigned col) const;
      };

      template <typename T>
      void imprime_posicion(const T& nodo)
      {
        for(auto v:nodo.get_posicion())
        std::cout<<v<<" ";
        std::cout<<"\n";
      }
    }

    #endif // NODO_REINAS_H_INCLUDED
