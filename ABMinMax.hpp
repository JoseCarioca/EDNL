//
// Created by epicg on 17/04/2024.
//

#ifndef PRACTICA1_ABminMax_HPP
#define PRACTICA1_ABminMax_HPP


#include <cassert>
template <typename T> class ABminMax {
public:
    explicit ABminMax(size_t maxNodos); // constructor
    void insertar(const T& e);
    void suprimir();
    const T& cima() const;
    bool vacio() const;
    ABminMax(const ABminMax<T>& A); // ctor. de copia
    ABminMax<T>& operator =(const ABminMax<T>& A); // asignación de ABminMax
    ~ABminMax(); // destructor
private:
    typedef size_t nodo; // índice del vector
// entre 0 y maxNodos-1
    T* nodos; // vector de nodos
    size_t maxNodos; // tamaño del vector
    size_t numNodos; // último nodo del árbol
    nodo padre(nodo i) const { return (i-1)/2; }
    nodo hIzq(nodo i) const { return 2*i+1; }
    nodo hDer(nodo i) const { return 2*i+2; }
    void flotar(nodo i);
    void hundir(nodo i);
};


template <typename T>
inline ABminMax<T>::ABminMax(size_t maxNodos) :
        nodos(new T[maxNodos]),
        maxNodos(maxNodos),
        numNodos(0) // ABminMax vacío.
{}
template <typename T>
inline const T& ABminMax<T>::cima() const
{
    assert(numNodos > 0); // ABminMax no vacío.
    return nodos[0];
}
template <typename T>
inline bool ABminMax<T>::vacio() const
{
    return (numNodos == 0);
}
template <typename T>
inline void ABminMax<T>::insertar(const T& e)
{
    assert(numNodos < maxNodos); // ABminMax no lleno.
    nodos[numNodos] = e;
    if (++numNodos > 1)
        flotar(numNodos-1); // Reordenar.
}
template <typename T>
void ABminMax<T>::flotar(nodo i)
{
    T e = nodos[i];
    while (i > 0 && e < nodos[padre(i)])
    {
        nodos[i] = nodos[padre(i)];
        i = padre(i);
    }
    nodos[i] = e;
}
template <typename T>
inline void ABminMax<T>::suprimir()
{
    assert(0 < maxNodos); // ABminMax no lleno.
    if (--numNodos > 0)
    {
        nodos[0] = nodos[numNodos];
        if (numNodos > 1)
            hundir(0);
    }
}
template <typename T>
void ABminMax<T>::hundir(nodo i)
{
    bool fin = false;
    T e = nodos[i];
    while (hIzq(i) < numNodos && !fin) // Hundir e.
    {
        nodo hMin; // Hijo menor del nodo i.
        if (hDer(i) < numNodos && nodos[hDer(i)] < nodos[hIzq(i)])
            hMin = hDer(i);
        else
            hMin = hIzq(i);
        if (nodos[hMin] < e) { // Subir el hijo menor.
            nodos[i] = nodos[hMin];
            i = hMin;
        }
        else // e <= nodos[hMin]
            fin = true;
    }
    nodos[i] = e; // Colocar e.
}
template <typename T>
inline ABminMax<T>::~ABminMax()
{
    delete[] nodos;
}
template <typename T>
ABminMax<T>::ABminMax(const ABminMax<T>& A) :
        nodos(new T[A.maxNodos]),
        maxNodos(A.maxNodos),
        numNodos(A.numNodos)
{
// Copiar el vector.
    for (nodo n = 0; n < numNodos; n++)
        nodos[n] = A.nodos[n];
}
template <typename T>
ABminMax<T>& ABminMax<T>::operator =(const ABminMax<T>& A)
{
    if (this != &A) // Evitar autoasignación.
    { // Destruir el vector y crear uno nuevo si es necesario.
        if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        numNodos = A.numNodos;
// Copiar el vector
        for (nodo n = 0; n < numNodos; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}
#endif //PRACTICA1_ABminMax_HPP
