#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <math.h>

namespace mapa
{
  struct Punto_2d
  {
    unsigned x;
    unsigned y;
  };

  class Mapa
  {
  public:
    Mapa(const unsigned num_filas,const unsigned num_columnas,const Punto_2d &i,const Punto_2d &f,const std::vector <Punto_2d> &lista_muros):inicio(i),fin(f)
    {
      //Obtenemos la maxima x y la maxima y entre la posicion inicial, final, muros y dimensiones rejilla
      set_filas_columnas(num_filas,num_columnas,lista_muros);
      set_muros(lista_muros);
    }
    Mapa()
    {
    }
    //        Mapa& operator=(const Mapa& mapa)
    //        {
    //            filas=mapa.filas;
    //            columnas=mapa.columnas;
    //            inicio=mapa.inicio;
    //            fin=mapa.fin;
    //            muros=mapa.muros;
    //            return *this;
    //        }

    void crea_mapa(const unsigned num_filas,const unsigned num_columnas,const Punto_2d &i,const Punto_2d &f,const std::vector <Punto_2d> &lista_muros)
    {
      inicio=i;
      fin=f;
      //Obtenemos la maxima x y la maxima y entre la posicion inicial, final, muros y dimensiones rejilla
      set_filas_columnas(num_filas,num_columnas,lista_muros);
      set_muros(lista_muros);
    }
    unsigned get_filas() const
    {
      return(filas);
    }
    unsigned get_columnas() const
    {
      return(columnas);
    }
    const Punto_2d &get_nodo_inicial() const
    {
      return inicio;
    }
    const Punto_2d &get_nodo_final() const
    {
      return fin;
    }
    const std::unordered_set<unsigned> &get_muros() const
    {
      return muros;
    }
    std::vector<Punto_2d> expandir(const Punto_2d&) const;
    bool prueba_meta(const Punto_2d&) const;
    double acumula_coste(const Punto_2d& p1,const Punto_2d& p2) const;
    double calcula_heuristica(const Punto_2d &p) const;
    unsigned nodo_to_clave(const Punto_2d &p) const;
    Punto_2d clave_to_nodo(unsigned clave) const;
    std::unordered_map<unsigned,unsigned> padre;    //Podrian juntarse padre y coste_actual en un pair<unsigned,float>
    std::unordered_map<unsigned,double>coste_actual;
    bool hijo_valido(const Punto_2d &punto_padre,const Punto_2d &punto_hijo,double &);
  private:
    void set_muros(const std::vector<Punto_2d> &lista_muros);
    void set_filas_columnas(const unsigned num_filas,const unsigned num_columnas,const std::vector <Punto_2d> &lista_muros);
    unsigned filas;
    unsigned columnas;
    std::unordered_set<unsigned>muros;
    Punto_2d inicio;
    Punto_2d fin;
  };
}
#endif // MAPA_H_INCLUDED
