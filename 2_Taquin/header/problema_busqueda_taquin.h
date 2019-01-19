#ifndef PROBLEMA_BUSQUEDA_TAQUIN_H_INCLUDED
#define PROBLEMA_BUSQUEDA_TAQUIN_H_INCLUDED
#include "taquin.h"
#include <limits>
#include <cassert>

namespace taquin
{
	class Problema_busqueda_taquin
	{
	public:

		Problema_busqueda_taquin(Nodo_taquin &i, Nodo_taquin &o) :nodo_inicial(i), nodo_objetivo(o)
		{
			assert(nodo_inicial.get_posicion().size() == nodo_objetivo.get_posicion().size() && "Error: nodos de diferentes dimensiones");
		}

		bool a_estrella();
		bool a_estrella_p_i();
		bool amplitud();

		bool profundidad()
		{
			size_t max_valor = std::numeric_limits<size_t>::max();
			return(profundidad(max_valor));
		}

		bool profundidad(size_t limite);

		bool profundizacion_iterativa()
		{
			size_t max_valor = std::numeric_limits<size_t>::max();
			return(profundizacion_iterativa(max_valor));
		}

		bool profundizacion_iterativa(size_t limite);

		std::vector<Nodo_taquin> get_solucion() const
		{
			return solucion;
		}

		size_t get_nodos_expandidos() const
		{
			return nodos_expandidos;
		}

	private:
		Nodo_taquin nodo_inicial;
		Nodo_taquin nodo_objetivo;
		size_t nodos_expandidos;
		std::vector<Nodo_taquin>solucion;
	};
	void muestra_solucion(const Problema_busqueda_taquin&);
}

#endif // PROBLEMA_BUSQUEDA_TAQUIN_H_INCLUDED
