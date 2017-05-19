#include "../header/hanoi.h"
#include <iostream>

namespace hanoi
{
  unsigned Hanoi::num_clavijas=0; //Inicializa la variable estatica, comun a todos los nodos Hanoi

  bool Hanoi::operador_valido(unsigned origen,unsigned destino) const     //A completar
  {
    bool salida=false;
    if(origen!=destino)
    {
        // std::cout<<origen<<"!="<<destino<<std::endl;
      if(origen==1 && destino==2)
      {
        if(!v1.empty() && (v2.empty() || v1.back() < v2.back()))
          return true;
        else
          return false;
      }
      if(origen==1 && destino==3)
      {
        if(!v1.empty() && (v3.empty() || v1.back() < v3.back()))
          return true;
        else
          return false;
      }
      if(origen==2 && destino==1)
      {
        if(!v2.empty() && (v1.empty() || v2.back() < v1.back()))
          return true;
        else
          return false;
      }
      if(origen==2 && destino==3)
      {
        if(!v2.empty() && (v3.empty() || v2.back() < v3.back()))
          return true;
        else
          return false;
      }
      if(origen==3 && destino==1)
      {
        if(!v3.empty() && (v1.empty() || v3.back() < v1.back()))
          return true;
        else
          return false;
      }
      // if(origen=3 && destino==2) was causing a segmentation fault
      if(origen==3 && destino==2)
      {
        if(!v3.empty() && (v2.empty() || v3.back() < v2.back()))
          return true;
        else
          return false;
      }
    }

    else
    {
      // std::cout<<origen<<"=="<<destino<<std::endl;
      return false;
    }
  }

  Hanoi Hanoi::crea_hijo(unsigned origen,unsigned destino) const        // A completar
  {
    Hanoi hijo(*this); //Copia el padre (*this) en hijo

    if(origen==1 && destino==2)
    {
      hijo.v2.push_back(v1.back());
      hijo.v1.pop_back();
    }
    if(origen==1 && destino==3)
    {
      hijo.v3.push_back(v1.back());
      hijo.v1.pop_back();
    }
    if(origen==2 && destino==1)
    {
      hijo.v1.push_back(v2.back());
      hijo.v2.pop_back();
    }
    if(origen==2 && destino==3)
    {
      hijo.v3.push_back(v2.back());
      hijo.v2.pop_back();
    }
    if(origen==3 && destino==1)
    {
      hijo.v1.push_back(v3.back());
      hijo.v3.pop_back();
    }
    // if(origen=3 && destino==2) was causing a segmentation fault
    if(origen==3 && destino==2)
    {
      hijo.v2.push_back(v3.back());
      hijo.v3.pop_back();
    }

    return hijo;
}

    void muestra_estado(const Hanoi& h)
    {
        //No es necesaria hacer esta funcion.
    }
}
