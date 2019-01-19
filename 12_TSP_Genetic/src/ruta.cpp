#include "../header/ruta.h"

#include <algorithm>

namespace ruta
{
	ciudades::Ciudades Ruta::ciudades; //ciudades es estatica
	double Ruta::calcula_distancia(const std::vector<unsigned>& rec)
	{
		return(ciudades.calcula_distancia(rec));
	}


	void Ruta::rotacion_3_puntos()
	{
		// Copiamos codigo actual en el posible nuevo codigo
		auto codigo_provisional = recorrido;
		unsigned c[3];

		//Elegimos aleatoriamente 3 indices de ciudades
		c[0] = aleatorio_num_ciudades(rng);
		c[1] = aleatorio_num_ciudades(rng);
		c[2] = aleatorio_num_ciudades(rng);

		//Exigimos que sean distintos
		while ((c[0] == c[1] ||
			c[0] == c[2] ||
			c[1] == c[2]))
		{
			c[0] = aleatorio_num_ciudades(rng);
			c[1] = aleatorio_num_ciudades(rng);
			c[2] = aleatorio_num_ciudades(rng);
		}
		//Los ordenamos de menor a mayor
		std::sort(c, c + 3);

		//Ejecutamos la rotacion
		auto it1 = codigo_provisional.begin() + c[0];
		auto it2 = codigo_provisional.begin() + c[1];
		auto it3 = codigo_provisional.begin() + c[2];
		rotate(it1, it2, it3);
		set_codigo(codigo_provisional);
	}

	// Elige una seccion dada por 2 puntos de la ruta y la rota
	void Ruta::rotacion_2_puntos()
	{
		// Copiamos codigo actual en el posible nuevo codigo
		auto codigo_provisional = recorrido;

		unsigned c1 = aleatorio_num_ciudades(rng);
		unsigned c2;

		do
		{
			c2 = aleatorio_num_ciudades(rng);
		} while (c1 == c2);
		if (c1 > c2)
		{
			auto aux = c2;
			c2 = c1;
			c1 = aux;
		}

		auto it1 = codigo_provisional.begin() + c1;
		auto it2 = codigo_provisional.begin() + c2;

		reverse(it1, it2);
		set_codigo(codigo_provisional);
	}

	void Ruta::crea_aleatoria()
	{
		crea_recorrido_aleatorio(num_ciudades, recorrido);
		distancia = ciudades.calcula_distancia(recorrido);
	}

	// Elige 2 puntos de la ruta y los intercambia
	void Ruta::intercambio_2_puntos()
	{
		// Copiamos codigo actual en el posible nuevo codigo
		auto codigo_provisional = recorrido;

		unsigned c1 = aleatorio_num_ciudades(rng);
		unsigned c2;
		do
		{
			c2 = aleatorio_num_ciudades(rng);
		} while (c1 == c2);

		codigo_provisional[c1] = recorrido[c2];
		codigo_provisional[c2] = recorrido[c1];
		set_codigo(codigo_provisional);
	}

	void Ruta::crea_codigo_vecino()
	{
		auto aleatorio = aleatorio_0_a_1(rng);


		if (aleatorio < 0.35)  //Umbrales para valores aleatorios elegidos "a pelo"
		{
			rotacion_3_puntos();
		}
		else if (aleatorio < 0.7)
		{
			rotacion_2_puntos();
		}
		else
		{
			intercambio_2_puntos();
		}
	}

	// Genera recorrido aleatorio
	void crea_recorrido_aleatorio(unsigned num_ciudades, std::vector<unsigned>& recorrido)
	{
		recorrido.clear();

		for (unsigned i = 0; i != num_ciudades; ++i)
		{
			recorrido.push_back(i);
		}
		std::random_shuffle(recorrido.begin() + 1, recorrido.end());
	}





}
