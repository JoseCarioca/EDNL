//
// Created by epicg on 21/02/2024.
//
//ejercicio 1. Numero de nodos de un ABin

#include "AbinEnla.hpp"
template <typename T> using Abin = AbinEnla<T>;

//Funcion auxiliar para llamada
template <typename T>
int numNodosAbin(Abin<T>& A)
{
    return numNodos_rec(A.raiz(), A);
}

template <typename T>
int numNodos_rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if ( n == Abin<T>::NODO_NULO )
        return 0;
    else
        return 1 + numNodos_rec(A.hijoIzqdo(n), A) + numNodos_rec(A.hijoDrcho(n), A) ;
}

//no lo usas al final, guardar para usar en el futuro
template <typename T>
void preordenAbin(typename Abin<T>::nodo n, const Abin<T>& A,
                  void(*procesar)(typename Abin<T>::nodo, const Abin<T>&))
{
    if ( n != Abin<T>::NODO_NULO)
    {
        procesar(n, A);
        preordenAbin(A.hijoIzqdo(n), A);
        preordenAbin(A.hijoDrcho(n), A);
    }
}