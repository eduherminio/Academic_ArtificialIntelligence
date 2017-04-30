cmake_minimum_required(VERSION 2.8)
project( $ENV{env_filename} C CXX)

file(GLOB_RECURSE SOURCES
	"include/*.h"
	"include/*.hpp"
	"src/*.cpp"
	"src/*.c"
)

SET(CMAKE_CXX_FLAGS "-std=c++14")

add_executable( ${PROJECT_NAME} ${PROJECT_NAME}.cpp ${SOURCES})

# 	After placing FindSFML.cmake in /cmake_modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# 	Detect and add SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
# 	Detect an add threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} Threads::Threads)


# cmake_minimum_required(VERSION 2.8)
#   This line must go first in the file

# project($ENV{env_filename})
#   avoids creating a variable for the name, allowing to use ${PROJECT_NAME} whenever its necessary
#   This allows to place project() before anything else but cmake_minimum_required()

# http://blog.beuc.net/posts/Build_a_SFML_project_with_CMake/
# https://github.com/SFML/SFML/wiki/Tutorial:-Build-your-SFML-project-with-CMake


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
