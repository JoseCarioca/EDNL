//
// Created by epicg on 26/04/2024.
//

#ifndef PRACTICA3_EJ1GRADOAGEN_HPP
#define PRACTICA3_EJ1GRADOAGEN_HPP
#include "AgenEnla.hpp"
#include <cmath>

template <typename T>
unsigned grado(const Agen<T>& A)
{
    return gradoRec(A.raiz(), A);
}

template <typename T>
unsigned gradoRec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else
    {
        unsigned nHijos = 0;
        //o llamar a fun auxiliar
        auto auxHijos = A.hijoIzqdo(n);
        while (auxHijos != Agen<T>::NODO_NULO)
        {
            nHijos++;
            auxHijos = A.hermDrcho(auxHijos);
        }

        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        unsigned max = 0;
        while(hijo != Agen<T>::NODO_NULO)
        {
            max = std::max(max, gradoRec(hijo, A));
            hijo = A.hermDrcho(hijo);
        }
        return std::max(max, nHijos);
    }
}

template <typename T>
unsigned numHijos(typename Agen<T>::nodo n, const Agen<T>& A)
{
    int numHijos = 0;
    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
    while (hijo != Agen<T>::NODO_NULO)
    {
        numHijos++;
        hijo = A.hermDrcho(hijo);
    }
    return numHijos;
}

#endif //PRACTICA3_EJ1GRADOAGEN_HPP
