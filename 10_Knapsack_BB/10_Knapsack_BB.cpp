#include "header/mochila.h"
#include "header/cronometro.h"

int main()
{
    // mochila::Mochila m("../Knapsack_files/4.txt");
    mochila::Mochila m("../Knapsack_files/24.txt");
    Cronometro<std::milli> crono;

    crono.inicio();

    if(m.resolver(bb::Seleccion_variable::estatica))
    {
        std::cout<<"Solution:"<<std::endl;
        m.imprime_solucion();
        std::cout<<"\nVisited nodes= "<<m.get_nodos_expandidos()<<std::endl;
    }

    crono.fin();

    std::cout<<"Time spent: "<<crono<<" ms."<<std::endl;
    std::cout<<std::endl;

    return 0;
}
