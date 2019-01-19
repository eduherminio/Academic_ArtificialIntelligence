#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#include "observador.h"
#include "rejilla.h"
#include "texturas.h"
#include "panel.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>


class Vista
{
	unsigned filas;
	unsigned columnas;

	// Dejamos 5 pixeles desde el tablero a los limites
	// Dejamos 1 pixel entre casillas
	const unsigned hueco_entre_casillas = 1;
	const unsigned hueco_al_borde = 5;
	const unsigned ancho_panel = 200;
	const unsigned tam_casilla = 80;
	unsigned ancho;
	unsigned alto;
	Rejilla rejilla;
	Panel panel;
	Textura textura;

	sf::RenderWindow render_window;



	sf::Clock solveTime;

	void procesa_eventos();
	void procesa_eventos_raton();


	unsigned fila_pulsada, columna_pulsada;
	bool jugando_humano;

	Observador<Evento_vista> observador;

public:
	void render();
	Vista(unsigned filas, unsigned columnas) :filas(filas), columnas(columnas)
	{
		ancho = unsigned(tam_casilla)*columnas + 2 * hueco_al_borde + (columnas - hueco_entre_casillas) + ancho_panel;
		alto = unsigned(tam_casilla)*filas + 2 * hueco_al_borde + (filas - hueco_entre_casillas);
		rejilla.set_rejilla(filas, columnas, tam_casilla, hueco_entre_casillas, hueco_al_borde, textura);
		jugando_humano = false;
	}
	Observador<Evento_vista>& get_observador()
	{
		return observador;
	}
	void ejecutar();
	unsigned get_fila_pulsada() const
	{
		return fila_pulsada;
	}
	unsigned get_columna_pulsada() const
	{
		return columna_pulsada;
	}
	void set_tipo_casilla(unsigned fil, unsigned col, Tipo_casilla tipo_casilla)
	{
		rejilla.set_tipo_casilla(fil, col, tipo_casilla, textura);
	}
	void fin_juego(const std::string&);
	void set_jugando_humano(bool valor)
	{
		jugando_humano = valor;
	}
	void set_texto_puntuacion(unsigned blancas, unsigned negras);
	void set_texto_turno(const std::string&);
	void set_texto_turno_humano();
	void set_texto_turno_ordenador();

};

#endif // VISTA_H_INCLUDED
