#ifndef PROBLEMA_CSP_H_INCLUDED
#define PROBLEMA_CSP_H_INCLUDED

#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include <iostream>
#include <cassert>
#include <algorithm>


/*
********
Variables: numerables, nº de filas en esta caso.
(T) es el valor de esa variable, que en nuestro caso también es unsigned (el nº de columna en el que está la reina)

std::vector<std::pair<unsigned,T>> solucion;
	// vector de variables y valores que forman la solución
std::vector<unsigned> variables_sin_etiquetar;
	// vector de variables aún fuera de la solución
std::vector<std::vector<T>> dominio;
	// vector de valores que puede tener cada variable
	// vector de variables
std::vector<std::vector<std::pair<unsigned,T>>> lista_exclusiones_dominio;	// sólo fc
	// conjunto de variable y valor imposible
	// vector de conjuntos imposibles para cada variable
	// vector de variables
std::vector<std::pair<unsigned,T>> lista_asignaciones
	// conjunto de variable y valor posible
	// vector de posibles combinaciones valor-variable

*******
*/


namespace csp
{
  enum class Seleccion_variable {aleatoria, estatica, mrv};
  enum class Algoritmo          {bt, fc, fc_ac1,fc_ac1_necesarios, fc_necesarios};

  template<typename T>
  class Problema_csp
  {
  public:
    Problema_csp() {}

    bool resolver(Seleccion_variable sel_var= Seleccion_variable::estatica, Algoritmo algoritmo= Algoritmo::fc)   // default arguments
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

    std::vector<std::pair<unsigned,T>>& get_solucion()  { return solucion; }

    std::size_t get_nodos_expandidos() const            { return nodos_expandidos; }

  protected:
    unsigned num_variables;
    std::vector<std::vector<T>> dominio;
    std::vector<std::vector<std::pair<unsigned,T>>> lista_exclusiones_dominio;
    std::vector<std::pair<unsigned,T>> solucion;

  private:
    std::vector<unsigned> variables_sin_etiquetar; //Vector instrumental que almacena las variables aun fuera de la solucion
    unsigned nodos_expandidos; //Para comparar entre algoritmos

    void inicializa();
    //FUNCIONES QUE CARGAN EL DOMINIO Y DESCRIBEN EL GRAFO DE RESTRICCIONES
    //virtuales pues dependen de cada problema particular
    virtual bool relacionadas(const unsigned var_1, const unsigned var_2)= 0;                             // =0: pure virtual function
    virtual bool consistente(const unsigned var_1, const T val_1, const unsigned var_2, const T val_2)= 0;
    virtual bool consistente(const unsigned variable, const T valor)= 0;
    virtual void inicializa_dominio()= 0;

    //SELECCION Y BLOQUEO VARIABLE
    void tipo_seleccion_variable(const Seleccion_variable sel_var);
    std::function<unsigned (void)> seleccion_variable;    // Puntero a funcion seleccion_variable
    // std::function <return_type(arg)> name;
    unsigned seleccion_variable_estatica();
    unsigned seleccion_variable_aleatoria();
    unsigned seleccion_variable_mrv();
    void bloquea_variable();
    void libera_variable(const unsigned variable);

    //ALGORITMOS

    // 1) Backtracking
    bool backtracking(); //--> Funcion general bactracking
    bool expandir_bt(const unsigned variable, std::vector<std::pair<unsigned, T>>& lista_asignaciones);
    virtual void restaura_estado(const std::pair<unsigned, T>& asignacion)= 0;        // =0: pure virtual functions
    virtual void actualiza_estado(const std::pair<unsigned, T>& asignacion)= 0;

    // 2) Look ahead
    bool look_ahead(); //--> Funcion general look ahead
    void seleccion_algoritmo_look_ahead(const Algoritmo algoritmo);
    std::function<bool (const std::pair<unsigned, T>&)> actualiza_dominio; // Puntero a funcion actualiza_dominio
    // std::function <return_type(arg)> name;
    void restaura_dominio(const unsigned variable);

    // 2) ->Forward checking
    bool actualiza_dominio_fc(const std::pair<unsigned, T>& asignacion);
    //////////////////////////////////////////////////////////////////////////////////////

    // 2) ->Forward checking con ac1
    bool actualiza_dominio_fc_ac1(const std::pair<unsigned, T>& asignacion);
    bool actualiza_dominio_ac1(const unsigned variable);
    bool revisar_ac1(const unsigned variable, const unsigned var_i, const unsigned var_j);
    //////////////////////////////////////////////////////////////////////////////////////

    //GENERADOR ALEATORIOS
    std::mt19937 rng;

    //PARA DEPURACION
    void imprime_dominio();
    void imprime_lista_asignaciones(std::vector< std::pair<unsigned, T> > lista_asignaciones);
    void imprime_variables_sin_etiquetar();
    void imprime_solucion_debug();
    void imprime_lista_exclusiones_dominio();
    void imprime_tablero();
  };



  template <typename T>
  void Problema_csp<T>::inicializa()
  {
    inicializa_dominio(); // Llamada virtual diferente para cada problema

    //Borra listas
    lista_exclusiones_dominio.clear();
    lista_exclusiones_dominio.resize(num_variables);
    variables_sin_etiquetar.clear();

    for(unsigned i=0; i!=num_variables; ++i) // Todas las variables sin etiquetar (sin asignar un valor) inicialmente
      variables_sin_etiquetar.push_back(i);

    solucion.clear();

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();   // Genera semilla para aleatorios
    rng.seed(seed);
  }

  //Para depuracion
    template <typename T>
    void Problema_csp<T>::imprime_dominio()
    {
      for(unsigned i=0; i!=num_variables(); ++i)
      {
        for(auto j:dominio(i))
          std::cout<<j<<" ";
        std::cout<<std::endl;
      }
    }

    template <typename T>
    void Problema_csp<T>::imprime_lista_asignaciones(std::vector< std::pair<unsigned, T> > lista_asignaciones)
    {
      std::cout<<"\nLista de asignaciones: ";
      for(const auto& valor : lista_asignaciones)
        std::cout<<"{"<<valor.first<<","<<valor.second<<"}"<<" ";
    }

    template <typename T>
    void Problema_csp<T>::imprime_variables_sin_etiquetar()
    {
      std::cout<<"\nvariables_sin_etiquetar: ";
      for(const auto& var: variables_sin_etiquetar)
        std::cout<<var<<" ";
    }

    template <typename T>
    void Problema_csp<T>::imprime_solucion_debug()
    {
      std::cout<<"\nSolucion: ";
      for(const auto& v: solucion)
        std::cout<<"{"<<v.first<<","<<v.second<<"}"<<" - ";
    }

    template <typename T>
    void Problema_csp<T>::imprime_lista_exclusiones_dominio()
    {
      std::cout<<"\nlista_exclusiones_dominio: ";
      for(int i=0; i<lista_exclusiones_dominio.size(); ++i)
        for(const auto& excl : lista_exclusiones_dominio[i])
          std::cout<<i<<": {"<<excl.first<<","<<excl.second<<"}"<<" - ";
        std::cout<<std::endl;
    }

    template <typename T>
    void Problema_csp<T>::imprime_tablero()  {
      std::sort(solucion.begin(),solucion.end());
      std::cout<<std::endl;
      // for(auto v:solucion)
      //   std::cout<<"("<<v.first<<","<<v.second<<")"<<std::endl;
      unsigned cont=0;
      for(const auto& queen : solucion)
      {
        std::cout<<++cont<<".\t";
        for(unsigned i=0; i< num_variables; ++i)
        {
          if(i==queen.second)
            std::cout<<"Q ";
          else
            std::cout<<"- ";
        }
        std::cout<<std::endl;
      }
    }

  #include "../header/csp_seleccion_variable.h"
  #include "../header/csp_seleccion_algoritmo.h"
  #include "../header/csp_backtracking.h"         // Template file
  #include "../header/csp_look_ahead.h"           // Template file

}

#endif // PROBLEMA_CSP_H_INCLUDED
