#include "../header/ruta.h"
#include <algorithm>

namespace ruta
{
  Ruta::Ruta()  {
    // DONE: Complete
    seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(seed);
    aleatorio_num_ciudades= std::uniform_int_distribution<unsigned>(0,num_ciudades);
    aleatorio_0_a_1=        std::uniform_real_distribution<double>(0., 1.);
  }

  Ruta::~Ruta(){};

  void Ruta::inicializa_ruta(ciudades::Ciudades&&ciu) {
    ciudades=ciu;
    num_ciudades=ciudades.get_num_ciudades();

    aleatorio_num_ciudades=std::uniform_int_distribution<unsigned>(0,num_ciudades-1);
    aleatorio_0_a_1=std::uniform_real_distribution<double>(0,1);
  }

  void Ruta::actualiza_ruta() {
    recorrido_actual=std::move(recorrido_provisional);
    distancia_actual=distancia_provisional;
  }

  double Ruta::calcula_distancia(const std::vector<unsigned>& recorrido)  {
    return(ciudades.calcula_distancia(recorrido));
  }

  unsigned Ruta::insert_function1(const std::vector<unsigned>& pos, unsigned& long_segmento)  {

    long_segmento= pos[1] - pos[0] + 1;
    int i;
    for(i=pos[0]; i<pos[0]+ pos[2]-pos[1]; ++i)
    {
      recorrido_provisional[i]= recorrido_actual[i + long_segmento];
    }
    unsigned new_i=i;
    unsigned j=0;
    for(int i=new_i; i< new_i + long_segmento; ++i)
    {
      recorrido_provisional[i]= recorrido_actual[pos[0]+j];
      ++j;
    }

    return new_i;
  }

  void Ruta::insert_function2(const std::vector<unsigned>& pos, unsigned& long_segmento)  {
    long_segmento= pos[2] - pos[1] + 1;

    for(unsigned i=0; i<long_segmento; ++i)                   // Completa el segmento
    {
      recorrido_provisional[pos[0]+1+i]= recorrido_actual[pos[1]+i];
    }

    for(unsigned w=0; w<pos[1]-pos[0]-1; ++w)                 // Completa los anteriores al segmento
    {
      recorrido_provisional[pos[0]+long_segmento+1+w]= recorrido_actual[pos[0]+1 + w];
    }
  }

  // DONE
  // El alumno debe programar una cuarta modificacion del recorrido
  // Seleccionar un segmento del recorrido y un punto, e insertar el segmento a partir del punto
  // Elige una sección dada por 3 puntos de la ruta y la rota
  // pasando el punto intermedio a ser el primero
  void Ruta::insercion_segmento() {

    recorrido_provisional= recorrido_actual;  // Most of it won't change

    // unsigned pos[3];
    std::vector<unsigned> pos;  // To be sorted easily
    pos.resize(3);

    pos[0]= aleatorio_num_ciudades(rng); // Three different random cities

    do {
      pos[1]= aleatorio_num_ciudades(rng);
    } while(pos[1]==pos[0]);

    do {
      pos[2]=aleatorio_num_ciudades(rng);
    } while(pos[2]==pos[1] || pos[2]==pos[0]);

    std::sort(pos.begin(), pos.end());

    auto aleatorio= aleatorio_0_a_1(rng);
    unsigned long_segmento, lon;

    if        (aleatorio<=  +0.25)  {   // inserts vector [p1, p2] after p3
      insert_function1(pos, long_segmento);
    }
    else if   (aleatorio <= +0.50)  {   // inserts vector [p2, p1] after p3
      lon= insert_function1(pos, long_segmento);

      auto it1= recorrido_provisional.begin() + lon;
      auto it2= recorrido_provisional.begin() + lon + long_segmento;

      std::reverse(it1, it2);
    }
    else if   (aleatorio <= +0.75)  {   // inserts vector [p2, p3] after p1
        insert_function2(pos, long_segmento);
    }
    else                            {   // inserts vector [p3, p2] after p1
      insert_function2(pos, long_segmento);

      auto it1= recorrido_provisional.begin() + pos[0]+1;
      auto it2= recorrido_provisional.begin() + pos[0]+1 + long_segmento;

      std::reverse(it1, it2);
    }

    distancia_provisional=calcula_distancia(recorrido_provisional);

    // Debug purposes
    // std::cout<<"***************"<<std::endl;
    // for(const auto& x:recorrido_actual)
    //   std::cout<<x<<" ";
    // std::cout<<std::endl;
    // for(const auto& x:pos)
    //   std::cout<<recorrido_actual[x]<<" ";
    // std::cout<<std::endl;
    // for(const auto& x:recorrido_provisional)
    //   std::cout<<x<<" ";
    // std::cout<<std::endl;
  }

  void Ruta::rotacion_3_puntos()  {
    // Copiamos recorrido actual en el posible nuevo recorrido
    recorrido_provisional=recorrido_actual;
    unsigned c[3];

    //Elegimos aleatoriamente 3 indices de ciudades
    c[0] = aleatorio_num_ciudades(rng);
    c[1] = aleatorio_num_ciudades(rng);
    c[2] = aleatorio_num_ciudades(rng);

    //Exigimos que sean distintos
    while ( (c[0] == c[1] ||
      c[0] == c[2] ||
      c[1] == c[2]))
      {
        c[0] = aleatorio_num_ciudades(rng);
        c[1] = aleatorio_num_ciudades(rng);
        c[2] = aleatorio_num_ciudades(rng);
      }
      //Los ordenamos de menor a mayor
      std::sort(c,c+3);

      //Ejecutamos la rotacion
      auto it1 = recorrido_provisional.begin() + c[0];
      auto it2 = recorrido_provisional.begin() + c[1];
      auto it3 = recorrido_provisional.begin() + c[2];
      rotate(it1,it2,it3);
      distancia_provisional=calcula_distancia(recorrido_provisional);
    }

  // Elige una seccion dada por 2 puntos de la ruta y la rota
  void Ruta::rotacion_2_puntos()  {
    // Copiamos recorrido actual en el posible nuevo recorrido
    recorrido_provisional=recorrido_actual;

    unsigned c1 = aleatorio_num_ciudades(rng);
    unsigned c2;

    do
    {
      c2 = aleatorio_num_ciudades(rng);
    }
    while(c1==c2);
    if(c1>c2)
    {
      auto aux=c2;
      c2=c1;
      c1=aux;
    }

    auto it1 = recorrido_provisional.begin() + c1;
    auto it2 = recorrido_provisional.begin() + c2;

    reverse(it1,it2);
    distancia_provisional=calcula_distancia(recorrido_provisional);
  }

  // Elige 2 puntos de la ruta y los intercambia
  void Ruta::intercambio_2_puntos() {
    // Copiamos recorrido actual en el posible nuevo recorrido
    recorrido_provisional=recorrido_actual;

    unsigned c1=aleatorio_num_ciudades(rng);
    unsigned c2;
    do
    {
      c2=aleatorio_num_ciudades(rng);
    }
    while(c1==c2);

    recorrido_provisional[c1]=recorrido_actual[c2];
    recorrido_provisional[c2]=recorrido_actual[c1];
    distancia_provisional=calcula_distancia(recorrido_provisional);
  }

  void Ruta::inicializa_recorrido() {
    crea_recorrido_aleatorio(num_ciudades,recorrido_actual);
    // crea_recorrido(num_ciudades,recorrido_actual);
    // crea_recorrido_avaro(recorrido_actual,ciudades);    // Seems optimum

    distancia_actual=ciudades.calcula_distancia(recorrido_actual);
  }

  void Ruta::crea_recorrido_vecino()  {
    // DONE
    //El alumno debe programar una cuarta modificacion del recorrido
    //Seleccionar un segmento del recorrido y un punto, e insertar el segmento a partir del punto

    //Jugamos con distintas modificaciones para "enriquecer" el problema
    auto aleatorio=aleatorio_0_a_1(rng);

    if(aleatorio<=        +0.25)    {
      rotacion_3_puntos();
    }
    else if(aleatorio<=   +0.50)    {
      rotacion_2_puntos();
    }
    else if(aleatorio<    +0.75)    {
      intercambio_2_puntos();
    }
    else                            {
      insercion_segmento();
    }
  }
  // Genera recorrido aleatorio
  void crea_recorrido_aleatorio(unsigned num_ciudades,std::vector<unsigned>& recorrido) {
    recorrido.clear();

    for(unsigned i=0; i!=num_ciudades; ++i)
    {
      recorrido.push_back(i);
    }
    std::random_shuffle(recorrido.begin()+1,recorrido.end());
  }

  // Genera un recorrido segun el orden de ciudad inicial
  void crea_recorrido(unsigned num_ciudades,std::vector<unsigned>& recorrido)  {
    recorrido.clear();
    for(unsigned i=0; i!=num_ciudades; ++i)
    {
      recorrido.push_back(i);
    }
  }

  // Ruta que escoge la primera ciudad, luego la mas cercana, luego la mas cercana a esta ultima, etc...
  void crea_recorrido_avaro(std::vector<unsigned>& recorrido,const ciudades::Ciudades& ciudades)  {
    recorrido.clear();
    std::set<unsigned> set_ciudades; //Lista ordenada (posiblemente un arbol rojinegro)
    std::set<unsigned>::iterator it;

    auto num_ciudades=ciudades.get_num_ciudades();

    for(unsigned i=0; i!=num_ciudades; ++i)
    {
      set_ciudades.insert(i);
    }

    unsigned ciudad=0; //Nuestra primera ciudad del recorrido
    for(unsigned i=0; i<num_ciudades-1; ++i)
    {
      // Añadimos ciudad
      recorrido.push_back(ciudad);
      // Eliminamos la ciudad de nuestro conjunto
      it = set_ciudades.find(ciudad); //Al estar ordenadas dentro de set su busqueda es rapida
      set_ciudades.erase(it);
      ciudad=get_vecino_mas_proximo(ciudad,set_ciudades,ciudades);
    }
    recorrido.push_back(ciudad);
  }

  // Buscamos ciudad mas proxima a ciudad de entre las que quedan en set
  unsigned get_vecino_mas_proximo( const unsigned c,const std::set<unsigned>& set_ciudades,const ciudades::Ciudades& ciudades)  {
    unsigned ciudad = 0;
    std::set<unsigned>::iterator it=set_ciudades.begin();
    // Inicializa la distancia minima
    double min_dist = ciudades.get_distancia(c,*it);


    for(it=set_ciudades.begin(); it!= set_ciudades.end(); ++it)
    {
      unsigned n = *it;
      double dist=ciudades.get_distancia(c,n);

      if(dist<=min_dist)
      {
        ciudad = n;
        min_dist = dist;
      }
    }
    return ciudad;
  }

}
