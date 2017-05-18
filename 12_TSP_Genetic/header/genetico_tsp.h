#ifndef GENETICO_TSP
#define GENETICO_TSP

#include "../header/observador.h"
#include <atomic>
#include <algorithm>
#include <cassert>
#include <iostream>

enum class Evento_Modelo{nuevo_codigo};
enum class Seleccion{torneo_determinista,torneo_probabilista,ruleta};

template<typename T>
class Genetico_Tsp
{
public:
  void inicializacion(const unsigned n_i,const double p_e,const unsigned n_g,const double p_m,const unsigned t_t);
  void set_seleccion(const Seleccion);
  void ejecutar(T&);

  Observador<Evento_Modelo>& get_observador()
  {
    return observador;
  }
  void detener()
  {
    abortar=true;
  }
  const std::vector<unsigned> get_codigo() const
  {
    return(mejor_codigo);
  }
  unsigned get_iteracion_actual() const
  {
    return(iteracion_actual);
  }
  double get_mejor_puntuacion() const
  {
    return(mejor_puntuacion);
  }
  void registra_observador(const Evento_Modelo& evento, std::function<void()> obs)
  {
    observador.registra_observador(evento,obs);
  }
private:
  std::atomic<bool> abortar;

  std::mt19937 rng;
  std::uniform_real_distribution<double> aleatorio_0_a_1;
  std::uniform_int_distribution<unsigned> aleatorio_num_individuos; //Entre 0 y num_individuos-1

  // Tipo de seleccion de padres
  Seleccion tipo_seleccion;
  std::function<unsigned ()> seleccion;
  unsigned seleccion_torneo_probabilista();
  unsigned seleccion_ruleta();
  unsigned seleccion_torneo_determinista();

  // Funciones que realizan diferentes tares respecto a individuos y poblacion
  std::vector<T> poblacion;
  void crea_poblacion_inicial(T&);
  void calcula_media_puntuaciones();
  bool permutacion_repetida(T&);
  void ordena_por_puntuacion();
  void actualiza_poblacion(std::vector<T> &poblacion_nueva);

  //Algoritmos de cruce de permutaciones
  std::vector<T> cruce_orden_1(const T &padre_1,const T &padre_2);

  //Datos disponibles para el observador
  Observador<Evento_Modelo> observador;
  unsigned iteracion_actual;
  double mejor_puntuacion;
  std::vector<unsigned> mejor_codigo;
  double media_puntuaciones; //No capturada por el Observador ni implementada en la Vista
  ////////////////////////////

  //Parametros iniciales
  unsigned num_individuos;
  unsigned num_individuos_elite;
  unsigned num_generaciones;
  double probabilidad_mutacion;
  unsigned tam_torneo;
  //estado_inicializacion permite garantizar que se ha inicializado y elegido un metodo de seleccion
  unsigned estado_inicializacion=0;
};


#include "../header/genetico_tsp_impl.h"

#endif // GENETICO_H_INCLUDED
