#include "../header/ciudades.h"
#include <fstream>
#include <sstream>
#include <cmath>

namespace ciudades
{
  //Lee un fichero normalizado TSPLIB
  //Para simplificar, sin p�rdida de generalidad, solo contemplamos distancias euclideas 2D
  bool Ciudades::carga_ciudades(const std::string nombre_fichero)
  {
    bool exito=false;
    coordenadas.clear();
    recorrido_optimo.clear();

    std::ifstream fichero;
    fichero.open( nombre_fichero.c_str() );

    if ( !fichero )
    {
      std::cout << "Error al abrir el fichero\n";
      return false;
    }

    // Leemos linea a linea el fichero TSPLIB
    // Verificamos que es del tipo EUC_2D
    // Formamos el vector de coordenadas

    std::string linea=" ";
    std::string palabra;
    std::string nombre_fich;

    while(linea!="EOF")
    {
      getline(fichero,linea);
      linea= linea.substr(0, linea.size()-1);   // NEEDED

      std::cout<<"**"<<linea<<std::endl;

      if(linea=="NODE_COORD_SECTION")
      {
        double x,y;
        std::cout<<"COORDENADAS"<<std::endl;
        for(unsigned i=0; i<num_ciudades; i++)
        {
          getline(fichero,linea); //leemos las lineas con las coordenadas
          std::stringstream linea_stream(linea);
          getline(linea_stream,palabra,' ');  //Obtenemos el indice de ciudad. No lo utilizamos
          getline(linea_stream,palabra,' ');  //Obtenemos la coordenada x;
          std::stringstream palabra_stream_x(palabra);
          palabra_stream_x >> x;  //Pasamos de string a double
          getline(linea_stream,palabra,' ');  //Obtenemos la coordenada y;
          std::stringstream palabra_stream_y(palabra);
          palabra_stream_y >> y;  //Pasamos de string a double
          coordenadas.push_back({x,y}); //Almacenamos las coordenadas
        }
      }
      else if(linea=="TOUR_SECTION")
      {
        std::cout<<linea<<std::endl;
        unsigned indice;
        std::cout<<"num_ciudades"<<num_ciudades<<std::endl;
        for(unsigned i=0; i<num_ciudades; i++)
        {
          // std::cout<<"iter"<<i<<std::endl;
          getline(fichero,linea); //leemos las lineas con las coordenadas
          std::stringstream indice_stream(linea);
          indice_stream >> indice;  //Pasamos de string a unsigned
          recorrido_optimo.push_back({indice-1}); //Almacenamos los indices (restamos 1)
        }
      }
      else
      {
        std::stringstream linea_stream(linea);
        getline(linea_stream,palabra,' ');  //Obtenemos la primera palabra de la linea de texto
        if(palabra=="EDGE_WEIGHT_TYPE")
        {
          getline(linea_stream,palabra,' '); //Leemos el texto correspondiente a los dos puntos :
          getline(linea_stream,palabra,' '); //Leemos el texto correspondiente al tipo de distancia
          exito=true;
          if(palabra=="EUC_2D")              //solo trabajamos con ficheros TSPLIB con distancias euclideas 2D
          {
            exito=true;
            std::cout<<"EUC_2D"<<std::endl;
          }
        }
        else if(palabra=="EDGE_WEIGHT_TYPE:")
        {
          getline(linea_stream,palabra,' '); //Leemos el texto correspondiente al tipo de distancia
          exito=true;
          if(palabra=="EUC_2D")              //solo trabajamos con ficheros TSPLIB con distancias euclideas 2D
          {
            exito=true;
            std::cout<<"EUC_2D"<<std::endl;
          }
        }
        else if(palabra=="DIMENSION")
        {
          getline(linea_stream,palabra,' '); //Leemos el texto correspondiente a los dos puntos :
          getline(linea_stream,palabra,' '); //Leemos el texto correspondiente al numero de ciudades
          std::stringstream palabra_stream(palabra);
          palabra_stream >> num_ciudades;  //Pasamos de string a int: �Ya tenemos el numero de ciudades!
          std::cout<< num_ciudades<<std::endl;
        }
        else if(palabra=="DIMENSION:")
        {
          getline(linea_stream,palabra,' '); //Leemos el texto correspondiente al numero de ciudades
          std::stringstream palabra_stream(palabra);
          palabra_stream >> num_ciudades;  //Pasamos de string a int: �Ya tenemos el numero de ciudades!
          std::cout<< num_ciudades<<std::endl;
        }
        else if(palabra=="NAME")
        {
          getline(linea_stream,palabra,' '); //Leemos el texto correspondiente a los dos puntos :
          getline(linea_stream,nombre_fich,' '); //Leemos el texto correspondiente al nombre del fichero
          std::cout<<nombre_fich<<std::endl;
        }
        else if(palabra=="NAME:")
        {
          getline(linea_stream,nombre_fich,' '); //Leemos el texto correspondiente al nombre del fichero
          std::cout<<nombre_fich<<std::endl;
        }
      }
    }
    fichero.close();

    //Formamos la matriz de distancias y calculamos los valores extremos
    if(exito==true)
    {
      set_matriz_distancias();
      std::cout<<"Set matriz distancias"<<std::endl;
    }
    return exito;
  }

  // Calcula la matriz de distancias entre las ciudades
  void Ciudades::set_matriz_distancias()
  {
    //Crea e inicializa a 0 la matriz de distancias

    distancias = std::vector<std::vector<double>>(num_ciudades,std::vector<double>(num_ciudades, 0.));

    std::pair<double,double> p;
    double dist;
    double x1,y1,x2,y2;

    //Calcula las distancias euclideas 2D
    for(unsigned i=0; i<num_ciudades; i++)
    {
      p=coordenadas.at(i);
      x1 = p.first;
      y1 = p.second;
      for(unsigned j=i+1; j<num_ciudades; j++)
      {
        p=coordenadas.at(j);
        x2 = p.first;
        y2 = p.second;

        dist = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        distancias[i][j]=distancias[j][i]=dist;
      }
    }
  }

  double Ciudades::calcula_distancia(const std::vector<unsigned>& recorrido) const
  {
    double distancia = 0.0;
    if(recorrido.size()>1)
    {
      for(unsigned i=0; i<num_ciudades-1; i++)
      {
        distancia+=distancias[recorrido[i]][recorrido[i+1]];
      }
      // Distancia entre la �ltima y la primera
      distancia += distancias[recorrido[num_ciudades-1]][recorrido[0]];
    }
    return(distancia);
  }

  //Los valores extremos los usamos para normalizar a las dimensiones de la pantalla a la hora de dibujar
  void Ciudades::calcula_valores_extremos(double &x_min,double &x_max,double &y_min,double &y_max) const
  {
    if(coordenadas.size()>1) //Al menos 2 ciudades
    {
      x_min=coordenadas[0].first;
      x_max=coordenadas[0].first;
      y_min=coordenadas[0].second;
      y_max=coordenadas[0].second;
    }
    for(auto &p:coordenadas)
    {
      if(p.first<x_min)
      x_min=p.first;
      else if(p.first>x_max)
      x_max=p.first;
      if(p.second<y_min)
      y_min=p.second;
      else if(p.second>y_max)
      y_max=p.second;
    }
  }
}
