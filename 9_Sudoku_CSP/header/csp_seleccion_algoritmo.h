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
    case Algoritmo::fc_ac1:
    actualiza_dominio = [this](const std::pair<unsigned,T> &asignacion) -> bool
    {
      return(actualiza_dominio_fc_ac1(asignacion));
    };
    break;
    default:
    assert(false && "Tipo de algoritmo no implementado");
    break;
  }
}

#include "../header/csp_fc.h" //Fichero de plantillas
#include "../header/csp_fc_ac1.h" //Fichero de plantillas

#endif // CSP_SELECCION_ALGORITMO_H_INCLUDED
