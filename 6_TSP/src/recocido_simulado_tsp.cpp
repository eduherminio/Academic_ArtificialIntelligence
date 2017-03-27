//FELIX MIGUEL TRESPADERNE
//INTELIGENCIA ARTIFICIAL APLICADA A�O 2017
//Inspirado en Simulated Annealing Methods, secci�n 10.9 del libro
//NUMERICAL RECIPES IN C


#include "../header/recocido_simulado_tsp.h"

void Recocido_simulado_TSP::inicializacion(const unsigned n_d,const unsigned n_p,const unsigned n_e_m,
  const double t,const double f_d)
  {
    //A completar: esta funci�n debe modificarse para que sintonice los par�metros de forma autom�tica
    num_descensos=n_d;
    num_permutaciones=n_p;
    num_exitos_maximo=n_e_m;
    temperatura=t;
    factor_descenso=f_d;
  }


  // Calcula una ruta mediante recocido simulado
  void Recocido_simulado_TSP::ejecutar(ruta::Ruta& ruta)
  {
    std::cout<<std::endl<<"Optimizing"<<std::endl<<"(...)"<<std::endl;
    set_v_lookup_table();
    // TO-DO: Initialización
    std::mt19937 rng;
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(seed);
    std::uniform_real_distribution<double> aleatorio_0_a_1(0,1);

    //A completar: el alumno invocar� desde aqu� a inicializacion para
    //sintonizar los parametros del algoritmo
    //inicializacion()
    ruta.inicializa_recorrido();
    auto distancia_actual= ruta.get_distancia_actual();
    mejor_distancia = distancia_actual;
    iteracion_actual=0;
    mejor_recorrido = ruta.get_recorrido();

    observador.notifica(Evento_Modelo::nuevo_recorrido);

    abortar=false;
    for(;iteracion_actual<num_descensos;++iteracion_actual)   // Algoritmo que itera entre las temperaturas
    {
      unsigned num_exitos=0;
      for(unsigned j=0; j<num_permutaciones; j++)           // Permutaciones para cada una de las temperaturas (copia del artículo de original recipes del campus)
      {
        if(abortar)   // Señal del hilo de la vista para que se detenga el algoritmo
        {
          return;
        }
        ruta.crea_recorrido_vecino();                     // Crea un recorrido que se le parezca -> recorrido provisional

        auto distancia_provisional = ruta.get_distancia_provisional();
        auto incremento=distancia_actual-distancia_provisional;   // incremento>0 -> mejora

        // TO-DO: Hacer una LUT para la funcion exp(incremento/temperatura)
        auto rnd_value= aleatorio_0_a_1(rng);
        double actual= (double)incremento/temperatura;
        size_t index= std::abs(round(1000 * (actual)));
        if(index > 9999)
          index=9999;
        // if(incremento>0 || aleatorio_0_a_1(rng) < exp(incremento/temperatura)) //DECISON METROPOLIS
        if(incremento>0 || rnd_value < v_lookup_table.at(index))
        {
          //Actualizamos la ruta actual
          ruta.actualiza_ruta();
          distancia_actual=distancia_provisional;

          if(distancia_actual<mejor_distancia)        // Nofitica el controlador para que actualice la vista
          {  //Notificamos al Controlador
            mejor_distancia = distancia_actual;
            mejor_recorrido = ruta.get_recorrido();
            observador.notifica(Evento_Modelo::nuevo_recorrido);
          }
          if(++num_exitos>num_exitos_maximo)        // Si, para una temperatura, muchos exitos -> sistema muy caliente (acepto cualquier cosa) -> corto el bucle interno y enfrío la temperatura
            break;
        }
      }
      if(num_exitos==0)                                 // Si, para una temperatura, ningún éxito -> Fin del algoritmo ()
        break;
      temperatura*=factor_descenso;
    }
    std::cout<<"**END**"<<std::endl;
  }

  void Recocido_simulado_TSP::set_v_lookup_table()
  {
    v_lookup_table.push_back(exp(0));
    for(int i=1; i<10000; ++i)
    {
      double exponent= -(double)i/1000;         // [-0.001, -9.999];
      v_lookup_table.push_back(exp(exponent));
    }
  }

  double Recocido_simulado_TSP::get_v_lookup_table(int key)
  {
    if(key<0)
      return v_lookup_table.at(-key);
    else
      return v_lookup_table.at(2*key);
  }
