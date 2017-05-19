// Otro método

#include "../header/problema_busqueda_taquin.h"
#include <unordered_set>
#include <queue>
#include <iostream>

namespace taquin
{
  bool Problema_busqueda_taquin::a_estrella_p_i()
  {
    solucion.clear();
    struct Nodo
    {
      Nodo_taquin nodo;
      size_t padre;
      size_t coste_actual;
      bool visitado;
    };

    std::vector<Nodo> lista; //{nodo,padre,coste_actual}
    std::unordered_set<std::string>claves;

    size_t nuevo_limite_coste=heuristica(nodo_inicial,nodo_objetivo);
    size_t limite_coste=0;

    bool exito=false;
    nodos_expandidos=0;
    while(exito==false && nuevo_limite_coste>limite_coste)
    {
      std::cout<<"Nuevo limite:"<<nuevo_limite_coste<<" "<<lista.size()<<" "<<claves.size()<<"\n";
      //Inicializacion
      lista.push_back({nodo_inicial,0,0,false});
      claves.insert(nodo_inicial.get_clave());
      size_t indice=0;
      limite_coste=nuevo_limite_coste;
      while(exito==false && lista.size()>0)
      {
        bool nuevo_calculo_limite=false;
        if(lista[indice].visitado==false)
        {
          //    std::cout<<claves.bucket_count()<<"\n"; //Evolucion del tamanho de la tabla hash
          lista[indice].visitado=true;
          ++nodos_expandidos;
          exito=(lista[indice].nodo==nodo_objetivo); //Prueba de meta

          if(exito==false)
          {
            auto hijos=lista[indice].nodo.expandir();

            for(auto& x:hijos)
            {
              auto clave_hijo=x.get_clave();
              if(claves.count(clave_hijo)==0) // Repetido?
              {
                auto coste_actual_hijo=lista[indice].coste_actual+coste_operador(lista[indice].nodo,x);
                auto coste_total=coste_actual_hijo+heuristica(x,nodo_objetivo);
                //Vemos si esta dentro del limite
                if(coste_total<=limite_coste)
                {
                  claves.insert(clave_hijo);
                  lista.push_back({x,indice,coste_actual_hijo,false});
                }
                else
                {
                  if(nuevo_calculo_limite==false)
                  {
                    nuevo_calculo_limite=true;
                    nuevo_limite_coste=coste_total;
                  }
                  else
                  {
                    if(coste_total<nuevo_limite_coste)
                    {
                      nuevo_limite_coste=coste_total;
                    }
                  }
                }
              }
            }
          }
        }
        else
        {
          claves.erase(lista[indice].nodo.get_clave()); //Importante hacerlo antes que pop_back()
          lista.pop_back();
        }
        indice=lista.size()-1;
      }

      if(exito)
      {
        while(indice!=0)
        {
          solucion.push_back(lista[indice].nodo);
          indice=lista[indice].padre;
        }
        solucion.push_back(lista[indice].nodo);
      }
    }

    return exito;
  }
}
