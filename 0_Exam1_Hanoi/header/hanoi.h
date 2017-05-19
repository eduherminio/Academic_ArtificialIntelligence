#ifndef HANOI_H_INCLUDED
#define HANOI_H_INCLUDED
//Añadir las cabeceras que necesiteis
#include <iostream>
#include <vector>

namespace hanoi
{
    class Hanoi
    {
    public:
       Hanoi(unsigned num)
       {
          num_clavijas=num;
          for(int i=num_clavijas-1; i>-1; i--)
          {
            v1.push_back(i+1);
          }

          // v1.clear();
          // v1.push_back(3);
          // v2.push_back(2);
          // v3.push_back(1);


          // for(auto x:v1)
          //   std::cout<<x<<" ";
          //
          // std::cout<<v1.back();

          //Aqui podeis rellenar "a mano" el estado inicial
          // usando vuestras variables miembro que describen el estado
       }
       bool operador_valido(unsigned,unsigned) const;
       Hanoi crea_hijo(unsigned,unsigned) const;
    private:
        static unsigned num_clavijas;
        std::vector<unsigned> v1;
        std::vector<unsigned> v2;
        std::vector<unsigned> v3;
        //Complete la descripcion del estado

    };
    void muestra_estado(const Hanoi&);
}

#endif // HANOI_H_INCLUDED
