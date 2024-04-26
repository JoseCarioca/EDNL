//
// Created by epicg on 26/04/2024.
//

#ifndef PRACTICA3_EJ3DESEQUILIBRIO_HPP
#define PRACTICA3_EJ3DESEQUILIBRIO_HPP
#include "AgenEnla.hpp"
#include <cmath>
template <typename T>
unsigned altura(typename Agen<T>:: nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        unsigned alturaMax = 0;
        while(hijo != Agen<T>::NODO_NULO)
        {
            alturaMax = std::max(alturaMax, altura(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return 1 + alturaMax;
    }
}

template <typename T>
unsigned desequilibrio(const Agen<T>& A)
{
    return desequilibrioRec2(A.raiz(), A);
}

template <typename T>
unsigned desequilibrioRec2(typename Agen<T>::nodo n, const Agen<T>& A)
{
    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
    unsigned alturaMaxima = 0, alturaMinima = UINT_MAX, aux = 0;
    while(hijo != Agen<T>::NODO_NULO)
    {
        aux = altura(hijo,A);
        if(aux > alturaMaxima) alturaMaxima = aux;
        if (aux < alturaMinima) alturaMinima = aux;
        hijo = A.hermDrcho(hijo);
    }
    return alturaMaxima - alturaMinima;
}

template <typename T>
unsigned alturaMin(typename Agen<T>:: nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        unsigned alturaMin = altura(n, A);
        while(hijo != Agen<T>::NODO_NULO)
        {
            alturaMin = std::min(alturaMin, altura(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return 1 + alturaMin;
    }
}


template <typename T>
unsigned desequilibrioRec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {

        unsigned desequilibrioMax = 0, alturaMinima = alturaMin(n, A), desNodo = std::fabs(altura(n, A) - alturaMinima );
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo != Agen<T>::NODO_NULO)
        {
            desequilibrioMax = std::max(desNodo, desequilibrioRec(hijo, A));
            hijo = A.hermDrcho(hijo);
        }
        return desequilibrioMax;
    }
}

#endif //PRACTICA3_EJ3DESEQUILIBRIO_HPP
