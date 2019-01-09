#ifndef KNN_H_INCLUDED
#define KNN_H_INCLUDED

#include <cstdint>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include <map>
#include <cassert>
// #include <algorithm>  // std::fill

template<typename Dato>
double distancia(const Dato& im1,const Dato& im2)
{
  // DONE

  double dis=0;
  assert(im1.size()==im2.size() && "Different size!");
  for(unsigned i=0; i<im1.size(); ++i)
  {
    dis+= abs(im1[i] - im2[i]);   // uint8_t instead of unsigned, fortunately
  }

  return dis*dis;
}

template<typename Dato,typename Etiqueta>
class Knn
{
public:

  void clasificar(const unsigned k, const unsigned indice);
  void evaluar(const Etiqueta);
  void ejecutar(const unsigned k,const unsigned indice, const unsigned num_etiquetas)
  {
    // DONE
    // Evaluar el acierto del test, respecto al entrenamiento

    // for(unsigned indice=0; indice<etiquetas_test.size(); ++indice)             // Takes too many time
    for(unsigned indice=0; indice<50; ++indice)
    {
      // std::cout<<static_cast<unsigned>(etiquetas_test[indice])<<std::endl;
      clasificar(k, indice);            // Antigua función ejecutar
      evaluar(etiquetas_test[indice]);  // Fills map_evaluacion()
    }

    unsigned cont=0;
    for(std::map<unsigned, std::pair<unsigned, unsigned>>::const_iterator it = map_evaluacion.begin(); it != map_evaluacion.end(); ++it, ++cont)
      std::cout<<static_cast<unsigned>(it->first)<<": "<<it->second.first<<"/"<<it->second.second<<std::endl;
  }

  void detener(){}
  void cargar_datos_test(std::vector<Dato>& d_t)                  { datos_test=               d_t;  }
  void cargar_etiquetas_test(std::vector<Etiqueta>& e_t)          { etiquetas_test=           e_t;  }
  void cargar_datos_entrenamiento(std::vector<Dato>& d_e)         { datos_entrenamiento=      d_e;  }
  void cargar_etiquetas_entrenamiento(std::vector<Etiqueta>& e_e) { etiquetas_entrenamiento=  e_e;  }

  unsigned get_num_datos_test()           const   { return(datos_test.size());          }
  unsigned get_num_datos_entrenamiento()  const   { return(datos_entrenamiento.size()); }
  unsigned get_etiqueta_ganadora()        const   { return etiqueta_ganadora;           }

private:
  std::vector<Dato> datos_test;
  std::vector<Dato> datos_entrenamiento;
  std::vector<Etiqueta> etiquetas_entrenamiento;
  std::vector<Etiqueta> etiquetas_test;
  unsigned etiqueta_ganadora;
  std::map<unsigned, std::pair<unsigned, unsigned>> map_evaluacion; // identifier, pair<success, total>
  unsigned knn_num_etiquetas;
};

template<typename Dato,typename Etiqueta>
void Knn<Dato,Etiqueta>::clasificar(const unsigned k,const unsigned indice) //indice de imagen en el vector de imagenes de test
{
  assert(indice>=0 && indice<datos_test.size() && "Invalid pic index");
  assert(k>0 && k<datos_entrenamiento.size()-1 && "Invalid k parameter");

  auto &dato_actual=datos_test[indice];
  std::priority_queue<std::pair<double, unsigned>,std::vector<std::pair<double, unsigned>>, std::greater<std::pair<double, unsigned>>> cola_prioridad;
  // <Distancia, índice>

  unsigned indice_dato=0;
  for(auto &dato:datos_entrenamiento)
  {
    cola_prioridad.push({distancia(dato,dato_actual),indice_dato});
    ++indice_dato;
  }
  //Calcula la frecuencia con la que aparece cada digito en los k mejores vecinos
  std::map<Etiqueta,unsigned> frecuencia;
  for(unsigned i=0; i!=k; ++i)
  {
    ++frecuencia[etiquetas_entrenamiento[cola_prioridad.top().second]];
    cola_prioridad.pop();
  }
  etiqueta_ganadora=0;
  unsigned frecuencia_mayor=0;
  for(unsigned i= 0; i!= 10; ++i)    // DONE: knn_num_etiquetas instead of 10, to make it generic
  {
    if(frecuencia[i]>frecuencia_mayor)
    {
      etiqueta_ganadora = i;
      frecuencia_mayor= frecuencia[i];
    }
  }
}

template<typename Dato,typename Etiqueta>
void Knn<Dato,Etiqueta>::evaluar(const Etiqueta etiqueta)
{
  // DONE
  // Evaluar el acierto del test, respecto al entrenamiento

  // std::vector<unsigned> v_etiquetas_totales;
  // std::vector<unsigned> v_etiquetas_acertadas;
  // v_etiquetas_acertadas.resize(num_etiquetas);
  // v_etiquetas_totales.resize(num_etiquetas);
  // std::fill(v_etiquetas_totales.begin(), v_etiquetas_totales.end(), 0);
  // std::fill(v_etiquetas_acertadas.begin(), v_etiquetas_acertadas.end(), 0);

  ++map_evaluacion[static_cast<unsigned>(etiqueta)].second;
  // ++v_etiquetas_totales[static_cast<unsigned>(etiquetas_test[indice])];

  if(etiqueta_ganadora == static_cast<unsigned>(etiqueta))
  {
    ++map_evaluacion[static_cast<unsigned>(etiqueta)].first;
    // ++v_etiquetas_acertadas[static_cast<unsigned>(etiquetas_test[indice])];
  }

  // for(unsigned i=0; i<v_etiquetas_totales.size(); ++i)
  //   std::cout<<i<<":"<<v_etiquetas_acertadas[i]<<"/"<<v_etiquetas_totales[i]<<std::endl;
}

#endif // KNN_H_INCLUDED
