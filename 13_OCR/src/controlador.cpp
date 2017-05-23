#include "../header/controlador.h"

#include <thread>

namespace controlador
{
  void Controlador::registra_observadores()
  {
    vista.registra_observador(Evento_Vista::ejecutar,[this]()
    {
      ejecuta_knn();
    });
    vista.registra_observador(Evento_Vista::cargar, [this]()
    {
      carga_imagenes_mnist();
      vista.set_boton_cargar(false);
      vista.muestra_botones_seleccion();
    });
    vista.registra_observador(Evento_Vista::detener, std::bind(&Controlador::detiene_knn,this));
    vista.registra_observador(Evento_Vista::iniciar_programa, [this]()
    {
      inicio_vista=true;
    });

    vista.registra_observador(Evento_Vista::finalizar_programa, std::bind(&Controlador::finaliza_programa,this));
  }

  bool Controlador::carga_imagenes_mnist()
  {
    knn.cargar_datos_entrenamiento(mnist.get_imagenes_entrenamiento());
    knn.cargar_datos_test(mnist.get_imagenes_test());
    knn.cargar_etiquetas_entrenamiento(mnist.get_etiquetas_entrenamiento());
    knn.cargar_etiquetas_test(mnist.get_etiquetas_test());
    return true;
  }

  void Controlador::inicia_programa()
  {
    inicio_vista=true;
    //La vista nos garantiza que todos sus recursos estan listos
  }
  void Controlador::finaliza_programa()
  {
    fin_vista=true;
    detiene_knn();
    c_v_barrera_knn.notify_one(); //Desbloqueamos hilo ejecutar para acabar el programa
    while(!fin_algoritmo);
  }

  void Controlador::ejecuta_knn()
  {
    vista.set_visualiza_imagen(false);
    vista.oculta_label_resultado();
    auto k=vista.k();
    auto indice=vista.indice();
    if(k<1 || k>mnist.get_imagenes_entrenamiento().size()-1)
    {
      vista.muestra_error("Invalid k value");
    }
    else if(indice<0 || indice>mnist.get_imagenes_test().size()-1)
    {
      vista.muestra_error("Invalid index");
    }
    else
    {
      std::unique_lock<std::mutex>u_l(barrera_knn);    //Bloqueamos
      vista.set_boton_ejecutar(false);
      vista.oculta_label_error();
      vista.set_imagen(sf_extension::raw_a_sfml(mnist.get_imagen_test(indice),28,28));
      vista.set_visualiza_imagen(true);
      inicio_algoritmo=true;
      c_v_barrera_knn.notify_one(); //Desbloqueamos hilo ejecutar()
    }
  }

  void Controlador::detiene_knn()
  {
    knn.detener();
    while(!fin_algoritmo);
  }
  void Controlador::ejecutar()
  {
    //Estas dimensiones podrian ser leidas desde un fichero de configuracion
    //o elegidas por linea de comandos
    const unsigned alto=400;      // FIXED SIZE
    const unsigned ancho=300;

    //Lanzamos el hilo vista
    hilo_vista=std::thread(&Vista::ejecutar,&vista,ancho,alto);


    inicio_vista=false;
    while(!inicio_vista);  //Esperamos a que la vista este inicializada

    fin_vista=false;

    while(!fin_vista)
    {
      // Bloqueamos /////////////////
      std::unique_lock<std::mutex>u_l(barrera_knn);
      static bool primera_vez=true;
      if(primera_vez)
      {
        vista.set_boton_cargar(true);
        primera_vez=false;
      }
      inicio_algoritmo=false;
      while(!inicio_algoritmo && !fin_vista) //fin_vista se pone a true al matar la ventana de la vista
      c_v_barrera_knn.wait(u_l); //Esperamos hasta que se inicie knn o finalicemos la vista
      //////////////////////////////////////////////////////////////////

      if(!fin_vista)
      {
        fin_algoritmo=false;

        // hilo_modelo=std::thread(knn.ejecutar,&knn,vista.k(),vista.indice());
        hilo_modelo=std::thread(&Knn<std::vector<uint8_t>,uint8_t>::ejecutar, &knn, vista.k(), vista.indice(), mnist.get_num_etiquetas());

        if(hilo_modelo.joinable())
        hilo_modelo.join();

        vista.muestra_resultado(knn.get_etiqueta_ganadora());
        vista.set_boton_ejecutar(true);

        fin_algoritmo=true;
      }
      fin_algoritmo=true;
    }
    if(hilo_vista.joinable())
    {
      hilo_vista.join();
    }
  }
}
