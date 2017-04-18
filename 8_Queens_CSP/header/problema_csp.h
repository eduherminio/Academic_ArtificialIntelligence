#ifndef PROBLEMA_CSP_H_INCLUDED
#define PROBLEMA_CSP_H_INCLUDED

#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include <iostream>

namespace csp
{
  enum class Seleccion_variable {aleatoria,estatica,mrv};
  enum class Algoritmo {bt,fc,fc_ac1,fc_ac1_necesarios,fc_necesarios};
  template<typename T>
  class Problema_csp
  {
  public:
    Problema_csp() {}

    bool resolver(Seleccion_variable sel_var=Seleccion_variable::estatica,Algoritmo algoritmo=Algoritmo::fc)
    {
      tipo_seleccion_variable(sel_var);

      if(algoritmo==Algoritmo::bt)
      return (backtracking());
      else
      {
        seleccion_algoritmo_look_ahead(algoritmo);
        return (look_ahead());
      }
    }
    std::vector<std::pair<unsigned,T>>& get_solucion()
    {
      return solucion;
    }
    std::size_t get_nodos_expandidos() const
    {
      return nodos_expandidos;
    }
  protected:
    unsigned num_variables;
    std::vector<std::vector<T>>dominio;
    std::vector<std::vector<std::pair<unsigned,T>>> lista_exclusiones_dominio;
    std::vector<std::pair<unsigned,T>>solucion;
  private:
    std::vector<unsigned>variables_sin_etiquetar; //Vector instrumental que almacena las variables a�n fuera de la soluci�n
    unsigned nodos_expandidos; //Para comparar entre algoritmos

    void inicializa();
    //FUNCIONES QUE CARGAN EL DOMINIO Y DESCRIBEN EL GRAFO DE RESTRICCIONES
    //virtuales pues dependen de cada problema particular
    virtual bool relacionadas(const unsigned var_1,const unsigned var_2)=0;
    virtual bool consistente(const unsigned var_1,const T val_1,const unsigned var_2,const T val_2)=0;
    virtual bool consistente(const unsigned variable,const T valor)=0;
    virtual void inicializa_dominio()=0;

    //SELECCION Y BLOQUEO VARIABLE
    void tipo_seleccion_variable(const Seleccion_variable sel_var);
    std::function<unsigned (void)> seleccion_variable; //Puntero a funcion seleccion_variable
    unsigned seleccion_variable_estatica();
    unsigned seleccion_variable_aleatoria();
    unsigned seleccion_variable_mrv();
    void bloquea_variable();
    void libera_variable(const unsigned variable);

    //ALGORITMOS

    //1) Backtracking
    bool backtracking(); //--> Funci�n general bactracking
    bool expandir_bt(const unsigned variable,std::vector<std::pair<unsigned,T>>& lista_asignaciones);
    virtual void restaura_estado(const std::pair<unsigned,T> &asignacion)=0;  //Llamada virtual diferente para cada problema
    virtual void actualiza_estado(const std::pair<unsigned,T> &asignacion)=0; //Llamada virtual diferente para cada problema
    //2) Look ahead
    bool look_ahead(); //--> Funci�n general look ahead
    void seleccion_algoritmo_look_ahead(const Algoritmo algoritmo);
    std::function<bool (const std::pair<unsigned,T>&)> actualiza_dominio; //Puntero a funcion actualiza_dominio
    void restaura_dominio(const unsigned variable);
    //2) ->Forward checking
    bool actualiza_dominio_fc(const std::pair<unsigned,T> &asignacion);
    //////////////////////////////////////////////////////////////////////////////////////
    //2) ->Forward checking con ac1
    bool actualiza_dominio_fc_ac1(const std::pair<unsigned,T> &asignacion);
    bool actualiza_dominio_ac1(const unsigned variable);
    bool revisar_ac1(const unsigned variable,const unsigned var_i,const unsigned var_j);
    //////////////////////////////////////////////////////////////////////////////////////

    //GENERADOR ALEATORIOS
    std::mt19937 rng;

    //PARA DEPURACION
    void imprime_dominio();
  };



  template <typename T>
  void Problema_csp<T>::inicializa()
  {
    inicializa_dominio(); //Llamada virtual diferente para cada problema

    //Borra listas
    lista_exclusiones_dominio.clear();
    lista_exclusiones_dominio.resize(num_variables);
    variables_sin_etiquetar.clear();
    for(unsigned i=0; i!=num_variables; ++i) //Todas las variables sin etiquetar(sin asignar un valor) inicialmente
    variables_sin_etiquetar.push_back(i);

    solucion.clear();
    //Genera semilla para aleatorios
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(seed);
  }

  //Para depuracion
  template <typename T>
  void Problema_csp<T>::imprime_dominio()
  {
    for(unsigned i=0; i!=num_variables(); ++i)
    {
      for(auto j:dominio(i))
      {
        std::cout<<j<<" ";
      }
      std::cout<<std::endl;
    }
  }

  #include "csp_seleccion_variable.h"
  #include "csp_seleccion_algoritmo.h"
  #include "csp_backtracking.h" //Fichero de plantillas
  #include "csp_look_ahead.h" //Fichero de plantillas

}

#endif // PROBLEMA_CSP_H_INCLUDED
