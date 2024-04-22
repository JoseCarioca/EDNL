#include <iostream>
#include "abin_E-S.h"
#include "Ejercicio1.HPP"
#include "Ejercicio2Altura.hpp"
#include "Ejercicio3.hpp"
class P {
public:
    static int n;
};
typedef char t;
const t fin = '#';

int main() {
    using namespace std;

    std::cout << "Hello, World!" << std::endl;
    AbinEnla<t> arbol, A, B;
    //ofstream fs("abin.dat"); //abrir fichero de salida
    //imprimirAbin(fs, A, fin);
    //fs.close();
    //cout << "*** Arbol A guardado en fichero abin.dat" << endl;
    P prueba;
    P::n = 5;
    std::cout << P::n << std::endl;
    cout << "Lectura arbol B de abin.dat" << endl;
    //rellenarAbin(arbol,0);
    //imprimirAbin(arbol);
    ifstream fe("abin.dat");//abrir fichero de entrada
    rellenarAbin(fe, B);
    fe.close();
    cout << "Mostrar arbol B" << endl;
    imprimirAbin(B); // en stdcout

    int numnodos, altura;
    numnodos = numNodosAbin(B);
    cout << "Numero de nodos:" << numnodos << endl;
    altura = alturaAbin(B);
    cout << "Altura arbol B:" << altura << endl;
    cout << "profundidad raiz :" << profundidadAbin(B.raiz(), B) << endl;



    return 0;
}

