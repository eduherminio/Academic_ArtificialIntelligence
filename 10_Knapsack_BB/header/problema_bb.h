#ifndef PROBLEMA_BB_H_INCLUDED
#define PROBLEMA_BB_H_INCLUDED

#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include <iostream>

namespace bb
{
  enum class Seleccion_variable {aleatoria, estatica, mrv};

  template<typename T>
  class Problema_bb
  {
  public:
    Problema_bb()
    {
      //Genera semilla para aleatorios
      auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      rng.seed(seed);
    }

    bool resolver(Seleccion_variable sel_var=Seleccion_variable::estatica)
    {
      inicializa();
      tipo_seleccion_variable(sel_var);
      return (bb_backtracking());
    }

    std::size_t get_nodos_expandidos() const
    {
      return nodos_expandidos;
    }
  protected:
    unsigned num_variables;
    std::vector<std::vector<T>> dominio;
    std::vector<std::pair<unsigned,T>> solucion;
    std::vector<unsigned> variables_sin_etiquetar; //Vector instrumental que almacena las variables a�n fuera de la soluci�n
  private:
    unsigned nodos_expandidos; //Para comparar entre algoritmos

    //FUNCIONES QUE CARGAN EL DOMINIO Y DESCRIBEN EL GRAFO DE RESTRICCIONES
    //virtuales pues dependen de cada problema particular
    virtual void inicializa()= 0;
    virtual bool consistente(const unsigned variable,const T valor)= 0;
    virtual void actualiza_solucion(std::vector< std::pair<unsigned,T> >&)= 0;
    virtual void ordenacion_estatica_variables_ad_hoc() =0;

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
    bool bb_backtracking(); //--> Funci�n general bactracking
    bool expandir_bt(const unsigned variable,std::vector<std::pair<unsigned,T>>& lista_asignaciones);
    virtual void restaura_estado(const std::pair<unsigned,T> &asignacion)=0;  //Llamada virtual diferente para cada problema
    virtual void actualiza_estado(const std::pair<unsigned,T> &asignacion)=0; //Llamada virtual diferente para cada problema

    //////////////////////////////////////////////////////////////////////////////////////

    //GENERADOR ALEATORIOS
    std::mt19937 rng;

  };

  #include "bb_seleccion_variable.h"
  #include "bb_backtracking.h" //Fichero de plantillas

}
#endif // PROBLEMA_BB_H_INCLUDED
