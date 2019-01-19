#ifndef CIUDADES
#define CIUDADES

#include <iostream>
#include <vector>

namespace ciudades
{
	class Ciudades
	{
	public:
		Ciudades()
		{

		}
		bool carga_ciudades(const std::string nombre_fichero, int& num_ciudades);
		// Devuelve la distancia entre 2 ciudades
		double get_distancia(const unsigned ciudad1, const unsigned ciudad2) const
		{
			return distancias[ciudad1][ciudad2];
		}
		unsigned get_num_ciudades() const
		{
			return num_ciudades;
		}
		double calcula_distancia(const std::vector<unsigned>& codigo) const;

		std::vector<std::pair<double, double>> const & get_coordenadas() const
		{
			return coordenadas;
		}
		const std::vector<unsigned> & get_codigo_optimo() const
		{
			return codigo_optimo;
		}
		void calcula_valores_extremos(double &x_min, double &x_max, double &y_min, double &y_max) const;
	private:
		unsigned num_ciudades;
		std::vector<std::pair<double, double>>coordenadas;
		std::vector<std::vector<double>>distancias;
		std::vector<unsigned> codigo_optimo;
		void set_matriz_distancias();
	};
}

#endif // CIUDADES_H_INCLUDED
