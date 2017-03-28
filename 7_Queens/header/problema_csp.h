#ifndef PROBLEMA_CSP_H_INCLUDED
#define PROBLEMA_CSP_H_INCLUDED

namespace problema_csp
{
  template<typename T>
  class Problema_csp
  {
  public:
    Problema_csp(T &nodo_inicial):nodo_inicial(nodo_inicial),nodo_solucion(nodo_inicial)
    {
    }
    bool profundidad();
    bool las_vegas_expandir(size_t &iteraciones);
    bool las_vegas_sucesor_aleatorio(size_t &iteraciones);

    std::size_t get_nodos_expandidos() const
    {
      return nodos_expandidos;
    }
    T get_solucion() const
    {
      return nodo_solucion;
    }
  private:
    T nodo_inicial;
    T nodo_solucion;
    std::size_t nodos_expandidos;
  };
}

#include "csp_profundidad.h" //Fichero de plantillas
#include "csp_las_vegas_expandir.h" //Fichero de plantillas
#include "csp_las_vegas_sucesor_aleatorio.h" //Fichero de plantillas

#endif // PROBLEMA_CSP_H_INCLUDED
