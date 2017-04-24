#ifndef CSP_SELECCION_ALGORITMO_H_INCLUDED
#define CSP_SELECCION_ALGORITMO_H_INCLUDED

template <typename T>
void Problema_csp<T>::seleccion_algoritmo_look_ahead(const csp::Algoritmo algoritmo)
{
  switch(algoritmo)
  {
    case Algoritmo::bt:
    break;
    case Algoritmo::fc:
    actualiza_dominio = [this](const std::pair<unsigned,T> &asignacion) -> bool
    {
      return(actualiza_dominio_fc(asignacion));
    };
    break;
    default:
    assert(false && "Algorithm type not implemented");
    break;
  }
}

#include "csp_fc.h" //Fichero de plantillas

#endif // CSP_SELECCION_ALGORITMO_H_INCLUDED
