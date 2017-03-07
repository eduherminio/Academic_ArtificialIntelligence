#ifndef NODO_TRAYECTORIA_H_INCLUDED
#define NODO_TRAYECTORIA_H_INCLUDED
#include "mapa.h"
#include <vector>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
namespace nodo_trayectoria
{
  using std::vector;

  class Nodo_trayectoria
  {

  public:
    Nodo_trayectoria(unsigned x,unsigned y):x(x),y(y)
    {
    }
    vector<Nodo_trayectoria> expandir() const;
    unsigned get_clave() const;
    static void set_mapa(const mapa::Mapa& m)
    {
      mapa=m;
    }
    unsigned get_x() const
    {
      return x;
    }
    unsigned get_y() const
    {
      return y;
    }
    double tipo_dato_coste()
    {
      return 0.;
    }
  private:
    static mapa::Mapa mapa;
    unsigned x;
    unsigned y;
    friend bool compatibles(const Nodo_trayectoria& nodo1, const Nodo_trayectoria& nodo2)
    {
      return true;
    }
    friend bool operator==(const Nodo_trayectoria& nodo1, const Nodo_trayectoria& nodo2);
    friend double heuristica(const Nodo_trayectoria& nodo1, const Nodo_trayectoria& nodo2);
    friend double coste_operador(const Nodo_trayectoria& nodo1, const Nodo_trayectoria& nodo2);
  };
  inline bool operator==(const Nodo_trayectoria& nodo1, const Nodo_trayectoria& nodo2) //Prueba de meta
  {
    return(nodo1.x==nodo2.x && nodo1.y==nodo2.y);
  }
  double heuristica(const Nodo_trayectoria& nodo1, const Nodo_trayectoria& nodo2);


}

#endif // NODO_TRAYECTORIA_H_INCLUDED
