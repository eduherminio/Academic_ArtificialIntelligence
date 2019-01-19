#include "../header/controlador.h"
#include <thread>

namespace controlador
{
	void Controlador::registra_observadores()
	{
		Observador<Evento_vista>& observador_vista = vista->get_observador();
		observador_vista.registra_observador(Evento_vista::casilla, std::bind(&Controlador::movimiento_humano, this));
		observador_vista.registra_observador(Evento_vista::manual, std::bind(&Controlador::reversi_manual, this));
		observador_vista.registra_observador(Evento_vista::ordenador, std::bind(&Controlador::reversi_ordenador, this));
	}
	void Controlador::ejecutar()
	{
		hilo_vista = std::thread(&Controlador::ejecuta_vista, this);
	}
	void Controlador::reversi_manual()
	{
		evento_vista = Evento_vista::manual;
		reversi->inicializar();
		num_piezas_humano = 2;
		num_piezas_ordenador = 2;
		manual = true;
		fin_juego = false;
		actualiza_tablero();
	}
	void Controlador::reversi_ordenador()
	{
		evento_vista = Evento_vista::ordenador;
		reversi->inicializar();
		num_piezas_humano = 2;
		num_piezas_ordenador = 2;
		manual = false;
		fin_juego = false;
		actualiza_tablero();
	}
	void Controlador::ejecuta_vista()
	{
		vista->ejecutar();
	}
	void Controlador::movimiento_humano()
	{
		auto fil = vista->get_fila_pulsada();
		auto col = vista->get_columna_pulsada();
		reversi->ejecuta_movimiento(fil, col);

		auto jugadas_validas = reversi->get_jugadas_validas();
		if (jugadas_validas.empty())
		{
			if (reversi->turno_humano())
			{
				reversi->set_turno_ordenador();
			}
			else
			{
				reversi->set_turno_humano();
			}
			jugadas_validas = reversi->get_jugadas_validas();

			if (jugadas_validas.empty())
			{
				fin_juego = true;
			}
			actualiza_tablero();

		}
		else
		{
			actualiza_tablero();
			if (!manual)
			{
				reversi->ejecuta_movimiento(); //Movimiento ordenador
				jugadas_validas = reversi->get_jugadas_validas();

				if (jugadas_validas.empty())
				{
					fin_juego = true;
				}
				actualiza_tablero();
			}
		}
	}

	void Controlador::actualiza_tablero()
	{
		num_piezas_humano = 0;
		num_piezas_ordenador = 0;
		for (unsigned i = 0; i != filas; ++i)
		{
			for (unsigned j = 0; j != columnas; ++j)
			{
				if (reversi->casilla_humano(i, j))
				{
					vista->set_tipo_casilla(i, j, Tipo_casilla::humano);
					++num_piezas_humano;
				}
				else if (reversi->casilla_ordenador(i, j))
				{
					vista->set_tipo_casilla(i, j, Tipo_casilla::ordenador);
					++num_piezas_ordenador;
				}
				else
				{
					vista->set_tipo_casilla(i, j, Tipo_casilla::vacia);
				}
			}
		}
		auto jugadas_validas = reversi->get_jugadas_validas();
		for (auto &jugada : jugadas_validas)
		{
			vista->set_tipo_casilla(jugada.x, jugada.y, Tipo_casilla::vacia_posible);
		}

		vista->set_texto_puntuacion(num_piezas_ordenador, num_piezas_humano);
		if (fin_juego)
		{
			if (num_piezas_humano > num_piezas_ordenador)
				vista->fin_juego("WHITE\nWINS");
			else if (num_piezas_humano < num_piezas_ordenador)
				vista->fin_juego("BLACK\nWINS");
			else
				vista->fin_juego("DRAW");
		}
		else
		{
			if (reversi->turno_humano())
			{
				vista->set_texto_turno("WHITE");
			}
			else
			{
				vista->set_texto_turno("BLACK");
			}
		}
		vista->render();

	}
}
