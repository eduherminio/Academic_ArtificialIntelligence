#ifndef RUTA
#define RUTA

#include "ciudades.h"
#include <set>
#include <chrono>
#include <random>

namespace ruta
{
  class Ruta
  {
  public:
    Ruta()
    {
      // Obtenci�n de semilla para generadores de aleatorios

    }
    void inicializa_ruta(ciudades::Ciudades&&ciu)
    {
      ciudades=ciu;
      num_ciudades=ciudades.get_num_ciudades();

      auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      rng.seed(seed);
      aleatorio_num_ciudades=std::uniform_int_distribution<unsigned>(0,num_ciudades-1);
      aleatorio_0_a_1=std::uniform_real_distribution<double>(0,1);
    }

    double calcula_distancia(const std::vector<unsigned>& recorrido);

    double get_distancia_actual() const
    {
      return distancia_actual;
    }
    double get_distancia_provisional() const
    {
      return distancia_provisional;
    }

    void actualiza_ruta()
    {
      recorrido_actual=std::move(recorrido_provisional);
      distancia_actual=distancia_provisional;
    }

    const std::vector<unsigned> get_recorrido() const
    {
      return recorrido_actual;
    }
    void crea_recorrido_vecino();
    void inicializa_recorrido();
  private:

    std::vector<unsigned> recorrido_actual;
    std::vector<unsigned> recorrido_provisional;
    double distancia_actual;              //Longitud del recorrido
    double distancia_provisional;  //Longitud del recorrido provisional
    unsigned num_ciudades;
    ciudades::Ciudades ciudades;    //Puntero a la clase Ciudades del problema
    std::mt19937 rng;
    std::uniform_int_distribution<unsigned> aleatorio_num_ciudades;
    std::uniform_real_distribution<double> aleatorio_0_a_1;

    void rotacion_2_puntos();    //Crea recorrido provisional rotando el actual usando 2 puntos
    void intercambio_2_puntos(); //Crea recorrido provisional intercambiando 2 puntos
    void rotacion_3_puntos();
  };

  void crea_recorrido(unsigned num_ciudades,std::vector<unsigned>&);
  void crea_recorrido_aleatorio(unsigned num_ciudades,std::vector<unsigned>&);
  void crea_recorrido_avaro(std::vector<unsigned>&,const ciudades::Ciudades&);
  unsigned get_vecino_mas_proximo(const unsigned c,const std::set<unsigned>& set_ciudades,const ciudades::Ciudades& ciudades);
}

#endif // RUTA_H_INCLUDED
