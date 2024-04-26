//
// Created by epicg on 26/04/2024.
//

#ifndef PRACTICA3_EJ4PODA_HPP
#define PRACTICA3_EJ4PODA_HPP
#include "AgenEnla.hpp"

void borrarDescendencia(Agen<int>::nodo n, Agen<int>& A);
void podaRec(Agen<int>::nodo n, Agen<int>& A, int x);

void poda(int x, Agen<int>& A)
{
    return podaRec(A.raiz(), A, x);
}

void podaRec(Agen<int>::nodo n, Agen<int>& A, int x)
{
    bool encontrado = false;
    Agen<int>::nodo hijo = A.hijoIzqdo(n);
    if(n != Agen<int>::NODO_NULO && !encontrado)
    {
        if(A.elemento(n) == x)
        {
            encontrado = true;
            borrarDescendencia(n, A);
        }
        else
        {
            hijo = A.hijoIzqdo(n);
            while(hijo != Agen<int>::NODO_NULO)
            {
                podaRec(hijo, A, x);
                hijo = A.hermDrcho(hijo);
            }
        }
    }
}

void borrarDescendencia(Agen<int>::nodo n, Agen<int>& A)
{
    Agen<int>::nodo hijo = A.hijoIzqdo(n);

    if (n != Agen<int>::NODO_NULO)
    {
        while (hijo != Agen<int>::NODO_NULO && A.hijoIzqdo(hijo) == Agen<int>::NODO_NULO)
        {
            A.eliminarHijoIzqdo(n);
            hijo = A.hijoIzqdo(n);
        }
        if (hijo != Agen<int>::NODO_NULO && A.hijoIzqdo(hijo) != Agen<int>::NODO_NULO)
        {
            borrarDescendencia(hijo, A);
            A.eliminarHijoIzqdo(n);
        }
    }
}

#endif //PRACTICA3_EJ4PODA_HPP
