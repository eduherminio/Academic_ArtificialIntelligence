
#include "../header/controlador.h"
#include "../header/nodo_trayectoria.h"
#include "../header/problema_busqueda.h"
#include <thread>

namespace controlador
{
  void Controlador::registra_observadores()
  {
    Observador<Evento_Vista>& observador_vista=vista->get_observador();
    observador_vista.registra_observador(Evento_Vista::EJECUTAR, std::bind(&Controlador::ejecuta_modelo,this));
  }
  void Controlador::ejecutar()
  {
    hilo_vista=std::thread(&Controlador::ejecuta_vista,this);

  }

  void Controlador::ejecuta_vista()
  {
    vista->ejecutar();
  }
  void Controlador::ejecuta_modelo()
  {
    hilo_modelo=std::thread(&Controlador::busca_trayectoria,this);
    hilo_modelo.join();
  }


  //  FUNCIONES DEL CONTROLADOR RELATIVAS AL MODELO
  mapa::Punto_2d pair_to_punto_2d(std::pair<unsigned,unsigned> p_e)
  {
    mapa::Punto_2d p_s;
    p_s.x=p_e.first;
    p_s.y=p_e.second;
    return p_s;
  }
  void Controlador::inicializa_mapa()
  {
    auto pos_inicial=pair_to_punto_2d(vista->pos_casilla_inicial());
    auto pos_final=pair_to_punto_2d(vista->pos_casilla_final());

    std::vector<mapa::Punto_2d> muros;
    for(auto &pos:vista->pos_muros())
    {
      muros.push_back(pair_to_punto_2d(pos));
    }
    mapa->crea_mapa(filas,columnas,pos_inicial,pos_final,muros);
  }
  void Controlador::busca_trayectoria()
  {
    //        rejilla.borra_trayectoria();
    inicializa_mapa();
    nodo_trayectoria::Nodo_trayectoria::set_mapa(*mapa);
    nodo_trayectoria::Nodo_trayectoria nodo_inicial(mapa->get_nodo_inicial().x,mapa->get_nodo_inicial().y);
    nodo_trayectoria::Nodo_trayectoria nodo_objetivo(mapa->get_nodo_final().x,mapa->get_nodo_final().y);

    problema_busqueda::Problema_busqueda<nodo_trayectoria::Nodo_trayectoria> problema(nodo_inicial,nodo_objetivo);
    std::vector<std::pair<unsigned,unsigned>> solucion;

    // if(problema.amplitud())
    // if(problema.profundidad())
    // if(problema.profundidad())
    // if(problema.coste_uniforme())
    // if(problema.voraz())
    if(problema.a_estrella())
    {
      for(auto nodo:problema.get_solucion())
      {
        solucion.push_back({nodo.get_x(),nodo.get_y()});
      }

      std::cout<<"Found\n";
    }
    else
    {
      std::cout<<"Not found\n";
    }
    vista->trayectoria_encontrada(solucion,problema.get_nodos_expandidos());
  }
}
