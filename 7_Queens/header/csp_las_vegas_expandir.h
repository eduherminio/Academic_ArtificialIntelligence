#include <chrono>
#include <random>

namespace problema_csp
{
  // iteraciones tiene a la entrada el limite de iteraciones y debera tener a la salida las iteraciones realizadas.

  template<typename T>
  bool Problema_csp<T>::las_vegas_expandir(size_t &iteraciones)
  {
    std::mt19937 rng;
    auto seed= std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(seed);   // Que pasa si se comenta esta linea?
    // Answer:
    // Se eliminaría la componente aleatoria del algoritmo, expandiéndose siempre el mismo número de nodos
    // (que a priori debería ser mayor que el promedio de nodos expandidos existienda esa componente de aleatoriedad)
    // Al no existir aleatoriedad, las cuatro implementaciones del algoritmo Las Vegas se comportan de igual manera

    T nodo(nodo_inicial);

    bool exito= false;
    nodos_expandidos= 0;

    const auto limite_iteraciones= iteraciones;
    iteraciones= 0;
    while(exito==false)
    {
      // DONE

      iteraciones++;
      const auto v_hijos= nodo.expandir();
      if(v_hijos.size())
      {
        ++nodos_expandidos;
        std::uniform_int_distribution<unsigned> aleatorio(0, v_hijos.size()-1);
        nodo= v_hijos[aleatorio(rng)];

        exito=nodo.prueba_meta(); //Prueba de meta
      }
      else
      {
        nodo= nodo_inicial;
      }

      if(iteraciones > limite_iteraciones)
        break;
    }
    if(exito)
    {
      nodo_solucion= nodo;
    }
    return exito;
  }
}
