#include <iostream>
#include <vector>

namespace problema_csp
{
	template<typename T>
	bool Problema_csp<T>::profundidad()
	{
		struct Nodo
		{
			T nodo;
			bool visitado;
		};
		std::vector<Nodo> lista;
		lista.push_back({ nodo_inicial,false });

		size_t indice = 0;
		bool exito = false;
		nodos_expandidos = 0;

		while (exito == false && lista.size() > 0)
		{
			// DONE: busqueda en profundidad

			if (lista[indice].visitado == false)
			{
				lista[indice].visitado = true;
				auto v_hijos = lista[indice].nodo.expandir();
				if (v_hijos.size())
				{
					nodos_expandidos++;
					for (const auto& hijo : v_hijos)
					{
						lista.push_back({ hijo, false });
					}
				}
				else
				{
					lista.pop_back();
				}
			}
			else
			{
				lista.pop_back();
			}

			indice = lista.size() - 1;
			exito = (lista[indice].nodo.prueba_meta());

		}
		if (exito)
		{
			nodo_solucion = lista[indice].nodo;
		}
		return exito;
	}
}
