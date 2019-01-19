#include "../header/taquin.h"
#include <iostream>

namespace taquin
{
	uint8_t Nodo_taquin::filas = 0;
	uint8_t Nodo_taquin::columnas = 0;

	std::vector<Nodo_taquin> Nodo_taquin::expandir() const
	{
		uint8_t fil = pos_cas_vac / columnas;
		uint8_t col = pos_cas_vac % columnas;

		//Numero de hijos: 9 posibilidades
		//4 vertices
		//4 lados
		//1 interior

		std::vector<uint8_t> pos_cas_vacia_hijos;

		if (fil == 0 && col == 0) //Esquina NO
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac + 1),uint8_t(pos_cas_vac + columnas) };
		}
		else if (fil == 0 && col == columnas - 1) //Esquina NE
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac - 1),uint8_t(pos_cas_vac + columnas) };
		}
		else if (fil == filas - 1 && col == 0) //Esquina SO
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac - columnas),uint8_t(pos_cas_vac + 1) };
		}
		else if (fil == filas - 1 && col == columnas - 1) //Esquina SE
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac - columnas),uint8_t(pos_cas_vac - 1) };
		}
		else if (fil == 0) //Lado norte interior
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac - 1),uint8_t(pos_cas_vac + 1),uint8_t(pos_cas_vac + columnas) };
		}
		else if (fil == filas - 1) //Lado sur interior
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac - columnas),uint8_t(pos_cas_vac - 1),uint8_t(pos_cas_vac + 1) };
		}
		else if (col == 0) //Lado oeste interior
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac - columnas),uint8_t(pos_cas_vac + 1),uint8_t(pos_cas_vac + columnas) };
		}
		else if (col == columnas - 1) //Lado este interior
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac - columnas),uint8_t(pos_cas_vac - 1),uint8_t(pos_cas_vac + columnas) };
		}
		else //Casilla interior
		{
			pos_cas_vacia_hijos = { uint8_t(pos_cas_vac - columnas),uint8_t(pos_cas_vac - 1),uint8_t(pos_cas_vac + 1),uint8_t(pos_cas_vac + columnas) };
		}

		std::vector<Nodo_taquin> hijos;     // Vector con los nodos hijos del nodo que se pasa a expandir()
		for (auto x : pos_cas_vacia_hijos)
		{
			hijos.push_back(*this);
			hijos.back().pos_cas_vac = x;
			hijos.back().posicion[pos_cas_vac] = posicion[x];
			hijos.back().posicion[x] = 0;
		}
		return hijos;
	}

	//    unsigned Nodo_taquin::get_clave() const
	//    {
	//        unsigned clave=0;
	//        for(auto x:posicion)
	//        {
	//            clave=10*clave+x;
	//        }
	//        return clave;
	//    }

	std::string Nodo_taquin::get_clave() const
	{
		std::string clave;
		clave.reserve(posicion.size());
		for (auto x : posicion)
			clave.push_back(x);
		return clave;
	}

	uint8_t mi_abs(uint8_t x, uint8_t y)
	{
		return x < y ? y - x : x - y;
	}
	//Heuristica Distancia de Manhattan
	size_t heuristica(const Nodo_taquin& nodo1, const Nodo_taquin& nodo2)
	{
		auto pos1 = nodo1.get_posicion();
		auto pos2 = nodo2.get_posicion();
		auto columnas = nodo1.get_columnas();

		size_t coste = 0;
		for (size_t i = 0; i != pos1.size(); ++i)
		{
			auto x = pos1[i];
			if (x != 0)
			{
				auto fil1 = i / columnas;
				auto col1 = i % columnas;
				for (size_t j = 0; j != pos2.size(); ++j)
				{
					auto y = pos2[j];
					if (x == y)
					{
						auto fil2 = j / columnas;
						auto col2 = j % columnas;
						coste += mi_abs(fil1, fil2) + mi_abs(col1, col2);
						break;
					}
				}
			}
		}
		return coste;
	}
}
