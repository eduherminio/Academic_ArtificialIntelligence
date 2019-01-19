#include "../header/mochila.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace mochila
{
	void Mochila::inicializa()
	{
		dominio = std::vector<std::vector<unsigned>>(num_variables, std::vector<unsigned> {0, 1});

		try
		{
			std::ifstream fichero(nombre_fichero);
			if (fichero)
			{
				fichero >> num_variables; //Numero de items
				fichero >> capacidad_maxima;
				pesos.resize(num_variables, 0);
				valores.resize(num_variables, 0);

				for (unsigned i = 0; i != num_variables; ++i)
				{
					fichero >> pesos[i];
				}
				for (unsigned i = 0; i != num_variables; ++i)
				{
					fichero >> valores[i];
				}
			}
			else
			{
				throw std::invalid_argument("Knapsack file does not exist.\nAn empty 9x9 Knapsack will be resolved.\n");
			}
		}
		catch (const std::invalid_argument &mensaje)
		{
			std::cout << mensaje.what() << std::endl;
		}
		variables_sin_etiquetar.clear();
		for (unsigned i = 0; i != num_variables; ++i) // Todas las variables sin etiquetar(sin asignar un valor) inicialmente
			variables_sin_etiquetar.push_back(i);
		solucion.clear();
		peso_actual = 0;
		valor_actual = 0;
		valor_optimo = 0;
	}

	void Mochila::ordenacion_estatica_variables_ad_hoc()
	{
		// DONE: order by increasing specific value (valor/peso)


		// for(const auto& variable : variables_sin_etiquetar)
		//   std::cout<<variable<<"("<<valores[variable]/pesos[variable]<<") ";
		// std::cout<<std::endl;

		std::sort(variables_sin_etiquetar.begin(), variables_sin_etiquetar.end(), [this](const unsigned a, const unsigned b) -> bool
		{
			return valores[a] / pesos[a] < valores[b] / pesos[b];
		});

		// for(const auto& variable : variables_sin_etiquetar)
		//   std::cout<<variable<<"("<<valores[variable]/pesos[variable]<<") ";
		// std::cout<<std::endl;
	}

	bool Mochila::consistente(const unsigned variable, const unsigned valor) // Una asignación se puede hacer o no
	{
		if (valor == 0)  // No introduzco nada
			return true;
		else
		{
			// DONE

			// Añadir la poda de la cota superior obtenida mediante mochila fraccional
			// coste acumulado + coste_fraccional < valor_optimo
			// cota_superior_mochila_fraccional incluye el valor acumulado

			if ((peso_actual + pesos[variable] <= capacidad_maxima) && (cota_superior_mochila_fraccional() > valor_optimo))
				return true;
			else
				return false;
		}
	}

	void Mochila::actualiza_estado(const std::pair<unsigned, unsigned> &asignacion)
	{
		if (asignacion.second)
		{
			valor_actual += valores[asignacion.first];
			peso_actual += pesos[asignacion.first];
		}
	}

	void Mochila::restaura_estado(const std::pair<unsigned, unsigned> &asignacion)
	{
		if (asignacion.second)
		{
			valor_actual -= valores[asignacion.first];
			peso_actual -= pesos[asignacion.first];
		}
	}

	void Mochila::actualiza_solucion(std::vector< std::pair<unsigned, unsigned> >& sol)
	{
		if (solucion.empty() || valor_optimo <= valor_actual)  // solución: vector de solución definitiva
		{
			solucion = sol;
			valor_optimo = valor_actual;
		}
	}

	double Mochila::cota_superior_mochila_fraccional()
	{
		double capacidad_fraccional = capacidad_maxima - peso_actual;
		double peso_fraccional = 0;
		double cota_superior = valor_actual;

		// Las variables se suponen ordenadas de menor a mayor segun valor especifico

		for (int i = variables_sin_etiquetar.size() - 1; i >= 0; --i)
		{
			auto var = variables_sin_etiquetar[i];
			if (peso_fraccional + pesos[var] <= capacidad_fraccional)
			{
				cota_superior += valores[var];
				peso_fraccional += pesos[var];
			}
			else
			{
				cota_superior += ((capacidad_fraccional - peso_fraccional) / (pesos[var])) * valores[var];
				break;
			}
		}

		return cota_superior;
	}

	void Mochila::imprime_solucion()
	{
		std::sort(solucion.begin(), solucion.end());
		for (const auto& v : solucion)
		{
			if (v.second)
			{
				std::cout << v.first << " " << pesos[v.first] << " " << valores[v.first] << "\n";
			}
		}
		std::cout << "Value: " << valor_optimo << std::endl;
	}
}
