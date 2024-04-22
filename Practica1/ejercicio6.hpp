//
// Desequilibrio
//
#include "AbinEnla.hpp"
template <typename T> using Abin = AbinEnla<T>;
template <typename T>
int alturaAbinRec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if ( n == Abin<T>::NODO_NULO )
        //si nodo hoja es altura 0, NODO_NULO debe de ser -1
        return -1;
    else

        return 1 + std::max(alturaAbinRec(A.hijoIzqdo(n), A), alturaAbinRec(A.hijoDrcho(n), A)) ;
}

//todo hacer mas legible
template <typename T>
int desequilibrioRec(typename Abin<T>::nodo n, const Abin<T> A)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
        return std::max(abs(alturaAbinRec(A.hijoIzqdo(n),A) - alturaAbinRec(A.hijoDrcho(n),A) ),
                        std::max(desequilibrioRec(A.hijoIzqdo(n), A), desequilibrioRec(A.hijoDrcho(n)), A) );
}