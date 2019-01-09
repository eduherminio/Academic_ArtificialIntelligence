#include "../header/problema_busqueda_taquin.h"
#include <unordered_set>
#include <queue>
#include <iostream>

namespace taquin
{
	bool Problema_busqueda_taquin::amplitud()
	{
		solucion.clear();
		struct Nodo   // taquin + indice del padre (esta ultima para llegar a la solucion)
		{
			Nodo_taquin nodo;
			size_t padre;
		};
		std::vector<Nodo> lista; //{nodo,padre}     // lista de nodos
		std::unordered_set<std::string>claves;      // nodos más claves: sustituye a la función repetido

		lista.push_back({ nodo_inicial,0 });  // Inicialización
		claves.insert(nodo_inicial.get_clave());

		size_t indice = 0;
		bool exito = false;
		nodos_expandidos = 0;
		while (exito == false && indice < lista.size())
		{
			//std::cout<<claves.bucket_count()<<"\n"; //Evolucion del tamanho de la tabla hash
			++nodos_expandidos;

			exito = (lista[indice].nodo == nodo_objetivo); //Prueba de meta

			if (exito == false)
			{
				auto hijos = lista[indice].nodo.expandir(); // hijos: lista de hijos

				for (auto& x : hijos)  // x-> nodo
				{
					auto clave_hijo = x.get_clave();
					if (claves.count(clave_hijo) == 0) // No está -> añado
					{
						lista.push_back({ x,indice });
						claves.insert(clave_hijo);
					}
				}
				indice++;
			}
		}

		if (exito)
		{
			while (indice != 0)
			{
				solucion.push_back(lista[indice].nodo);
				indice = lista[indice].padre;
			}
			solucion.push_back(lista[indice].nodo);
		}
		return exito;
	}
} // end namespace taquin
