//
// Created by epicg on 17/04/2024.
// Ejercicio7 - arbol pseudocompleto

#ifndef PRACTICA1_EJERCICIO6PSEUDOCOMPLETO_HPP
#define PRACTICA1_EJERCICIO6PSEUDOCOMPLETO_HPP

#include "AbinEnla.hpp"
#include "Ejercicio2Altura.hpp"

/**
 * Si es vacio o raiz devuelve True
 */
template <typename T> using Abin = AbinEnla<T>;

template <typename T>
int numHijos(typename Abin<T>::nodo n, const Abin<T> &A)
{
    int hijos = 0;
    if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO) ++hijos;
    if (A.hijoDrcho(n) != Abin<T>::NODO_NULO) ++hijos;
    return hijos;
}

template <typename T>
bool pseudocompletoAbin(const Abin<T> &A)
{
    int altura = A.altura(A.raiz());
    if ( altura == -1 || altura == 0) //si arbol vacio o solo raiz
        return true;

    if (altura == 1)
        return (numHijos(A.raiz()) % 2 == 0); //0 o 2 hijos es true

    return pseudocompletoAbinRec(A.raiz(),altura, A);
}

template <typename T>
bool pseudocompletoAbinRec(typename Abin<T>::nodo n, int alturaArbol, const Abin<T> &A)
{
    if(n == Abin<T>::NODO_NULO)
        return true;
    else
    {
        auto hizq = A.hijoIzqdo(n);
        auto hder = A.hijoDrcho(n);
        if (A.profundidad(n) == alturaArbol - 1)
        {
            return ( (hizq == Abin<T>::NODO_NULO) == (hder == Abin<T>::NODO_NULO) );
        }else
        {
            return pseudocompletoAbinRec(hizq,alturaArbol,A) && pseudocompletoAbinRec(hder,alturaArbol,A);
        }
    }
}

#endif //PRACTICA1_EJERCICIO6PSEUDOCOMPLETO_HPP
