#include <iostream>
#include "AgenEnla.hpp"
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}




template <typename T>
void postordenAgen(typename Agen<T>::nodo n, const Agen<T>& A,
                   void (*procesar)(typename Agen<T>::nodo, const Agen<T>&))
// Recorrido en postorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol A. Cada nodo visitado se procesa mediante
// la función procesar().
{
    if (n != Agen<T>::NODO_NULO) {
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO) {
            postordenAgen(hijo, A, procesar);
            hijo = A.hermDrcho(hijo);
        }
        procesar(n, A);
    }
}
template <typename T>
void escribirNodo (typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (n != Agen<T>::NODO_NULO)
        std::cout << A.elemento(n) << ' ';
}