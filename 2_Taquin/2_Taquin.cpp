#include "header/problema_busqueda_taquin.h"
#include <ctime>
#include <iostream>

int main()
{
  using namespace std;

  /////////////////////////////////////////////////////////////////////////////////////
  //    Ejemplo a profundidad 31                                                     //
        // taquin::Nodo_taquin inicial(3,3,{8,6,7,2,5,4,3,0,1});                        //
        // taquin::Nodo_taquin objetivo(3,3,{1,2,3,4,5,6,7,8,0});                       //
  /////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////////////
  //    Ejemplo a profundidad 50                                                     //
     taquin::Nodo_taquin inicial(4,4,{12,15,6,10,4,9,5,8,14,13,0,2,1,7,11,3});    //
     taquin::Nodo_taquin objetivo(4,4,{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0});   //
  /////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////////////
  //    Ejemplo a profundidad 80                                                     //
    //  taquin::Nodo_taquin inicial(4,4,{15,14,8,12,10,11,9,13,2,6,5,1,3,7,4,0});    //
    //  taquin::Nodo_taquin objetivo(4,4,{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0});   //
  /////////////////////////////////////////////////////////////////////////////////////


  taquin::Problema_busqueda_taquin problema(inicial,objetivo);
  clock_t start, end1, end2, end3;
  start = clock();
/*
  if(problema.amplitud())     {
    muestra_solucion(problema);

    std::cout<<"\n*****Búsqueda por Amplitud*****"<<std::endl;
    cout<<"\n\nNumero de nodos expandidos: "<<problema.get_nodos_expandidos()<<"\n";

    end1 = clock();
    double time_elapsed = double(end1 - start);
    cout<<"Tiempo empleado: "<<time_elapsed/1000<<endl;
    cout<<"\n--------------------------------------------------"<<endl;
    start= clock();
  }

  if(problema.profundidad())  {
    // muestra_solucion(problema);

    std::cout<<"\n*****Búsqueda por Profundidad*****"<<std::endl;
    cout<<"\nNumero de nodos expandidos: "<<problema.get_nodos_expandidos()<<"\n";

    end2 = clock();
    double time_elapsed = double(end2 - start);
    cout<<"Tiempo empleado: "<<time_elapsed/1000<<endl;
    cout<<"\n--------------------------------------------------"<<endl;
    start= clock();
  }
*/
  if(problema.a_estrella())   {
    muestra_solucion(problema);

    std::cout<<"\n*****Búsqueda A* ******"<<std::endl;
    cout<<"\nNumero de nodos expandidos: "<<problema.get_nodos_expandidos()<<"\n";

    end3 = clock();
    double time_elapsed = double(end3 - start);
    cout<<"Tiempo empleado: "<<time_elapsed/1000<<endl;
  }
}
