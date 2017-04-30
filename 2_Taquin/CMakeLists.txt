cmake_minimum_required(VERSION 2.8)
project( $ENV{env_filename} )

file(GLOB_RECURSE SOURCES
	"include/*.h"
	"include/*.hpp"
	"src/*.cpp"
	"src/*.c"
)

SET(CMAKE_CXX_FLAGS "-std=c++14")

add_executable( ${PROJECT_NAME} ${PROJECT_NAME}.cpp ${SOURCES})


# cmake_minimum_required(VERSION 2.8)
#   This line must go first in the file

# project($ENV{env_filename})
#   avoids creating a variable for the name, allowing to use ${PROJECT_NAME} whenever its necessary
#   This allows to place project() before anything else but cmake_minimum_required()


#
# Author:      Eduardo Cáceres de la Calle
# Subject:     Inteligencia Artificial
# Degree:      Industrial Electronics and Automatic Control Engineering
# University:  Universidad de Valladolid (UVa) - EII
#
# Code written in 2017.
# Uploaded for educational purposes only.
#
#
