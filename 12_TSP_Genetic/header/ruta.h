#ifndef RUTA
#define RUTA

#include "../header/ciudades.h"
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

    double calcula_distancia(const std::vector<unsigned>& rec);

    double puntuacion() const
    {
      return distancia;
    }
    const std::vector<unsigned> get_codigo() const
    {
      return recorrido;
    }
    void set_codigo(std::vector<unsigned> cod)
    {
      recorrido=std::move(cod);
      distancia=calcula_distancia(recorrido);
    }
    void crea_codigo_vecino();
    void crea_aleatoria();
    void mutacion()
    {
      crea_codigo_vecino();
    }
  private:
    std::vector<unsigned> recorrido;
    double distancia;
    unsigned num_ciudades;
    static ciudades::Ciudades ciudades;    //clase Ciudades del problema
    std::mt19937 rng;
    std::uniform_int_distribution<unsigned> aleatorio_num_ciudades;
    std::uniform_real_distribution<double> aleatorio_0_a_1;

    void rotacion_2_puntos();    //Crea codigo rotando el actual usando 2 puntos
    void intercambio_2_puntos(); //Crea codigo intercambiando 2 puntos
    void rotacion_3_puntos();
  };

  void crea_recorrido_aleatorio(unsigned num_ciudades,std::vector<unsigned>&);
}

#endif // RUTA_H_INCLUDED
