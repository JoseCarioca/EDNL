//
// Created by epicg on 20/04/2024.
//

#ifndef PRACTICA2_EJ2REFLEJO_HPP
#define PRACTICA2_EJ2REFLEJO_HPP
#include "../AbinEnla.hpp"
template <typename T> using Abin = AbinEnla<T>;

template <typename T> // por copia? bue
Abin<T> reflejo(const Abin<T> &A){
    Abin<T> B; // si se crea antes para pasar por ref  a la funcion auxiliar
    //no hace falta if a.vacio return b.vacio pero se puede poner por eficiencia
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

#endif //PRACTICA2_EJ2REFLEJO_HPP
