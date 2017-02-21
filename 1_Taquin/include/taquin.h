#ifndef TAQUIN_H_INCLUDED
#define TAQUIN_H_INCLUDED

#include <cstddef>
#include <vector>
#include <limits>

namespace taquin
{
  struct Nodo_Taquin  { // Nodo_taquin  regla de estilo
    unsigned posicion[9];
    unsigned pos_cas_vac;   // posicion casi ya vacia, refleja la posici�n del 0 sin tener que iterar por el vector para encontrarlo
    int padre;  //int pues el nodo inicial tiene un valor de indice invalido -1. Componente b�sico para reconstruir luego el camino (ver def. de soluci�n).
    unsigned profundidad;
    bool visitado;  // para saber si un nodo ha sido expandido (caso de que no tenga operadores hijo)
                    // sirve para eliminar nodos
  };
    
  class Taquin  {
    public:
      Taquin(unsigned i[],unsigned f[])  {  //Constructor
          set_inicial(i);
          set_objetivo(f);
      }
      void amplitud();

      void profundidad()  {
          size_t max_valor = std::numeric_limits<size_t>::max();
          profundidad(max_valor);
      }
      void profundidad(size_t);
      void solucion();        // Una vez llegado el objetivo, escala hasta 'arriba' para encontrar el camino


    private:
      void set_inicial(const unsigned v[]);  //Podr�an ser p�blicas y de esta forma probar distintas configuraciones
      void set_objetivo(const unsigned v[]); //en el mismo programa y con la misma variable Taquin
      bool prueba_meta(const unsigned [],const unsigned []);  // Dos vectores coinciden
      void expandir(const size_t, const bool amplitud);  // Va construyendo el árbol
      bool repetido(const Nodo_Taquin&,size_t, const bool amplitud);   // Comprueba si un nodo est� repetido, para no volver a expandirlo
      void inicializar_lista();

      std::vector <Nodo_Taquin> lista;
      unsigned indice_objetivo;  //Indice del �rbol en el que se encuentra la solucion
      bool exito;                //A true si encontramos la solucion

      unsigned posicion_inicial[9];
      unsigned posicion_objetivo[9];
  };
}

#endif // TAQUIN_H_INCLUDED
