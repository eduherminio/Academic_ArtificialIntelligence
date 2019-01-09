#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED
#include <iostream>
#include <thread>
#include <chrono>
//#include "modelo.h"   // Nuestra clase modelo
#include "vista.h"   // Nuestra clase vista
#include "mapa.h"   // Nuestra clase vista

namespace controlador
{
	class Controlador
	{
	public:
		Controlador(unsigned filas, unsigned columnas, unsigned tam_casilla) :filas(filas), columnas(columnas)
		{
			vista = std::unique_ptr<Vista>(new Vista(filas, columnas, tam_casilla));
			mapa = std::unique_ptr<mapa::Mapa>(new mapa::Mapa());
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
		std::unique_ptr<mapa::Mapa> mapa;
		Observador<Evento_Vista> observador_vista;
		void registra_observadores();
		void inicializa_mapa();
		void busca_trayectoria();
		void ejecuta_vista();
		void ejecuta_modelo();
	};

}
#endif // CONTROLADOR_H_INCLUDED
