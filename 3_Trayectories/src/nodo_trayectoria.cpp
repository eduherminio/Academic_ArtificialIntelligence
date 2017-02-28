#include "../header/nodo_trayectoria.h"
#include <iostream>
#include <cmath>

namespace nodo_trayectoria
{
  const int despl[8][2]= {{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};
  mapa::Mapa Nodo_trayectoria::mapa;

  std::vector<Nodo_trayectoria> Nodo_trayectoria::expandir() const
  {
    std::vector<Nodo_trayectoria> hijos;
    Nodo_trayectoria hijo(*this);
    int hijo_x,hijo_y; //int pues podemos tener sumas negativas
    for(unsigned i=0; i<8; ++i) //Tenemos 8 posibles hijos
    {
      hijo_x=x+despl[i][0];
      hijo_y=y+despl[i][1];

      if(hijo_x>=0 && hijo_y>=0 && hijo_x<static_cast<int>(mapa.get_filas()) && hijo_y<static_cast<int>(mapa.get_columnas()))
      {
        auto clave=hijo_x*mapa.get_columnas()+hijo_y;
        if(!mapa.get_muros().count(clave))
        {
          hijo.x=static_cast<unsigned>(hijo_x);
          hijo.y=static_cast<unsigned>(hijo_y);
          hijos.push_back(hijo);
        }
      }
    }
    return hijos;
  }

  unsigned Nodo_trayectoria::get_clave() const
  {
    return(x*mapa.get_columnas()+y);
  }
  double heuristica(const Nodo_trayectoria& nodo1, const Nodo_trayectoria& nodo2)
  {
    auto dist1=fabs(static_cast<double>(nodo1.x)-static_cast<double>(nodo2.x));
    auto dist2=fabs(static_cast<double>(nodo1.y)-static_cast<double>(nodo2.y));
    if(dist1>dist2)
    return(dist2*sqrt(2)+dist1-dist2);
    else
    return(dist1*sqrt(2)+dist2-dist1);
  }
  double coste_operador(const Nodo_trayectoria& nodo1, const Nodo_trayectoria& nodo2)
  {
    if(nodo1.x==nodo2.x || nodo1.y==nodo2.y)
    return 1.;
    else
    return sqrt(2.);
  }
}
