cmake_minimum_required(VERSION 3.27)
project(Practica3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Practica3 main.cpp
        agenlis.hpp
        AgenEnla.hpp
        agen_E-S.hpp
        ej1gradoAgen.hpp
        ej2profundidad.hpp
        ej3desequilibrio.hpp
        ej4poda.hpp)
