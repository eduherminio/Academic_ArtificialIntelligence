#ifndef PROBLEMA_BUSQUEDA_H_INCLUDED
#define PROBLEMA_BUSQUEDA_H_INCLUDED


namespace problema_busqueda
{
  template<typename T>
  class Problema_busqueda
  {
  public:
    Problema_busqueda(T &i,T &o):nodo_inicial(i),nodo_objetivo(o)
    {
      assert(compatibles(nodo_inicial,nodo_objetivo) && "Nodos no compatibles");
    }
    bool a_estrella();
    bool a_estrella_p_i();
    bool coste_uniforme();
    bool amplitud();
    bool voraz();
    bool profundidad()
    {
      std::size_t max_valor = std::numeric_limits<std::size_t>::max();
      return(profundidad(max_valor));
    }
    bool profundidad(std::size_t limite);
    bool profundizacion_iterativa()
    {
      size_t max_valor = std::numeric_limits<size_t>::max();
      return(profundizacion_iterativa(max_valor));
    }
    bool profundizacion_iterativa(size_t limite);
    std::vector<T> get_solucion() const
    {
      return solucion;
    }
    std::size_t get_nodos_expandidos() const
    {
      return nodos_expandidos;
    }
  private:
    T nodo_inicial;
    T nodo_objetivo;
    std::size_t nodos_expandidos;
    std::vector<T>solucion;
  };
}

#include "busqueda_amplitud.h"            	// Plantillas necesarias para resolver el problema
#include "busqueda_profundidad.h"
#include "busqueda_a_estrella.h"
#include "busqueda_coste_uniforme.h"
#include "busqueda_voraz.h"

#endif // PROBLEMA_BUSQUEDA_H_INCLUDED
