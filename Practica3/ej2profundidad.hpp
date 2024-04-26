//
// Created by epicg on 26/04/2024.
//

#ifndef PRACTICA3_EJ2PROFUNDIDAD_HPP
#define PRACTICA3_EJ2PROFUNDIDAD_HPP
#include "AgenEnla.hpp"
template <typename T>
int profundidadRec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (n == Agen<T>::NODO_NULO)
        return -1;
    else
        return 1 + profundidadRec(A.padre(n), A);
}

#endif //PRACTICA3_EJ2PROFUNDIDAD_HPP
