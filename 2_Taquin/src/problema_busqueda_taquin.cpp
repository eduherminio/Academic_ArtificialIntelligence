#include "../header/problema_busqueda_taquin.h"
#include <iostream>

namespace taquin
{
	void muestra_solucion(const Problema_busqueda_taquin& problema)
	{
		auto solucion = problema.get_solucion();
		if (!solucion.size())
			std::cout << "No se ha encontrado solucion\n";
		else
		{
			for (auto x : solucion)
			{
				for (auto y : x.get_posicion())  // get posicion devuelve std::vector<uint8_t> posicion;
				{
					std::cout << static_cast<unsigned>(y) << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "\nProfundidad de la solucion: " << solucion.size() - 1 << "\n";
		}
	}
}
