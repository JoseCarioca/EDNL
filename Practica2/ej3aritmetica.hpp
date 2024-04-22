//
// Created by epicg on 20/04/2024.
//

#ifndef PRACTICA2_EJ3ARITMETICA_HPP
#define PRACTICA2_EJ3ARITMETICA_HPP
#include "../AbinEnla.hpp"
template <typename T> using Abin = AbinEnla<T>;
union opera
{
    double operando;
    char operador;
};

double calcularRec(Abin<opera>::nodo n, const Abin<opera> &A)
{
    switch (A.elemento(n).operador) {
        case '*':
            return calcularRec(A.hijoIzqdo(n), A) * calcularRec(A.hijoDrcho(n),A);
        case '/':
            return calcularRec(A.hijoIzqdo(n), A) / calcularRec(A.hijoDrcho(n),A);
        case '+':
            return calcularRec(A.hijoIzqdo(n), A) + calcularRec(A.hijoDrcho(n),A);
        case '-':
            return calcularRec(A.hijoIzqdo(n), A) - calcularRec(A.hijoDrcho(n),A);
        default:
            return A.elemento(n).operando;
    }
}
double calcular(const Abin<opera> &A)
{
    return calcularRec(A.raiz(), A);
}
#endif //PRACTICA2_EJ3ARITMETICA_HPP
