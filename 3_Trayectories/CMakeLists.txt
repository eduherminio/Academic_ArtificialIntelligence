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

# After placing FindSFML.cmake in /cmake_modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# Detect and add SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
# Detect an add threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} Threads::Threads)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)





# http://blog.beuc.net/posts/Build_a_SFML_project_with_CMake/
# https://github.com/SFML/SFML/wiki/Tutorial:-Build-your-SFML-project-with-CMake


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
