#ifndef RECOCIDO_SIMULADO_TSP
#define RECOCIDO_SIMULADO_TSP

#include "ruta.h"
#include "observador.h"
#include <atomic>

enum class Evento_Modelo{nuevo_recorrido};

class Recocido_simulado_TSP
{
public:
  void inicializacion(const unsigned num_descensos,const unsigned num_permutaciones,
    const unsigned num_exitos_maximo,const double temperatura,
    const double factor_descenso);
    void ejecutar(ruta::Ruta& ruta);

    Observador<Evento_Modelo>& get_observador()
    {
      return observador;
    }
    void detener()
    {
      abortar=true;
    }
    const std::vector<unsigned> get_recorrido() const
    {
      return(mejor_recorrido);
    }
    unsigned get_iteracion_actual() const
    {
      return(iteracion_actual);
    }
    double get_mejor_distancia() const
    {
      return(mejor_distancia);
    }
  private:
    std::atomic<bool> abortar;

    Observador<Evento_Modelo> observador;

    //Datos disponibles para el observador
    unsigned iteracion_actual;
    double mejor_distancia;
    std::vector<unsigned> mejor_recorrido;
    ////////////////////////////

    unsigned num_descensos;
    unsigned num_permutaciones;
    unsigned num_exitos_maximo;
    double temperatura;
    double factor_descenso;
  };




  #endif // RECOCIDO_SIMULADO_H_INCLUDED
