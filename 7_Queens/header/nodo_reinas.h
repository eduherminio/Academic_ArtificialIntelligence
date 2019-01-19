#ifndef NODO_REINAS_H_INCLUDED
#define NODO_REINAS_H_INCLUDED

#include <cstddef>
#include <vector>
#include <set>
#include <iostream>
#include <random>

namespace nodo_reinas
{
	using std::vector;
	using std::set;

	class Nodo_reinas
	{
	public:
		Nodo_reinas(const unsigned dim, const vector<unsigned>& posicion)
			:dim(dim), posicion(posicion)
		{
		}

		vector<unsigned> get_posicion() const { return posicion; }
		bool prueba_meta()              const { return(posicion.size() == dim); }

		vector<Nodo_reinas> expandir() const;
		virtual bool sucesor_aleatorio(std::mt19937& rng);

	protected:
		unsigned dim;               // Dimension del tablero
		vector<unsigned> posicion;  // Stores, for each ocuppied row, the column where a queen is placed; so it's max size is dim

	private:
		bool columna_valida(const unsigned fil, const unsigned col) const;
	};

	class Nodo_reinas_set
		:public Nodo_reinas
	{
	public:
		Nodo_reinas_set(const unsigned dim, const vector<unsigned>& posicion)
			:Nodo_reinas(dim, posicion)
		{
		}
		void update_sets();
		vector<Nodo_reinas_set> expandir();                 // Sobreescritura - no virtual or override admitted due to the different return types (not covariant)
		bool sucesor_aleatorio(std::mt19937& rng) override; // Sobreescritura - 'virtual' & 'override' added

	private:
		set<unsigned> columna;
		set<unsigned> diag_45;
		set<unsigned> diag_135;
		bool columna_valida(const unsigned fil, const unsigned col) const;
	};

	template <typename T>
	void imprime_posicion(const T& nodo, const unsigned nodos_expandidos)
	{
		std::cout << "Nodos exp: " << nodos_expandidos << std::endl;
		for (const auto& x : nodo.get_posicion())
			std::cout << x << " ";
		std::cout << std::endl;

		imprime_tablero(nodo);  // Comment if not needed
	}

	template <typename T>
	void imprime_tablero(const T& nodo)
	{
		for (const auto& x : nodo.get_posicion())
		{
			for (unsigned i = 0; i < nodo.get_posicion().size(); ++i)
			{
				if (i == x)
					std::cout << "Q ";
				else
					std::cout << "- ";
			}
			std::cout << std::endl;
		}
	}
}

#endif // NODO_REINAS_H_INCLUDED
