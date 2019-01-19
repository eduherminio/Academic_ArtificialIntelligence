//Cargamos los parametros del algoritmo genetico
template<typename T>
void Genetico_Tsp<T>::inicializacion(const unsigned num_ciudades)
{
	// Inicializa parametros
	num_individuos = num_ciudades * 0.5;
	num_generaciones = num_ciudades * 200;
	probabilidad_mutacion = 0.02;
	double porcentaje_elite = 0.1;
	tam_torneo = num_ciudades / 10;
	if (porcentaje_elite<0 || porcentaje_elite>0.5)
	{
		std::cout << "Wrong elitism percentage\n";
	}
	num_individuos_elite = static_cast<unsigned>(porcentaje_elite*num_individuos + 0.5);
	if (num_individuos_elite % 2 == 1)  //Numero par para facilitar que los cruces sean pares
		++num_individuos_elite;

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	rng.seed(seed);
	aleatorio_0_a_1 = std::uniform_real_distribution<double>(0, 1);
	aleatorio_num_individuos = std::uniform_int_distribution<unsigned>(0, num_individuos - 1);
	++estado_inicializacion;

	std::cout << "num_individuos:\t" << num_individuos << std::endl;
	std::cout << "num_generaciones:\t" << num_generaciones << std::endl;
	std::cout << "tam_torneo:\t" << tam_torneo << std::endl;
	std::cout << "porcentaje_elite:\t" << porcentaje_elite << std::endl;
	std::cout << "probabilidad_mutacion:\t" << probabilidad_mutacion << std::endl;
}

template<typename T>
void Genetico_Tsp<T>::set_seleccion(const Seleccion tipo_seleccion)
{
	switch (tipo_seleccion)
	{
	case Seleccion::torneo_determinista:
		seleccion = [this]()
		{
			return(seleccion_torneo_determinista());
		};
		break;
	case Seleccion::torneo_probabilista:
		assert(false && "No implementado");
		break;
	case Seleccion::ruleta:
		assert(false && "No implementado");
		break;
	}
	++estado_inicializacion;
}

template<typename T>
void Genetico_Tsp<T>::ejecutar(T& individuo, unsigned num_ciudades)
{
	inicializacion(num_ciudades);

	assert(estado_inicializacion == 2 && "No se ha inicializado correctamente el algoritmo genetico");    // Selección del tipo de selección / inicializar parámetros antes de empezar

	// 1. Se pasa individuo porque tiene la matriz de ciudades (podía haberse mandado directamente esto)
	crea_poblacion_inicial(individuo);

	// 2. Ordenamos la poblacion por orden de puntuacion
	ordena_por_puntuacion();

	std::vector<ruta::Ruta> poblacion_nueva;            // Población a generar, en paralelo con la vieja, y que pasará a sustituir a estas
	poblacion_nueva.reserve(num_individuos);

	// 3. Evaluación
	mejor_puntuacion = poblacion[0].puntuacion();
	iteracion_actual = 0;
	mejor_codigo = poblacion[0].get_codigo();           // Mejor recorrido, en el caso de TSP

	observador.notifica(Evento_Modelo::nuevo_codigo);   // Notificamos a la vista de un nuevo mejor recorrido, para que lo pinte

	abortar = false;
	for (unsigned i = 0; i != num_generaciones; ++i)
	{
		if (abortar)
		{
			return;
		}

		// DONE

		//ELITISMO
		//Completar Alumno ---> Añade a poblacion_nueva los individuos de la elite
		// Muy parecido a uno de las transparencias
		// Meter a la población nueva las élites de la población nueva, con un bucle for

		for (unsigned n_elite = 0; n_elite < num_individuos_elite; ++n_elite)
		{
			poblacion_nueva.push_back(poblacion[0 + n_elite]);
		}

		// Generar hijos hasta completar el nº de individuos
		// No es un bucle for porque puede haber repetidos
		while (poblacion_nueva.size() != num_individuos)
		{
			//SELECCION
			//Suponemos que los hijos se hacen con operadores de 2 padres
			//Alumno ---> Obten mediante seleccion 2 indices de padre
			//Alumno ---> Asegura que no estan repetidos

			unsigned indice_padre_1, indice_padre_2;
			indice_padre_1 = seleccion();

			do
			{
				indice_padre_2 = seleccion();
			} while (indice_padre_1 == indice_padre_2);

			// std::cout<<indice_padre_1<< " -- "<<indice_padre_2<<std::endl;

			//CRUCE
			//El cruce genera una lista de hijos, tipicamente 1 o 2
			// Mando a los dos padres, y nos devuelve una lista de hijos (lo habitual es que sean 1 o 2)
			// cruce_orden_1()

			//Alumno ---> Calcula la lista de hijos (2 en este caso) mediante el operador cruce_orden_1()

			auto hijos = cruce_orden_1(poblacion[indice_padre_1], poblacion[indice_padre_2]);

			//MUTACION
			// Multar con cierta probabilidad, y comprobar que no está repetido
			// Si la mutación coincide, no se le añade
			for (auto &h : hijos) //Al compilar inicialmente dara error pues hijos no esta creada
			{
				//Alumno ---> Muta al hijo h segun aleatorio_0_a_1(rng)<probabilidad_mutacion
				//Alumno ---> Añade el hijo a la poblacion nueva
				//Alumno ---> Si poblacion nueva esta completa  --> break!
				if (aleatorio_0_a_1(rng) < probabilidad_mutacion)
					h.mutacion();

				if (permutacion_repetida(h))
					continue;

				poblacion_nueva.push_back(h);
				if (poblacion_nueva.size() == num_individuos)
					break;
			}
		}

		//Alumno ---> Actualiza la poblacion, cambiando la vieja por la nueva
		actualiza_poblacion(poblacion_nueva);
		//Alumno ---> ordena por puntuacion la poblacion. Asi nos aseguramos que poblacion[0]
		//Alumno ---> es nuestro mejor individuo y accedemos facilmente a la elite
		ordena_por_puntuacion();

		if (poblacion[0].puntuacion() < mejor_puntuacion) //Notificamos al Controlador: el mejor de la poblaciòn es mejor que el que tenía hasta el momento
		{
			mejor_puntuacion = poblacion[0].puntuacion();
			// std::cout<<" Best: "<<mejor_puntuacion<<std::endl;
			iteracion_actual = i;
			mejor_codigo = poblacion[0].get_codigo();

			observador.notifica(Evento_Modelo::nuevo_codigo);
		}
	}
}

template<typename T>
void Genetico_Tsp<T>::crea_poblacion_inicial(T& individuo)
{
	poblacion.clear();
	do
	{
		individuo.crea_aleatoria();
		//Verificamos que no esta repetido
		if (!permutacion_repetida(individuo))
		{
			poblacion.push_back(individuo);
		}
	} while (poblacion.size() != num_individuos);
	calcula_media_puntuaciones();
	return;
}

template<typename T>
bool Genetico_Tsp<T>::permutacion_repetida(T &individuo)
{
	bool repetido = false;
	double puntuacion = individuo.puntuacion();
	auto codigo1 = individuo.get_codigo();

	for (auto &p : poblacion)
	{
		if (p.puntuacion() == puntuacion) //Filtramos si son distintas
		{
			auto codigo2 = p.get_codigo();
			auto it = std::find(codigo2.begin(), codigo2.end(), codigo1[0]); //it posicion del primer valor en un individuo de la poblacion
			repetido = true;
			for (auto valor : codigo1)
			{
				if (valor != *it)
				{
					repetido = false;
					break;
				}
				else
				{
					++it;
					if (it == codigo2.end())
						it = codigo2.begin();
				}
			}
			if (repetido)
				break;
		}
	}
	return repetido;
}

template<typename T>
void Genetico_Tsp<T>::calcula_media_puntuaciones()
{
	double sumatorio_puntuaciones = 0.;
	// Calcula el sumatorio de todas las puntuaciones de los individuos
	for (auto &individuo : poblacion)
	{
		sumatorio_puntuaciones += individuo.puntuacion();
	}
	media_puntuaciones = sumatorio_puntuaciones / num_individuos;
}

template<typename T>
void Genetico_Tsp<T>::ordena_por_puntuacion()
{
	std::sort(poblacion.begin(), poblacion.end(), [](const T& ind1, const T& ind2)
	{
		return(ind1.puntuacion() < ind2.puntuacion());
	});
}

template<typename T>
unsigned Genetico_Tsp<T>::seleccion_torneo_determinista()
// DONE
// Tantos aleatorios como tamaño del torneo, y selecciono el mejor
//Ahora mismo el torneo tiene un unico contendiente, luego siempre gana
//Notese que en este problema es de minimizacion
//Completar por el alumno
//Recuerde: la variable tam_torneo contiene el numero de contendientes en el torneo
{
	// unsigned valor_aleatorio=aleatorio_num_individuos(rng); //Valor entre 0 y num_individuos-1
	// unsigned ganador=valor_aleatorio;
	// return ganador;
	typedef std::pair<double, unsigned> myType;
	std::vector<myType> v_candidatos;
	// We don't use a map since no repetitive values can be stored. It would avoid sort();
	v_candidatos.reserve(tam_torneo);  // Not a vector!
	while (v_candidatos.size() != tam_torneo)
	{
		unsigned valor_aleatorio = aleatorio_num_individuos(rng);  // [0, num_individuos-1]
		v_candidatos.push_back(std::make_pair(poblacion[valor_aleatorio].puntuacion(), valor_aleatorio));
	}

	std::sort(v_candidatos.begin(), v_candidatos.end(), [](const myType& a, const myType& b)  // not a vector
	{
		return(a.first < b.first);
	});

	return v_candidatos.front().second;
}

template<typename T>
unsigned Genetico_Tsp<T>::seleccion_torneo_probabilista()
{
	//No implementado
	return 1;
}

template<typename T>
unsigned Genetico_Tsp<T>::seleccion_ruleta()
{
	//No implementado
	return 1;
}

template<typename T>
std::vector<T> Genetico_Tsp<T>::cruce_orden_1(const T &padre_1, const T &padre_2)
{
	auto p1 = padre_1.get_codigo();
	auto p2 = padre_2.get_codigo();

	auto h1(p1);  //Copiamos los codigos de los padres en los hijos
	auto h2(p2);

	std::uniform_int_distribution<unsigned> aleatorio_tam_codigo(0, padre_1.get_codigo().size() - 1); //Entre 0 y tam_codigo-1
	unsigned inicio = aleatorio_tam_codigo(rng);
	unsigned fin = aleatorio_tam_codigo(rng);

	unsigned tam_representacion = p1.size();

	//Por comodidad, reordenamos la secuencia permutacion pasando a ser inicio el primer elemento de los hijos
	//Sobreescribimos la secuencia entre inicio y fin del padre_1 en hijo_2 y viceversa
	unsigned indice = inicio;
	unsigned contador = 0;
	unsigned num_cruces;
	if (fin >= inicio)
		num_cruces = 1 + fin - inicio;
	else
		num_cruces = 1 + tam_representacion - inicio + fin;

	for (unsigned i = 0; i != tam_representacion; ++i)
	{
		if (contador < num_cruces)
		{
			h1[i] = p2[indice];
			h2[i] = p1[indice];
		}
		else
		{
			h1[i] = p1[indice];
			h2[i] = p2[indice];
		}
		if (++indice == tam_representacion)
			indice = 0;
		++contador;
	}

	//Ahora inicio=0 y fin=num_cruces-1
	fin = num_cruces - 1;
	inicio = 0;
	//Detectamos repeticiones

	std::vector<unsigned> repetidos_h1, repetidos_h2;
	repetidos_h1.reserve(fin);
	repetidos_h2.reserve(fin);
	for (unsigned i = 0; i != tam_representacion; ++i)
	{
		if (i > fin)
		{
			//Buscamos las repeticiones dentro de la secuencia copia y lo marcamos
			for (unsigned j = 0; j <= fin; ++j)
			{
				if (h1[i] == h1[j])
				{
					repetidos_h1.push_back(i);
					break;
				}
			}
			for (unsigned j = 0; j <= fin; ++j)
			{

				if (h2[i] == h2[j])
				{
					repetidos_h2.push_back(i);
					break;
				}
			}
		}
	}

	// cout<<"Colisiones marcadas\n";
	//Reparamos las colisiones
	unsigned indice_h1 = 0;
	unsigned indice_h2 = 0;

	for (unsigned i = 0; i != repetidos_h1.size(); ++i)
	{
		while (std::find(h1.begin(), h1.begin() + fin + 1, h2[indice_h2]) != h1.begin() + fin + 1)
		{
			++indice_h2;
		}
		h1[repetidos_h1[i]] = h2[indice_h2];
		++indice_h2;
	}

	for (unsigned i = 0; i != repetidos_h2.size(); ++i)
	{
		while (std::find(h2.begin(), h2.begin() + fin + 1, h1[indice_h1]) != h2.begin() + fin + 1)
		{
			++indice_h1;
		}
		h2[repetidos_h2[i]] = h1[indice_h1];
		++indice_h1;
	}

	std::vector<T> hijos;

	hijos.push_back(padre_1);
	hijos.push_back(padre_2);

	hijos[0].set_codigo(h1); //set codigo actualiza el codigo y calcula su puntuacion
	hijos[1].set_codigo(h2);

	return hijos;
}

template<typename T>
void Genetico_Tsp<T>::actualiza_poblacion(std::vector<T> &poblacion_nueva)
{
	poblacion.clear();                   //Borramos la poblacion actual
	poblacion_nueva.swap(poblacion);     //Cargamos la nueva en la actual
	calcula_media_puntuaciones();
	std::cout << media_puntuaciones << std::endl; // DONE
}
