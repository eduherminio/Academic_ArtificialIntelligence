#include "../header/controlador.h"
// #include "../header/dialogo_fichero_windows.h"
#include "../header/dialogo_fichero_linux.h"

#include <thread>

namespace controlador
{
  void Controlador::registra_observadores()
  {
    Observador<Evento_Vista>& observador_vista=vista.get_observador();
    vista.registra_observador(Evento_Vista::ejecutar,[this]()
    {
      ejecuta_genetico_tsp();
    });
    vista.registra_observador(Evento_Vista::cargar, std::bind(&Controlador::carga_problema_tsplib,this));
    vista.registra_observador(Evento_Vista::detener, std::bind(&Controlador::detiene_genetico_tsp,this));
    vista.registra_observador(Evento_Vista::iniciar_programa, [this]()
    {
      inicio_vista=true;
    });
    vista.registra_observador(Evento_Vista::finalizar_programa, std::bind(&Controlador::finaliza_programa,this));

    Observador<Evento_Modelo>& observador_modelo=genetico_tsp.get_observador();
    genetico_tsp.registra_observador(Evento_Modelo::nuevo_codigo,[this]()
    {
      push_datos();
    });
  }

  bool Controlador::carga_problema_tsplib()
  {
    std::string fichero_tsp;
    if(lee_nombre_fichero(fichero_tsp))
    {
      ciudades::Ciudades ciudades;
      ciudades.carga_ciudades(fichero_tsp);  //Carga el vector de coordenadas y la matriz de distancias
      if(set_coordenadas_visualizacion(ciudades))
      {
        vista.set_recorrido_optimo(ciudades.get_codigo_optimo());
        vista.set_texto_distancia_optima("Optimum : "+parche::to_string(ciudades.calcula_distancia(ciudades.get_codigo_optimo())));
        vista.set_texto_iteracion("");
        vista.set_texto_mejor_distancia("");
        ruta.inicializa_ruta(std::move(ciudades));
        auto recorrido=ruta.get_codigo();
        vista.muestra_boton_ejecutar();
        return true;
      }
    }
    return false;
  }

  void Controlador::inicia_programa()
  {
    inicio_vista=true;
    //La vista nos garantiza que todos sus recursos estan listos
  }
  void Controlador::finaliza_programa()
  {
    fin_vista=true;
    detiene_genetico_tsp();
    c_v_barrera_tsp.notify_one(); //Desbloqueamos hilo ejecutar para acabar el programa
    while(!fin_hilos); //Nos aseguramos que los hilos tsp y datos han finalizado
    while(!fin_algoritmo);
  }

  void Controlador::ejecuta_genetico_tsp()
  {
    std::unique_lock<std::mutex>u_l(barrera_tsp);    //Bloqueamos añadir nuevo recorrido
    vista.oculta_boton_cargar();
    vista.oculta_boton_ejecutar();
    vista.muestra_boton_detener();
    inicio_algoritmo=true;
    c_v_barrera_tsp.notify_one(); //Desbloqueamos hilo ejecutar()
  }

  void Controlador::detiene_genetico_tsp()
  {
    genetico_tsp.detener();
    while(!fin_algoritmo);
    vacia_datos();
  }
  void Controlador::ejecutar()
  {
    //Estas dimensiones podrian ser leidas desde un fichero de configuracion
    //o elegidas por linea de comandos
    const unsigned ancho=960; //Dimensiones de la ventana
    const unsigned alto=720;
    const unsigned ancho_panel=250;

    //Lanzamos el hilo vista
    hilo_vista=std::thread(&Vista::ejecutar,&vista,ancho,alto,ancho_panel);

    inicio_vista=false;
    while(!inicio_vista);  //Esperamos a que la vista este inicializada

    fin_vista=false;

    while(!fin_vista)
    {
      // Bloqueamos /////////////////
      std::unique_lock<std::mutex>u_l(barrera_tsp);
      vista.oculta_boton_detener();
      vista.oculta_boton_ejecutar();
      vista.muestra_boton_cargar();
      inicio_algoritmo=false; //Se pone a true al pulsar boton_cargar()
      while(!inicio_algoritmo && !fin_vista) //fin_vista se pone a true al matar la ventana de la vista
      c_v_barrera_tsp.wait(u_l); //Esperamos hasta que se inicie un TSP o finalicemos la vista
      //////////////////////////////////////////////////////////////////

      fin_hilos=false;
      if(!fin_vista)
      {
        hilo_cola_datos=std::thread(&Controlador::pop_datos,this);

        fin_algoritmo=false;
        // hilo_modelo=std::thread(genetico_tsp.ejecutar,&genetico_tsp,std::ref(ruta));

        // auto ff=[this](){&Genetico_Tsp<ruta::Ruta>::ejecutar(std::ref(ruta));};
        // hilo_modelo=std::thread(&ff);

       hilo_modelo=std::thread(&Genetico_Tsp<ruta::Ruta>::ejecutar,&genetico_tsp,std::ref(ruta));

        if(hilo_modelo.joinable())
        hilo_modelo.join();

        fin_algoritmo=true;

        c_v_barrera_datos.notify_one();      //Desbloqueamos el hilo pop_datos()
        if(hilo_cola_datos.joinable())
        hilo_cola_datos.join();
      }
      fin_algoritmo=true;
      fin_hilos=true;
    }
    if(hilo_vista.joinable())
    {
      hilo_vista.join();
    }
  }


  void Controlador::push_datos()
  {
    std::unique_lock<std::mutex>u_l(barrera_datos);    //Bloqueamos eliminar recorrido
    datos.push({genetico_tsp.get_codigo(),genetico_tsp.get_mejor_puntuacion(),genetico_tsp.get_iteracion_actual()});
    c_v_barrera_datos.notify_one();
  }
  void Controlador::pop_datos()
  {
    while(!fin_algoritmo)
    {
      std::unique_lock<std::mutex>u_l(barrera_datos);    //Bloqueamos añadir nuevo recorrido
      while(datos.empty() && !fin_algoritmo)
      {
        c_v_barrera_datos.wait(u_l);
      }

      if(fin_algoritmo)
      {
        while(!datos.empty())
        {
          auto dato=std::move(datos.front());
          datos.pop();
          vista.actualiza_recorrido(dato.recorrido,"Iteration: "+parche::to_string(dato.iteracion),"Distance: "+parche::to_string(dato.mejor_distancia));
        }
      }
      else
      {
        auto dato=std::move(datos.front());
        datos.pop();
        u_l.unlock(); //Desbloqueamos lo antes posible
        vista.actualiza_recorrido(dato.recorrido,"Iteration: "+parche::to_string(dato.iteracion),"Distance: "+parche::to_string(dato.mejor_distancia));
      }
    }
  }
  void Controlador::vacia_datos()
  {
    std::unique_lock<std::mutex>u_l(barrera_datos);    //Bloqueamos
    while(!datos.empty()) //Vaciamos la cola de datos
    datos.pop();
  }

  // Transfiere coordenadas desde la clase Ciudades a la clase Canvas
  bool Controlador::set_coordenadas_visualizacion(const ciudades::Ciudades& ciudades)
  {
    double x_min,x_max,y_min,y_max;
    ciudades.calcula_valores_extremos(x_min,x_max,y_min,y_max);
    if(x_min==x_max || y_min==y_max) //Las ciudades estan en una vertical o en una horizontal
    {
      return false;  //El problema es trivial y no tiene sentido buscar una solucion
    }

    std::vector<std::pair<unsigned,unsigned>> coordenadas_canvas; //Coordenadas de las ciudades normalizadas a las dimensiones del CANVAS

    unsigned x_sup_izq,y_sup_izq,x_inf_der,y_inf_der;
    vista.get_rectangulo_canvas(x_sup_izq,y_sup_izq,x_inf_der,y_inf_der);

    double x,y;   //coordenadas reales
    double xn,yn; //coordenadas reales normalizadas en [0,1]
    unsigned xv,yv;   //coordenadas int ajustadas al espacio de visualizacion
    for(auto &p:ciudades.get_coordenadas())
    {
      x=p.first;
      y=p.second;
      xn=(x-x_min)/(x_max-x_min);  //No tenemos division por 0 al garantizarlo mas arriba
      yn=(y-y_min)/(y_max-y_min);
      xv=unsigned(x_sup_izq+xn*(x_inf_der-x_sup_izq));
      yv=unsigned(y_sup_izq+yn*(y_inf_der-y_sup_izq));
      coordenadas_canvas.push_back({yv,xv});  //Coordenadas cambiadas
    }
    vista.set_coordenadas(coordenadas_canvas);
    return true;
  }


}
