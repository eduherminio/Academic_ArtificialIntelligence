#ifndef PROBLEMA_CSP_H_INCLUDED
#define PROBLEMA_CSP_H_INCLUDED

#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include <iostream>
#include <cassert>

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
    std::vector<unsigned> variables_sin_etiquetar; //Vector instrumental que almacena las variables a�n fuera de la soluci�n
    unsigned nodos_expandidos; //Para comparar entre algoritmos

    void inicializa();
    //FUNCIONES QUE CARGAN EL DOMINIO Y DESCRIBEN EL GRAFO DE RESTRICCIONES
    //virtuales pues dependen de cada problema particular
    virtual bool relacionadas(const unsigned var_1, const unsigned var_2)= 0;                             // =0: pure virtual function
    virtual bool consistente(const unsigned var_1, const T val_1,const unsigned var_2, const T val_2)= 0;
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
    bool expandir_bt(const unsigned variable,std::vector<std::pair<unsigned, T>>& lista_asignaciones);
    virtual void restaura_estado(const std::pair<unsigned, T> &asignacion)= 0;        // =0: pure virtual functions
    virtual void actualiza_estado(const std::pair<unsigned, T> &asignacion)= 0;

    // 2) Look ahead
    bool look_ahead(); //--> Funci�n general look ahead
    void seleccion_algoritmo_look_ahead(const Algoritmo algoritmo);
    std::function<bool (const std::pair<unsigned, T>&)> actualiza_dominio; // Puntero a funcion actualiza_dominio
    // std::function <return_type(arg)> name;
    void restaura_dominio(const unsigned variable);

    //2) ->Forward checking
    bool actualiza_dominio_fc(const std::pair<unsigned, T> &asignacion);
    //////////////////////////////////////////////////////////////////////////////////////

    //2) ->Forward checking con ac1
    bool actualiza_dominio_fc_ac1(const std::pair<unsigned, T> &asignacion);
    bool actualiza_dominio_ac1(const unsigned variable);
    bool revisar_ac1(const unsigned variable, const unsigned var_i, const unsigned var_j);
    //////////////////////////////////////////////////////////////////////////////////////

    //GENERADOR ALEATORIOS
    std::mt19937 rng;

    //PARA DEPURACION
    void imprime_dominio();
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
    for(unsigned i=0; i!=num_variables; ++i)
    {
      std::cout<<"Q"<<i+1<<":"<<std::endl;
      for(const auto& j : dominio[i])
        std::cout<<j<<" ";
      std::cout<<std::endl;
    }
  }

  #include "../header/csp_seleccion_variable.h"
  #include "../header/csp_seleccion_algoritmo.h"
  #include "../header/csp_backtracking.h"         // Template file
  #include "../header/csp_look_ahead.h"           // Template file

}

#endif // PROBLEMA_CSP_H_INCLUDED
