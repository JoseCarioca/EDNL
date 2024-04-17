//
// Created by epicg on 21/02/2024.
//
//ejercicio 2. Altura de un arbol

#include "AbinEnla.hpp"
#include "algorithm"
template <typename T> using Abin = AbinEnla<T>;

template <typename T>
int alturaAbin(Abin<T>& A)
{
    return alturaAbinRec(A.raiz(), A);
}

template <typename T>
int alturaAbinRec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if ( n == Abin<T>::NODO_NULO )
        //si nodo hoja es altura 0, NODO_NULO debe de ser -1
        return -1;
    else

        return 1 + std::max(alturaAbinRec(A.hijoIzqdo(n), A), alturaAbinRec(A.hijoDrcho(n), A)) ;
}


