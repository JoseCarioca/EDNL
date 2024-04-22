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
void insertarMin_Max(const T &e, typename AbinRel<T>::nodo n, AbinRel<T> &A)
{
    typename AbinRel<T>::nodo hijo;
    //se entiende que n es el ulitmo nodo añadido en un arbol
    if(A.hijoIzqdo(n) == AbinRel<T>::NODO_NULO )
    {
        A.insertarHijoIzqdo(n, e);
        hijo = A.hijoIzqdo(n);
    }//si es par es un hder sino hizq
    else
    {
        A.insertarHijoDrcho(n, e);
        hijo = A.hijoDrcho(n);
    }
    int max = log2(n+1); //altura del nodo n
    if (max % 2 == 0 ) //altura par -> hijo es min, altura impar es max
    {
        if (e > A.elemento(n)) //e es el hijo n es su padre
        {
            A.elemento(hijo) = A.elemento(n);
            A.elemento(n) = e;
            //abuelo de n
            size_t abuelo = (n-1)/2; abuelo = (abuelo - 1)/2; //no se me ocurre otra manera
            while(abuelo < n && e > A.elemento(abuelo)) //mientras elemento > abuelo
            {
                A.elemento(n) = A.elemento(abuelo);
                A.elemento(abuelo) = n;
                n = abuelo;
                abuelo = (abuelo-1)/2; abuelo = (abuelo-1)/2;
            }

        }else if (e < A.elemento(A.padre(n)))
        {
            A.elemento(hijo) = A.elemento(A.padre(n));
            A.elemento(A.padre) = e;
            size_t abuelo = (n-1)/2; abuelo = (abuelo - 1)/2;
            while (abuelo < n && e < A.elemento(abuelo))
            {
                A.elemento(n) = A.elemento(abuelo);
                A.elemento(abuelo) = n;
                n = abuelo;
                abuelo = (abuelo-1)/2; abuelo = (abuelo-1)/2;
            }

        }
    }else
    {

    }
}
#endif //PRACTICA5_EJ2INSTERTARMINMAX_HPP
