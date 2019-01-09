#ifndef DARDOS_PI_H_INCLUDED
#define DARDOS_PI_H_INCLUDED

#include <stdexcept>
#include <iostream>
#include <cstdlib>

class Dardos_Pi
{
public:
  Dardos_Pi(const unsigned iterations) { // Constuctor
    try
    {
      if(iterations<100)
      {
        throw std::invalid_argument("Number of iterations must be >=100");
      }
    }
    catch(const std::invalid_argument &mensaje)
    {
      std::cout<<mensaje.what()<<std::endl;
      exit(EXIT_FAILURE);
    }

    Calculate_Pi(iterations);
  }

  double get_pi() const {
    return pi_;
  };

private:
  void Calculate_Pi(const unsigned iterations);

  double pi_;
};

#endif // DARDOS_PI_H_INCLUDED
