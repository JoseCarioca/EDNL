/**
 * PARCIAL DE ÁRBOLES 2024
 * Reflejo de un árbol general
 */
#ifndef PARCIALARBOLES2024_HPP
#define PARCIALARBOLES2024_HPP

#include "AgenEnla.hpp"
template <typename T>
void reflejoRec(typename Agen<T>::nodo nodo_a, const Agen<T>& A,
                typename Agen<T>::nodo nodo_r, Agen<T>& R);

template <typename T>
Agen<T> reflejos(const Agen<T> &A)
{
    Agen<T> R;
    if(!A.arbolVacio())
    {
        R.insertarRaiz(A.elemento(A.raiz()));
        reflejoRec(A.raiz(),A,R.raiz(), R);
    }
    return R;
}
template <typename T>
void reflejoRec(typename Agen<T>::nodo nodo_a, const Agen<T>& A,
                typename Agen<T>::nodo nodo_r, Agen<T>& R)
{
    if(nodo_a != Agen<T>::NODO_NULO)
    {
        auto hijoA = A.hijoIzqdo(nodo_a);
        while( hijoA != Agen<T>::NODO_NULO)
        {
            R.insertarHijoIzqdo(nodo_r, A.elemento(hijoA));
            reflejoRec(hijoA, A, R.hijoIzqdo(nodo_r), R);
            hijoA = A.hermDrcho(hijoA);
        }
    }
}
//auxiliar de pruba para probar en el main
void pruebaReflejo(Agen<int> &A)
{
    A.insertarRaiz(0);
    auto n = A.raiz(); A.insertarHijoIzqdo(n,1);
    n = A.hijoIzqdo(n); A.insertarHermDrcho(n,3); A.insertarHermDrcho(n,2);
    n = A.hermDrcho(n); A.insertarHijoIzqdo(n,4);
    n = A.hijoIzqdo(n); A.insertarHermDrcho(n,5);
}


#endif //PARCIALARBOLES2024_HPP
