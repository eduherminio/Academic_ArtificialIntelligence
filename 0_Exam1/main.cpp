#include "header/hanoi.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    using namespace std;
    hanoi::Hanoi nodo(3);
    muestra_estado(nodo);

    //Crea todos los hijos del nodo h
    //suponiendo que se ha inicializado en el constructor

    std::vector<hanoi::Hanoi> hijos;
    std::cout<<std::endl;
    for(int i=1; i<4; ++i)
    {
        for(int j=1; j<4; ++j)
        {
            if(i!=j)
                if(nodo.operador_valido(i,j))
                {
                    std::cout<<i<<" "<<j<<std::endl;
                    hijos.push_back(nodo.crea_hijo(i,j));
                }
        }
    }

    //Muestra los hijos
    for(auto &x:hijos)
        muestra_estado(x);

    return 0;
}
