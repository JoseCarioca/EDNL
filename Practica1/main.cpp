#include <iostream>
#include "AbinEnla.hpp"
#include "abin_E-S.h"

int main() {
    using namespace std;
    typedef char t;
    const t fin = '#';
    std::cout << "Hello, World!" << std::endl;
    AbinEnla<t> arbol, A, B;
    std::cout << "Lectura del arbol A" << std::endl;
    rellenarAbin(A, fin);
    ofstream fs("abin.dat"); //abrir fichero de salida
    imprimirAbin(fs, A, fin);
    fs.close();
    cout << "*** Arbol A guardado en fichero abin.dat" << endl;
    cout << "Lectura arbol B de abin.dat" << endl;
    //rellenarAbin(arbol,0);
    //imprimirAbin(arbol);
    ifstream fe("abin.dat");//abrir fichero de entrada
    rellenarAbin(fe, B);
    fe.close();

    cout << "Mostrar arbol B" << endl;
    imprimirAbin(B); // en stdcout

    return 0;
}
