//
// Created by epicg on 21/02/2024.
//
//Ejercicio3
#include "AbinEnla.hpp"
template <typename T> using Abin = AbinEnla<T>;

template <typename T>
int profundidadAbin(typename Abin<T>::nodo n, Abin<T>& A)
{
    int deep = -1;
    while(n != Abin<T>::NODO_NULO){
        ++deep;
        n = A.padre(n);
    }
    return deep;
}

template <typename T>
int profundidadAbinRec(typename Abin<T>::nodo n, Abin<T>& A)
{
    if (n != Abin<T>::NODO_NULO) //o n == A.raiz
        return -1;                  //y aqui return 0
    else
        return 1 + profundidadAbinRec(A.padre(n), A);
}




