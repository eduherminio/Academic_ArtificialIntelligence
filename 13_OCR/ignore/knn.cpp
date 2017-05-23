#include "../header/knn.h"

#include "../MNIST/include/mnist_reader.h"
#include <queue>
#include <cmath>

uint8_t Knn::ejecutar(const unsigned k,const unsigned indice) const //indice de imagen en el vector de imagenes de test
{
  std::cout<<"k="<<k<<"\n";
  std::cout<<"indice="<<indice<<"\n";
  if(indice>=0 && indice<imagenes_test.size())
  {
    auto &im_test=imagenes_test.at(indice);
    std::priority_queue<std::pair<double, unsigned>,std::vector<std::pair<double, unsigned>>, std::greater<std::pair<double, unsigned>>> cola_prioridad;

    unsigned indice_imagen=0;
    double distancia_actual;
    for(auto &im_entrenamiento:imagenes_entrenamiento)
    {
      cola_prioridad.push({distancia(im_entrenamiento,im_test),indice_imagen});
      indice_imagen++;
    }
    //Calcula la frecuencia con la que aparece cada digito en los k mejores vecinos
    unsigned frecuencia[10]= {0};  //10  -->tenemos 10 digitos, ergo 10 etiquetas
    std::cout<<"k="<<k<<std::endl;
    for(unsigned i=0; i!=k; ++i)
    {
      frecuencia[etiquetas_entrenamiento.at(cola_prioridad.top().second)] += 1;
      cola_prioridad.pop();
    }
    uint8_t etiqueta_ganadora=0;
    unsigned frecuencia_mayor=0;
    for(unsigned i= 0; i!=10; ++i)
    {
      if(frecuencia[i]>frecuencia_mayor)
      {
        etiqueta_ganadora = i;
        frecuencia_mayor= frecuencia[i];
      }
    }
    std::cout<<(int)etiqueta_ganadora<<" "<<(int)etiquetas_test.at(indice)<<std::endl;
    std::cout<<"FIN"<<std::endl;
    return(etiqueta_ganadora);
  }
  else
  {
    std::cout<<"El indice no es valido"<<std::endl;
    return 11;
  }

}

double Knn::distancia(const std::vector<uint8_t> &im1,const std::vector<uint8_t> & im2) const
{
  unsigned indice_pixel=0;
  double dif;
  double distancia_al_cuadrado=0;
  for(auto &dato:im1)
  {
    dif=dato-im2.at(indice_pixel);
    distancia_al_cuadrado+=dif*dif;
    indice_pixel++;
  }
  return sqrt(distancia_al_cuadrado);  //¿Hace falta?

}
