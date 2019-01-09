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
      // actualiza_dominio es un puntero a función (declarado en problema_csp)
      // Aquí definimos a qué función apuntará actualiza_dominio en el futuro
      // A esto se le añade el uso de una función lambda, que nos permite definir aquí el contenidola función a la que apunta el puntero a función
      // seleccion_variable = [this]() -> unsigned
      // [this]:        variable capture: variables declared outside the lambda which needs to be used inside of it
      // ():            parameters, as a normal function
      // -> unsigned    new return value sintax: auto foo() -> return type
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
      assert(false && "Algorithm type not implemented");
      break;
  }
}

#include "../header/csp_fc.h" //Fichero de plantillas
#include "../header/csp_fc_ac1.h" //Fichero de plantillas

#endif // CSP_SELECCION_ALGORITMO_H_INCLUDED
