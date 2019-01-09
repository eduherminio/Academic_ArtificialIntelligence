#include "../include/taquin.h"
#include <iostream>

namespace taquin
{
	int prof = 0;
	void copia_posicion(const unsigned origen[], unsigned destino[]) {
		for (auto i = 0; i < 9; ++i)
			destino[i] = origen[i];
	}

	void Taquin::set_objetivo(const unsigned v[]) {
		copia_posicion(v, posicion_objetivo);
	}

	void Taquin::set_inicial(const unsigned v[]) {
		copia_posicion(v, posicion_inicial);
	}

	bool Taquin::prueba_meta(const unsigned v1[], const unsigned v2[]) {
		size_t i = 0;

		while (i < 9)
		{
			if (v1[i] != v2[i])
				return false;
			++i;
		}
		return true;
	}

	void Taquin::inicializar_lista() {
		exito = false;
		struct Nodo_Taquin nodo_inicial;

		for (int i = 0; i < 9; ++i)
		{
			nodo_inicial.posicion[i] = posicion_inicial[i];
			if (posicion_inicial[i] == 0)
				nodo_inicial.pos_cas_vac = i;
		}

		nodo_inicial.padre = -1;
		nodo_inicial.profundidad = 0;
		nodo_inicial.visitado = false;

		lista.clear();                  //Borramos la lista de nodos
		lista.push_back(nodo_inicial);
	}

	void Taquin::expandir(const size_t indice, const bool amplitud) {
		// Te dice que nodos son tus hijos
		static const unsigned matriz_expansion[9][5] = { {2,1,7,0,0},{3,0,2,8,0},{2,1,3,0,0},{3,2,4,8,0},{2,3,5,0,0},{3,4,6,8,0},{2,5,7,0,0},{3,0,6,8,0},{4,1,3,5,7} };
		// filas: numero de casilla
		// columnas: nodos hijo
		//  0 | 1 | 2
		//  7 | 8 | 3
		//  6 | 5 | 4
		//
		//
		struct Nodo_Taquin hijo;
		// Caracteristicas comunes a cualquier hijo que pueda existir:
		hijo.profundidad = lista[indice].profundidad + 1;
		hijo.padre = indice;
		hijo.visitado = false; //Este campo no es necesario en la Busqueda en Amplitud

		if (amplitud && prof != hijo.profundidad) {   // Sólo nos interesa ver cómo va el tema en el caso de amplitud, que será más lento
			prof = hijo.profundidad;
			std::cout << prof << std::endl;
		}
		auto num_hijos = matriz_expansion[lista[indice].pos_cas_vac][0];
		// std::cout<<"Hijos: "<<hijo.profundidad<<" :"<<std::endl;
		for (unsigned i = 0; i < num_hijos; i++)
		{
			hijo.pos_cas_vac = matriz_expansion[lista[indice].pos_cas_vac][i + 1];

			copia_posicion(lista[indice].posicion, hijo.posicion);

			hijo.posicion[lista[indice].pos_cas_vac] = lista[indice].posicion[hijo.pos_cas_vac];
			// Reemplaza el contenido de  # # posición del hijo correspondiente a la que su padre tenía vacía (casilla que se intercambia con el cero)
			//  con el contenido de       * * (casilla del padre donde pasará a estar el cero del hijo)
			// *8*| 0 | 2
			//  7 | 1 | 3
			//  6 | 5 | 4
			//  0 |#8#| 2
			//  7 | 1 | 3
			//  6 | 5 | 4

			hijo.posicion[hijo.pos_cas_vac] = 0;

			if (!repetido(hijo, indice, amplitud)) {
				lista.push_back(hijo);
			}
		}
	}

	void Taquin::amplitud() {
		size_t indice = 0;
		inicializar_lista();    // turns exito false

		while (exito == false && indice < lista.size())
		{
			exito = prueba_meta(lista[indice].posicion, posicion_objetivo);
			expandir(indice, true);
			if (exito == false) {
				++indice;
			}
		}
		if (exito)
			indice_objetivo = indice;
	}

	void Taquin::profundidad(size_t limite) {  //   Tarea a completar
		size_t indice_lista = 0;
		inicializar_lista();

		//  Arbol ejemplo
		  //            A
		  //        / |   \
          //       B  C   D
		  //             /  \
          //            E    F
		  //            |    |
		  //            H    G

		// Desarrollo por profundidad
		  //  [ *A* ]
		  //
		  //  [ A | B C *D* ]
		  //    v
		  //  [ A | B C D | E *F* ]
		  //    v       v
		  //  [ A | B C D | E F | *G* ]
		  //    v       v     v
		  //  [ A | B C D | *E* F | G ]
		  //    v       v    v  v   v
		  // *nodo a expandir*, v= nodo.visiado=true

		while (exito == false && indice_lista < lista.size() /*&& lista[indice_lista].profundidad <= limite*/) {
			// Debugging
			  // for(int nodos=0; nodos<lista.size(); nodos++)
			  // {
			  //   for(int posiciones=0; posiciones<9; posiciones++)
			  //   {
			  //     std::cout<<lista[nodos].posicion[posiciones]<<" ";
			  //   }
			  //   std::cout<<std::endl;
			  // }
			  // std::cout<<std::endl;

			  // for(int i=0; i<9; i++)
			  // std::cout<<lista[indice_lista].posicion[i];
			  // std::cout<<std::endl;
			if (lista[indice_lista].profundidad >= limite) {
				for (int i = lista.size() - 2; i > -1; i--) {
					if (lista[i].visitado == false) {
						indice_lista = i;
						lista.resize(i + 1);
						break;
					}
				}
				if (indice_lista == 0) {
					std::cout << "Déjame sumergirme mas en el problema" << std::endl;
					break;
				}
			}

			exito = prueba_meta(lista[indice_lista].posicion, posicion_objetivo);

			if (exito == false) {
				lista[indice_lista].visitado = true;
				expandir(indice_lista, false);
				if (indice_lista != (lista.size() - 1)) {
					indice_lista = lista.size() - 1;                // Apuntando hacia el último nodo añadido
				}
				else {   // No nodes added
				  // std::cout<<"**********no nodes added*************"<<std::endl;
					bool unsuccesful_end = true;
					for (int i = lista.size() - 2; i > -1; i--) {
						if (lista[i].visitado == false) {
							indice_lista = i;
							unsuccesful_end = false;
							break;
						} //  if
					} //  for -- break exit
					if (unsuccesful_end == true) {
						// std::cout<<"final de la rama"<<std::endl;
						break;
					}
				} //  else
			} //  if
		} //  while -- break exit
		if (exito)
			indice_objetivo = indice_lista;
	}

	bool Taquin::repetido(const Nodo_Taquin& nodo, size_t indice_lista, const bool amplitud) {  //   Tarea a completar
		bool repe = true;

		if (amplitud == true) {     // Amplitud: búsqueda de nodos repetidos solo en ancestros
			int i = indice_lista;
			while (i >= 0)
			{
				for (auto pos = 0; pos < 9; ++pos) {
					if (lista[lista[i].padre].posicion[pos] != nodo.posicion[pos]) {
						repe = false;
						break;
					}
				}
				if (repe == true) {
					return true;
				}
				else {
					repe = true;
				}

				i = lista[i].padre;

				if (i <= 0) {
					return false;
				}
			}
			return false;
		}

		else if (amplitud == false) {   // Profundidad: búsqueda de nodos en toda la lista
			for (auto iter_lista = lista.size() - 1; iter_lista >= 0; iter_lista--) {

				// Debugging
				  // std::cout<<"\nComparemos"<<std::endl;
				  // for(auto pos=0; pos<9; pos++)
				  //   std::cout<<lista[iter_lista].posicion[pos];
				  // std::cout<<std::endl;
				  // for(auto pos=0; pos<9; pos++)
				  //   std::cout<<nodo.posicion[pos];
				  // std::cout<<std::endl;

				for (auto pos = 0; pos < 9; ++pos) {

					if (lista[iter_lista].posicion[pos] != nodo.posicion[pos]) {
						repe = false;
						// std::cout<<" no repetido"<<std::endl;
						break;
					}
				}
				if (repe == true) {
					// std::cout<<" repetido"<<std::endl;
					return true;
				}
				else {
					repe = true;
				}

				if (iter_lista == 0) {
					return false;
				}
			}
			return false;
		}
	}

	void Taquin::solucion() {
		unsigned i, j;
		if (exito == false) {
			std::cout << "No se encontro solucion" << std::endl;
		}
		else {
			unsigned num_posiciones = lista[indice_objetivo].profundidad + 1;
			//unsigned solucion[num_posiciones][9];
			std::vector<std::vector<unsigned>> solucion;
			solucion.resize(num_posiciones + 1);
			for (int i = 0; i < solucion.size(); ++i)
			{
				solucion[i].resize(9);
			}

			int indice = indice_objetivo;  //indice tomara el vaor -1

			for (i = num_posiciones; i--;) { //Mucho cuidado con los unsigned cuando decrementamos
				for (j = 0; j < 9; ++j) {
					solucion[i][j] = lista[indice].posicion[j];
				}
				indice = lista[indice].padre;
			}
			for (i = 0; i < num_posiciones; ++i) {
				for (j = 0; j < 9; ++j) {
					std::cout << solucion[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "Numero de pasos: " << num_posiciones << std::endl;
		}
	}

} // namespace taquin
