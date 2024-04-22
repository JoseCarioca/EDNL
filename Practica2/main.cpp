#include <iostream>
#include "ej1similares.hpp"
#include "ej2reflejo.hpp"
#include "ej3aritmetica.hpp"
#include "../AbinEnla.hpp"
#include "../abin_E-S.h"


int main() {
    Abin<opera> operacion;
    opera aux{};
    aux.operador = '*'; operacion.insertarRaiz(aux);
    auto n = operacion.raiz();
    aux.operando = 7; operacion.insertarHijoIzqdo(n, aux);
    aux.operador = '/'; operacion.insertarHijoDrcho(n,aux);
    n = operacion.hijoDrcho(n);
    aux.operador = '-'; operacion.insertarHijoIzqdo(n, aux);
    aux.operando = 2; operacion.insertarHijoDrcho(n,aux);
    n = operacion.hijoIzqdo(n);
    aux.operando = 15; operacion.insertarHijoIzqdo(n, aux);
    aux.operando = 3.2; operacion.insertarHijoDrcho(n,aux);
    std::cout << calcular(operacion) << std::endl;


    AbinEnla<int> a, b;

    a.insertarRaiz(8);
    auto na = a.raiz();
    a.insertarHijoIzqdo(na,5);
    a.insertarHijoDrcho(na, 7);
    na = a.hijoDrcho(na);
    a.insertarHijoDrcho(na, 6);
    AbinEnla<int> r = reflejo(a);
    b = a;
    std::cout << similares(a,b) << std::endl;
    a.insertarHijoIzqdo(a.hijoIzqdo(a.raiz()), -1);
    std::cout << similares(a,b) << std::endl;
    std::cout << "Arbol A" << std::endl;
    imprimirAbin(a);
    std::cout << "Reflejo de A" << std::endl;
    imprimirAbin(r);

    return 0;
}
