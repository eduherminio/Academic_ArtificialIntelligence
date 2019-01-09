#include "../header/sf_extension.h"

namespace sf_extension
{
  sf::Image raw_a_sfml(const std::vector<uint8_t>& m,const unsigned fil,const unsigned col)
  {
    sf::Image im;
    im.create(col,fil); //Dimensiones cambiadas

    for(unsigned i=0; i!=fil; ++i)
    for(unsigned j=0; j!=col; ++j)
    im.setPixel(j,i, {m[i*col+j],m[i*col+j],m[i*col+j]});//Coordenadas cambiadas
    return im;
  }
}
