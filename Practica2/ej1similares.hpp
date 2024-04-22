//
// Created by epicg on 18/04/2024.
//

#ifndef PRACTICA2_EJ1SIMILARES_HPP
#define PRACTICA2_EJ1SIMILARES_HPP

#include "../AbinEnla.hpp"
template <typename T> using Abin = AbinEnla<T>;

template <typename T>
bool similares(const Abin<T> &A, const Abin<T> &B){
    //no hace falta if a.vacio return b.vacio pero se puede poner por eficiencia
    return similaresRec(A.raiz(), A, B.raiz(), B);
}


template <typename T>
bool similaresRec(typename Abin<T>::nodo nodo_a,const Abin<T> &A,
                  typename Abin<T>::nodo nodo_b, const Abin<T> &B)
{
    if (nodo_a == Abin<T>::NODO_NULO || nodo_b == Abin<T>::NODO_NULO)
    {
        return ( (nodo_a == Abin<T>::NODO_NULO) == (nodo_b == Abin<T>::NODO_NULO) );
    }else
    {
        return ( similaresRec(A.hijoIzqdo(nodo_a), A, B.hijoIzqdo(nodo_b), B) &&
        similaresRec(A.hijoDrcho(nodo_a), A, B.hijoDrcho(nodo_b), B) );
    }
}
#endif //PRACTICA2_EJ1SIMILARES_HPP
