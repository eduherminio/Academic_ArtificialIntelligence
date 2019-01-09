#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED

#include <iostream>
#include <thread>
#include <chrono>
#include "reversi.h"   // Nuestra clase modelo
#include "vista.h"   // Nuestra clase vista

namespace controlador
{
  class Controlador
  {
  public:
    Controlador(unsigned filas,unsigned columnas):filas(filas),columnas(columnas)
    {
      vista=std::unique_ptr<Vista>(new Vista(filas,columnas));
      reversi=std::unique_ptr<Reversi>(new Reversi(filas,columnas));
      registra_observadores();
    }
    ~Controlador()
    {
      hilo_vista.join();
    }
    void ejecutar();
  private:
    unsigned filas;
    unsigned columnas;
    std::thread hilo_vista;
    std::thread hilo_modelo;
    std::unique_ptr<Vista> vista;
    std::unique_ptr <Reversi> reversi;   //Aplicacion
    Observador<Evento_vista> observador_vista;
    void registra_observadores();
    void ejecuta_vista();
    void ejecuta_modelo();
    void movimiento_humano();
    void movimiento_ordenador();
    void actualiza_tablero();
    void reversi_manual();
    void reversi_ordenador();
    Evento_vista evento_vista;
    bool manual;
    bool fin_juego;

    unsigned num_piezas_humano;
    unsigned num_piezas_ordenador;
  };

}

#endif // CONTROLADOR_H_INCLUDED
