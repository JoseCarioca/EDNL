#include <iostream>
#include "alg_grafo_E-S.h"

int main() {
    //ejercicio 1
    vector<vector<int>> matrix;
    // Initialize the vector of vectors with values
    matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    matriz<int> viajes(4, INT_MAX);
    for(size_t i = 0; i < viajes.dimension(); ++i)
    {
        for(size_t j = 0; j < viajes.dimension(); ++j)
        {
            std::cin >> viajes[i][j];
        }
    }
    for(size_t i = 0; i < viajes.dimension(); ++i)
    {
        for(size_t j = 0; j < viajes.dimension(); ++j)
        {
            std::cout << viajes[i][j] << " ";
        }
        std::cout << std::endl;
    }


            std::cout << "Hello, World!" << std::endl;
    return 0;
}
