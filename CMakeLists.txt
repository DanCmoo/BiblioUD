cmake_minimum_required(VERSION 3.28.1)
project(Biblioteca)

set(CMAKE_CXX_STANDARD 14)

add_executable(Biblioteca
        src
        src/main.cpp
        src/models/Autor.cpp
        src/models/Edicion.cpp
)

