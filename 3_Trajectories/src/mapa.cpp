#include "../header/mapa.h"

namespace mapa
{
	const int despl[8][2] = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };
	void Mapa::set_muros(const std::vector<Punto_2d> &lista_muros)
	{
		muros.clear();
		for (auto punto : lista_muros)
		{
			muros.insert(columnas*punto.x + punto.y);
		}
	}
	void Mapa::set_filas_columnas(const unsigned num_filas, const unsigned num_columnas, const std::vector <Punto_2d> &mur)
	{
		auto fil = fin.x;
		auto col = fin.y;
		if (inicio.x > fil)
			fil = inicio.x;
		if (inicio.y > col)
			col = inicio.y;
		for (auto punto : mur)
		{
			if (punto.x > fil)
				fil = punto.x;
			if (punto.y > col)
				col = punto.y;
		}
		fil += 2;
		if (fil > num_filas)
			fil = num_filas;
		col += 2;
		if (col > num_columnas)
			col = num_columnas;
		//configura propiedades del mapa para todas las casillas
		filas = fil;
		columnas = col;
	}

	std::vector<Punto_2d> Mapa::expandir(const Punto_2d& punto) const
	{
		Punto_2d hijo;
		std::vector<Punto_2d> lista_hijos;
		int hijo_x, hijo_y; //int pues podemos tener sumas negativas
		for (unsigned i = 0; i < 8; i++) //Tenemos 8 posibles hijos
		{
			hijo_x = punto.x + despl[i][0];
			hijo_y = punto.y + despl[i][1];

			if (hijo_x >= 0 && hijo_y >= 0 && hijo_x < static_cast<int>(filas) && hijo_y < static_cast<int>(columnas))
			{
				auto clave = hijo_x * columnas + hijo_y;
				if (!muros.count(clave))
				{
					hijo.x = static_cast<unsigned>(hijo_x);
					hijo.y = static_cast<unsigned>(hijo_y);
					lista_hijos.push_back(hijo);
				}
			}
		}
		return lista_hijos;
	}
	double Mapa::acumula_coste(const Punto_2d& p1, const Punto_2d& p2) const
	{
		if (p1.x == p2.x || p1.y == p2.y)
			return 1.;
		else
			return sqrt(2.);
	}
	bool Mapa::prueba_meta(const Punto_2d& p) const
	{
		bool exito = false;
		if (p.x == fin.x && p.y == fin.y)
			exito = true;
		return exito;
	}

	double Mapa::calcula_heuristica(const Punto_2d &p) const
	{
		auto dist1 = fabs(static_cast<double>(p.x) - static_cast<double>(fin.x));
		auto dist2 = fabs(static_cast<double>(p.y) - static_cast<double>(fin.y));
		if (dist1 > dist2)
			return(dist2*sqrt(2) + dist1 - dist2);
		else
			return(dist1*sqrt(2) + dist2 - dist1);
	}

	unsigned Mapa::nodo_to_clave(const Punto_2d &p) const
	{
		return(p.x*get_columnas() + p.y);
	}

	Punto_2d Mapa::clave_to_nodo(unsigned clave) const
	{
		Punto_2d p;
		p.x = clave / columnas;
		p.y = clave % columnas;
		return(p);
	}

	bool Mapa::hijo_valido(const Punto_2d &punto_padre, const Punto_2d &punto_hijo, double &coste_actual_hijo)
	{
		auto clave_nodo_actual = nodo_to_clave(punto_padre);
		auto clave_hijo = nodo_to_clave(punto_hijo);
		coste_actual_hijo = coste_actual[clave_nodo_actual] + acumula_coste(punto_padre, punto_hijo);

		//El hijo puede estar repetido, pero tener en esa rama un coste superior al actual
		//En ese caso, abandonamos el hijo antiguo y lo cambiamos por el nuevo
		if (!padre.count(clave_hijo) || coste_actual_hijo < coste_actual[clave_hijo])
		{
			coste_actual[clave_hijo] = coste_actual_hijo;
			padre[clave_hijo] = clave_nodo_actual;
			return true;
		}
		else
			return false;
	}
}
