#ifndef REVERSI_H_INCLUDED
#define REVERSI_H_INCLUDED

#include "posicion_reversi.h"
#include "nodo_reversi.h"

enum class Algoritmo :uint8_t
{
	minimax, alpha_beta
};

class Reversi  //Nuestro modelo
{
public:
	Reversi(const unsigned num_filas, const unsigned num_columnas) :filas(num_filas), columnas(num_columnas)
	{
		// Debug error checking
		assert((filas > 3) && (columnas > 3));
		posicion.inicializar(filas, columnas); //Crea la matriz tablero sin contenido

	}
	bool fin_partida() const
	{
		if (posicion.get_pasa() == Tipo_tablero::terminal)
			return(true);
		else
			return(false);
	}
	void ejecuta_movimiento(const unsigned x, const unsigned y);
	void ejecuta_movimiento();
	bool casilla_vacia(const unsigned x, const unsigned y) const
	{
		return(posicion.get_tablero(x, y) == Turno::vacia);
	}
	bool casilla_humano(const unsigned x, const unsigned y) const
	{
		return(posicion.get_tablero(x, y) == Turno::humano);
	}
	bool casilla_ordenador(const unsigned x, const unsigned y) const
	{
		return(posicion.get_tablero(x, y) == Turno::ordenador);
	}
	bool turno_humano() const
	{
		return(posicion.get_turno() == Turno::humano);
	}
	bool turno_ordenador() const
	{
		return(posicion.get_turno() == Turno::ordenador);
	}
	void set_turno_ordenador()
	{
		posicion.set_turno(Turno::ordenador);
	}
	void set_turno_humano()
	{
		posicion.set_turno(Turno::humano);
	}
	int get_heuristica() const
	{
		return(heuristica);
	}
	void set_profundidad_maxima(const unsigned valor)
	{
		profundidad_maxima = 1;
		if (valor > profundidad_maxima)
			profundidad_maxima = valor;
	}
	void inicializar();
	int estrategia_alpha_beta();
	int estrategia_minimax();
	void set_algoritmo(const Algoritmo alg)
	{
		algoritmo = alg;
	}
	std::vector<Jugada> get_jugadas_validas()
	{
		return posicion.calcula_jugadas();
	}
private:
	Posicion_reversi posicion;
	std::vector<Jugada> jugadas_validas_humano;
	std::vector<Jugada> jugadas_validas;
	const unsigned filas;
	const unsigned columnas;
	unsigned profundidad_maxima;
	int heuristica;
	Algoritmo algoritmo;
};

#endif // REVERSI_H_INCLUDED
