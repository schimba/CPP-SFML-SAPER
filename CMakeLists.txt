cmake_minimum_required(VERSION 3.9)
project(SpaerDeluxe)

set(CMAKE_CXX_STANDARD 11)

add_executable(SpaerDeluxe  main.cpp Pole.cpp Pole.h Plansza.cpp Plansza.h)




# Detect and add SFML
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SpaerDeluxe ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()