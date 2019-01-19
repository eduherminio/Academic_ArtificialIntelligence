#ifndef SF_EXTENSION_H_INCLUDED
#define SF_EXTENSION_H_INCLUDED

#include "../header/mnist.h"
#include <SFML/Graphics.hpp>

namespace sf_extension
{
	sf::Image raw_a_sfml(const std::vector<uint8_t>& m, const unsigned fil, const unsigned col);
}


#endif // SF_EXTENSION_H_INCLUDED
