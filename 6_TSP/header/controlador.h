#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED

#include "vista.h"   // Nuestra clase vista
#include "ruta.h"
#include "recocido_simulado_tsp.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>

namespace parche
{
  template < typename T > std::string to_string( const T& n )
  {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
  }
}
namespace controlador
{
  struct Datos_visualizacion
  {
    std::vector<unsigned> recorrido;
    double mejor_distancia;
    unsigned iteracion;
  };
  class Controlador
  {
  public:
    Controlador()
    {
      registra_observadores();    // TO-CHECK
      //Esta inicializacion es muy muy muy mejorable
      //El alumno deber� eliminar estos par�metros y obtnerlos de forma autom�tica dentro
      //de la clase TSP analizando las caracter�sticas del problema
      ////////////////////////////////////////////////////////////////////////////////////
      num_descensos=10000;
      num_permutaciones=5000;
      num_exitos_maximo=2000;
      temperatura=1000;
      factor_descenso=0.99;
      ////////////////////////////////////////////////////////////////////////////////////
    }
    void ejecutar();
  private:
    unsigned num_descensos;
    unsigned num_permutaciones;
    unsigned num_exitos_maximo;
    double temperatura;
    double factor_descenso;

    Vista vista;
    Recocido_simulado_TSP algoritmo_sa_tsp;
    Observador<Evento_Vista> observador_vista;
    Observador<Evento_Vista> observador_modelo;

    std::thread hilo_vista;
    std::thread hilo_modelo;
    std::thread hilo_cola_datos;

    std::atomic<bool> inicio_vista;
    std::atomic<bool> fin_vista;
    std::atomic<bool> inicio_algoritmo;
    std::atomic<bool> fin_algoritmo;
    std::atomic<bool> fin_hilos;

    std::mutex barrera_datos;
    std::mutex barrera_tsp;
    std::condition_variable c_v_barrera_datos;
    std::condition_variable c_v_barrera_tsp;

    std::queue<Datos_visualizacion> datos;

    ruta::Ruta ruta;

    void registra_observadores();

    bool carga_problema_tsplib();
    bool set_coordenadas_visualizacion(const ciudades::Ciudades& ciudades);

    void inicia_programa();
    void finaliza_programa();

    void ejecuta_sa_tsp();  //Hilo sa_tsp
    void detiene_sa_tsp();

    void push_datos();
    void pop_datos();    //Hilo cola de datos
    void vacia_datos();
  };
}
#endif // CONTROLADOR_H_INCLUDED
