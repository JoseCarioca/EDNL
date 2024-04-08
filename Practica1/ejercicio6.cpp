//
// Desequilibrio
//
#include "AbinEnla.hpp"
template <typename T> using Abin = AbinEnla<T>;

template <typename T>
int desequilibrio(typename Abin<T>::nodo n, const Abin<T> A)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
        return max
}