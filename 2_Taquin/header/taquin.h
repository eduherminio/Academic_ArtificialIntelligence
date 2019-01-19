#ifndef TAQUIN_H_INCLUDED
#define TAQUIN_H_INCLUDED

#include <vector>
#include <cassert>
#include <cstdint>
#include <string>
#include <algorithm>

namespace taquin
{
	class Nodo_taquin //Limitado a 256 posibles valores
	{
	public:
		Nodo_taquin(uint8_t fil, uint8_t col, std::vector<uint8_t> posicion) :posicion(posicion)
		{
			filas = fil;
			columnas = col;

			//Verificamos que posicion.size() es filas*columnas
			assert(filas*columnas == posicion.size() && "Error: vector posicion de dimension no valida");

			//Verificamos que posicion es una permutacion de {0,1,...,filas*columna-1}
			auto aux(posicion);
			std::sort(aux.begin(), aux.end());
			for (size_t i = 0; i != aux.size(); ++i)
				assert(aux[i] == i && "Error: vector posicion no es una permutacion {0,1,...,n}");

			//Calculamos posicion de casilla vacia
			for (int i = 0; i != filas * columnas; ++i)
			{
				if (posicion.at(i) == 0)
				{
					pos_cas_vac = i;
					break;
				}
			}

		}

		std::vector<Nodo_taquin> expandir() const;
		//      unsigned get_clave() const;
		std::string get_clave() const;

		std::vector<uint8_t> get_posicion() const
		{
			return posicion;
		}
		uint8_t get_columnas() const
		{
			return columnas;
		}
	private:
		static uint8_t filas; //static puesto que filas y columnas e scompartido por todos los nodos
		static uint8_t columnas;
		std::vector<uint8_t> posicion;
		uint8_t pos_cas_vac;  //Miembro instrumental para agilizar la expansion de un nodo
	};

	inline bool operator==(const Nodo_taquin& nodo1, const Nodo_taquin& nodo2)
	{ //Prueba de meta   // Helper función. Redifinición de == -> coge dos taquines, y devuelve igualdad si coinciden sus vectores de posición

		return(nodo1.get_posicion() == nodo2.get_posicion());
	}

	size_t heuristica(const Nodo_taquin& nodo1, const Nodo_taquin& nodo2);

	inline size_t coste_operador(const Nodo_taquin& nodo1, const Nodo_taquin& nodo2)
	{
		return 1;   // coste de moverse de un nodo al otro, en el caso del taquin: 1
	}
}

#endif // TAQUIN_H_INCLUDED
