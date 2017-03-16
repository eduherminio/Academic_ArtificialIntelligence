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


#cmake_minimum_required(VERSION 2.8)
#project($ENV{env_filename})
#   These two lines must go first in the file

# set(namefile "0_Intro")
#   creates a variable named namefile

# set(filename $ENV{namefile})
#   accesses an environment variable

# project($ENV{env_filename})
#   avoids creating a variable for the name, allowing to use ${PROJECT_NAME} whenever its necessary
#   This allows to place project() before anything else (but cmake_minimum_required()

#file(STRINGS "filename.txt" filename)
#   creates a variable named filename from the content of filename.txt
#   filename.txt should only have the content of the variable inside
#   (not variable="content")
