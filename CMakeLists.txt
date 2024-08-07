cmake_minimum_required(VERSION 3.28)
project(Arreglos_Paginados)

set(CMAKE_CXX_STANDARD 26)

add_executable(generator
        src/generator.cpp
        src/generator.h
)

add_executable(sorter
        src/sorter.cpp
        src/sorter.h
        src/PagedArray.cpp
        src/PagedArray.h
        src/quicksort.cpp
        src/quicksort.h
        src/insertionSort.cpp
        src/insertionSort.h
        src/bubbleSort.cpp
        src/bubbleSort.h
)
