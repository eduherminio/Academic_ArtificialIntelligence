#ifndef CRONOMETRO_H_INCLUDED
#define CRONOMETRO_H_INCLUDED

#include <chrono>
#include <iostream>
#include <cassert>

template<typename T>
class Cronometro
{
public:
  void inicio()
  {
    tiempo_inicio = std::chrono::high_resolution_clock::now();
    estado=1;
  }
  void fin()
  {
    assert(estado>=1 && "No se puso en marcha el cronometro");
    intervalo= (std::chrono::high_resolution_clock::now()-tiempo_inicio);
    estado=2;
  }
  double get_intervalo() const
  {
    assert(estado==2 && "No se paro el cronometro");
    return intervalo.count();
  }
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> tiempo_inicio;
  std::chrono::duration<double,T> intervalo;
  unsigned estado=0;

};

template<typename T>
std::ostream& operator<< (std::ostream& out,const Cronometro<T>& crono)
{
  out<<crono.get_intervalo();
  return out;
}

#endif // CRONOMETRO_H_INCLUDED
