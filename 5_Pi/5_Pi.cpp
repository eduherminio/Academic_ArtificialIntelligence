#include "header/dardos_pi.h"
#include <cmath>
#include <iomanip>

int main()
{
  unsigned n_iterations;
  std::setprecision(6);
  while(true)
  {
    std::cout<<"\nNumber of iterations: ";
    double input;
    std::cin>>input;
    if(input<0)
      return 0;

    n_iterations= ceil(input);

    Dardos_Pi pi(n_iterations);

    std::cout<<"pi≈ "<<pi.get_pi()<<std::endl;
  }

  return 0;
}
