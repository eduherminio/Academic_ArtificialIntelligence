#include <chrono>
#include <random>

namespace problema_csp
{
  //iteraciones tiene a la entrada el l�mite de iteraciones.
  //A la salida las iteraciones realizadas
  template<typename T>
  bool Problema_csp<T>::las_vegas_expandir(size_t &iteraciones)
  {
    std::mt19937 rng;
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(seed); //�Qu� pasa si se comenta esta l�nea?

    T nodo(nodo_inicial);

    bool exito=false;
    nodos_expandidos=0;

    const auto limite_iteraciones=iteraciones;
    iteraciones=0;
    while(exito==false)
    {
      ++nodos_expandidos;
      exito=nodo.prueba_meta(); //Prueba de meta

      //Completar
      exito=true;  //Eliminar esta linea
      if(iteraciones>limite_iteraciones)
      break;
    }
    if(exito)
    {
      nodo_solucion=nodo;
    }
    return exito;
  }
}
