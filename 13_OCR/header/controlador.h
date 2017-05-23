#ifndef CONTROLADOR_H_INCLUDED

#define CONTROLADOR_H_INCLUDED

#include "../header/vista.h"   // Nuestra clase vista
#include "../header/knn.h"
#include "../header/mnist.h"
#include "../header/sf_extension.h"
#include "../MNIST/include/mnist_reader.h"
#include "../MNIST/include/mnist_utils.h"
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
  class Controlador
  {
  public:
    Controlador(Vista &vista,Knn<std::vector<uint8_t>,uint8_t> &knn,Mnist &mnist):vista(vista),knn(knn),mnist(mnist)
    {
      registra_observadores();
    }
    void ejecutar();
  private:

    Vista &vista;
    Knn<std::vector<uint8_t>,uint8_t> &knn;
    Mnist &mnist;

    std::thread hilo_vista;
    std::thread hilo_modelo;

    std::atomic<bool> inicio_vista;
    std::atomic<bool> fin_vista;
    std::atomic<bool> inicio_algoritmo;
    std::atomic<bool> fin_algoritmo;

    std::mutex barrera_knn;
    std::condition_variable c_v_barrera_knn;

    void registra_observadores();

    bool carga_imagenes_mnist();

    void inicia_programa();
    void finaliza_programa();

    void ejecuta_knn();  //Hilo sa_tsp
    void detiene_knn();

  };
}

#endif // CONTROLADOR_H_INCLUDED
