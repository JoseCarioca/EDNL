//
// Created by epicg on 25/04/2024.
//

#ifndef PRACTICA5_EXAMENREFLEJADOS_HPP
#define PRACTICA5_EXAMENREFLEJADOS_HPP

#include "../AbinEnla.hpp"
//#include "apuntes.hpp"
template <typename T> using Abin = AbinEnla<T>;

template <typename T>
bool sonReflejo(const Abin<T> &A, const Abin<T> &B){
    //no hace falta if a.vacio return b.vacio pero se puede poner por eficiencia
    return sonReflejoRec(A.raiz(), A, B.raiz(), B);
}

template <typename T>
bool sonReflejoRec(typename Abin<T>::nodo nodo_a,const Abin<T> &A,
                   typename Abin<T>::nodo nodo_b, const Abin<T> &B)
{
    //nodo_a != Abin<T>::NODO_NULO && nodo_b != Abin<T>::NODO_NULO A.hijoIzqdo(nodo_a) == Abin<T>::NODO_NULO && A.hijoDrcho(nodo_a) == Abin<T>::NODO_NULO
    //    && B.hijoIzqdo(nodo_b) == Abin<T>::NODO_NULO && B.hijoDrcho(nodo_b) == Abin<T>::NODO_NULO
    if (nodo_a == Abin<T>::NODO_NULO || nodo_b == Abin<T>::NODO_NULO)
    {
        return nodo_a == Abin<T>::NODO_NULO && nodo_b == Abin<T>::NODO_NULO; //ESTA ES BUENA

    }else
    {
        return  ( A.elemento(nodo_a) == B.elemento(nodo_b)  &&
                sonReflejoRec(A.hijoIzqdo(nodo_a), A, B.hijoDrcho(nodo_b), B) &&
                sonReflejoRec(A.hijoDrcho(nodo_a), A, B.hijoIzqdo(nodo_b), B) );
    }
}

template <typename T>
int numNodosReflejadosRec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    //si cualquiera de los dos es nulo no es reflejado, creo que podria poner A.elemento(delHijo) pero acceder a elemento de nulo
    //da fallo? mejor lo dejo asi
    if (A.hijoIzqdo(n) == Abin<T>::NODO_NULO || A.hijoDrcho(n) == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return numNodosReflejadosRec(A.hijoIzqdo(n), A)
        + numNodosReflejadosRec(A.hijoDrcho(n), A)
        + 2* sonReflejoRec(A.hijoIzqdo(n), A, A.hijoDrcho(n), A) ;
    }
}

template <typename T> // Devuelve el número de nodos reflejados
int numNodosReflejados(const Abin<T>& A) {
    if (A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return numNodosReflejadosRec(A.raiz(), A);
    }
}



template <typename T>
Abin<T> reflejo(const Abin<T> &A){
    Abin<T> B;

    if (!A.arbolVacio())
    {
        B.insertarRaiz(A.elemento(A.raiz())); //insertamos la raiz en B y ya podemos pasar la referencia
        reflejoRec(A.raiz(), A, B.raiz(), B);
    }
    return B;

}

template <typename T>
void reflejoRec(typename Abin<T>::nodo nodo_a, const Abin<T> &A, typename Abin<T>::nodo nodo_b, Abin<T> &B)
{
    if (nodo_a != Abin<T>::NODO_NULO)
    {
        if ( A.hijoIzqdo(nodo_a) != Abin<T>::NODO_NULO)
        {
            B.insertarHijoDrcho( nodo_b,
                                 A.elemento( A.hijoIzqdo(nodo_a) ) );

            reflejoRec(A.hijoIzqdo(nodo_a), A, B.hijoDrcho(nodo_b), B);
        }
        if (A.hijoDrcho(nodo_a) != Abin<T>::NODO_NULO) {
            B.insertarHijoIzqdo( nodo_b,
                                 A.elemento (A.hijoDrcho(nodo_a) ) );

            reflejoRec(A.hijoDrcho(nodo_a), A, B.hijoIzqdo(nodo_b), B);
        }
    }
}

#endif //PRACTICA5_EXAMENREFLEJADOS_HPP
