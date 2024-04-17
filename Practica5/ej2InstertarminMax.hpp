//
// Created by epicg on 17/04/2024.
//

#ifndef PRACTICA5_EJ2INSTERTARMINMAX_HPP
#define PRACTICA5_EJ2INSTERTARMINMAX_HPP
#include "../AbinVec1.hpp"
#include <cmath>
/**
 * No se si hacer un tad minmax... de momento que cumpla la precondicion
 * Precondicion: Es un arbol min-max y no esta ya metido?
 */

template <typename T>
void AbinRel::minMaxinsertar(typename AbinRel<T>::nodo n, const T& e)
{
}
template <typename T>
void insertarMin_Max(T &e, typename AbinRel<T>::nodo n, AbinRel<T> &A)
{
    typename AbinRel<T>::nodo hijo;
    if(n % 2 == 0)
    {
        A.insertarHijoDrcho(n, e);
        hijo = A.hijoDrcho(n);
    }//si es par es un hder sino hizq
    else
    {
        A.insertarHijoIzqdo(n, e);
        hijo = A.hijoIzqdo(n);
    }
    int max = log2(n+1); //altura
    if (max % 2 == 0 ) //altura par min, altura impar es max
    {
        T padre = A.elemento(padre(n));
        if (*e > padre)
        {
            A.elemento(hijo) = padre;
            A.elemento(n) = *e;
        }
    }
}
#endif //PRACTICA5_EJ2INSTERTARMINMAX_HPP
