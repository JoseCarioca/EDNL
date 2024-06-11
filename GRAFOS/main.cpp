#include <iostream>
#include "alg_grafo_E-S.h"

#include "alg_grafoPMC.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

#include "grafoPMC.h"

//prueba de creacion DAT
void createTextDatFile(const std::string& filename);

int main() {
    using namespace std;

    std::cout << "¡Hola, mundo! ¿Cómo estás?" << std::endl;
    std::cout << "Esta línea tiene tildes: á, é, í, ó, ú." << std::endl;
    std::cout << "Esta línea tiene signos especiales: ñ, ü." << std::endl;

    /**
     * Añade '../' a cada fichero ya que la llamada la hace Cmake desde la carpeta cmake-build-debug
     */
    GrafoP<unsigned> carreteras("../entradaGrafo.dat");
    vector<size_t> rutas; //vertice es tipo size_t
    cout << carreteras << endl;
    vector<unsigned> distancias = Dijkstra(carreteras,0,rutas);
    cout << "Distancias mínimas a cada vértice: " <<distancias << endl;
    cout << "Rutas a seguir: " <<rutas << endl;
    return 0;
}



void createTextDatFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Unable to create file " << filename << std::endl;
        return;
    }

    // Example text data
    unsigned n = 3;
    std::vector<std::vector<int>> costes = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    // Write the number of vertices
    outFile << n << std::endl;

    // Write the matrix data
    for (const auto& row : costes) {
        for (const auto& value : row) {
            outFile << value << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
    // Get the absolute path of the file
    std::filesystem::path filePath = std::filesystem::absolute(filename);
    std::cout << "Binary .dat file created successfully: " << filePath << std::endl;
}




//codigo antiguo
void pruebaMatriz0()
{
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
}