#ifndef KNN
#define KNN

#include <cstdint>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include <map>
#include <cassert>

template<typename Dato>
double distancia(const Dato& im1,const Dato& im2)
{
  // DONE

  double dis=0;
  assert(im1.size()==im2.size() && "Different size!");
  for(unsigned i=0; i<im1.size(); ++i)
  {
    dis+= abs(im1[i] - im2[i]);
  }

  return dis*dis;
}

template<typename Dato,typename Etiqueta>
class Knn
{
public:
  unsigned get_num_datos_test() const
  {
    return(datos_test.size());
  }
  unsigned get_num_datos_entrenamiento() const
  {
    return(datos_entrenamiento.size());
  }
  void ejecutar(const unsigned k,const unsigned indice);
  //TO-DO: llama a clasifica (la actual ejecutar y luego cuenta los éxitos)
  void detener(){}
  void cargar_datos_test(std::vector<Dato>& d_t)
  {
    datos_test=d_t;
  }
  void cargar_etiquetas_test(std::vector<Etiqueta>& e_t)
  {
    etiquetas_test=e_t;
  }
  void cargar_datos_entrenamiento(std::vector<Dato>& d_e)
  {
    datos_entrenamiento=d_e;
  }
  void cargar_etiquetas_entrenamiento(std::vector<Etiqueta>& e_e)
  {
    etiquetas_entrenamiento=e_e;
  }
  unsigned get_etiqueta_ganadora()
  {
    return etiqueta_ganadora;
  }
private:
  std::vector<Dato> datos_test;
  std::vector<Dato> datos_entrenamiento;
  std::vector<Etiqueta> etiquetas_entrenamiento;
  std::vector<Etiqueta> etiquetas_test;
  unsigned etiqueta_ganadora;
};

template<typename Dato,typename Etiqueta>
void Knn<Dato,Etiqueta>::ejecutar(const unsigned k,const unsigned indice) //indice de imagen en el vector de imagenes de test
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
  for(unsigned i= 0; i!=10; ++i)    // num_etiquetas
  {
    if(frecuencia[i]>frecuencia_mayor)
    {
      etiqueta_ganadora = i;
      frecuencia_mayor= frecuencia[i];
    }
  }
}

#endif // KNN_H_INCLUDED
