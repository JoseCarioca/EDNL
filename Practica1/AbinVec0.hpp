//
// Created by epicg on 16/02/2024.
//

#ifndef PRACTICA1_ABINVEC0_HPP
#define PRACTICA1_ABINVEC0_HPP

#include <cassert>

template <typename T>
class AbinVec0 {
public:
    typedef size_t nodo;
    static const nodo NODO_NULO;

    explicit AbinVec0(size_t maxNodos);
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHijoDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T& elemento(nodo n) const;
    T& elemento(nodo n);
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    ~AbinVec0();
    //fuera de especificacion
    AbinVec0(const AbinVec0<T>& a);
    AbinVec0<T>& operator =(const AbinVec0<T>& A);
private:
    struct celda {
        T elto;
        nodo padre, hizq, hder;
       //en esta impl no hace falta nodo raiz sino una variable que guarde
       // la dir del vector ah y quizas un nodo raiz vaya

    };
    celda * nodos; //vector de nodos (bueno de celdas diria yo)
    size_t maxNodos;
    size_t numNodos;

    //void destruirNodos(nodo& n); //metodo auxiliar para el destructor??
    //nodo copiar(nodo n);

};

//definicion del nodo nulo
template <typename T>
const typename AbinVec0<T>::nodo AbinVec0<T>::NODO_NULO(SIZE_MAX);

template <typename T>
inline AbinVec0<T>::AbinVec0(size_t maxNodos) :
    nodos(new celda[maxNodos]),
    maxNodos(maxNodos),
    numNodos(0)
{}

template <typename T>
inline void AbinVec0<T>::insertarRaiz(const T &e)
{
    assert(numNodos == 0);
    numNodos = 1;
    nodos[0].elto = e;
    nodos[0].padre = NODO_NULO;
    nodos[0].hizq = NODO_NULO;
    nodos[0].hder = NODO_NULO;
}

template <typename T>
inline void AbinVec0<T>::insertarHijoIzqdo(AbinVec0::nodo n, const T &e)
{
    assert(n >= 0 && n < numNodos); //valido
    assert(nodos[n].hizq == NODO_NULO); //!E hizq
    assert(numNodos < maxNodos); //queda hueco

    nodos[n].hizq = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    ++numNodos;
}

template <typename T>
inline void AbinVec0<T>::insertarHijoDrcho(AbinVec0::nodo n, const T &e)
{
    assert(n >= 0 && n < numNodos); //valido
    assert(nodos[n].hder == NODO_NULO); //!E hizq
    assert(numNodos < maxNodos); //queda hueco

    nodos[n].hder = numNodos;
    nodos[numNodos].elto = e;
    nodos[numNodos].hizq = NODO_NULO;
    nodos[numNodos].hder = NODO_NULO;
    ++numNodos;
}

template <typename T>
void AbinVec0<T>::eliminarHijoIzqdo(AbinVec0::nodo n)
{
    assert(n >= 0 && n < numNodos); //nodo valido
    nodo hizqdo = nodos[n].hizq;
    assert(hizqdo != NODO_NULO); //existe hizqdo
    assert(nodos[hizqdo].hizq == NODO_NULO &&
    nodos[hizqdo].hder == NODO_NULO); //hizq es hoja

    if (hizqdo != numNodos-1)
    {
        //mover el ult nodo a la pos de hizq
        nodos[hizqdo] = nodos[numNodos-1];
        //actualizar pos del nodo padre
        nodo padre = nodos[hizqdo].padre;
        if (nodos[padre].hizq == numNodos-1)
            nodos[padre].hizq = hizqdo;
        else
            nodos[padre].hder = hizqdo;

        //si el nodo movido tiene hijos actualizar las posiciones de su padre
    if(nodos[hizqdo].hizq != NODO_NULO)
        nodos[nodos[hizqdo].hizq].padre = hizqdo;
    if(nodos[hizqdo].hder != NODO_NULO)
        nodos[nodos[hizqdo].hder].padre = hizqdo;
    }
    nodos[n].hizq = NODO_NULO;
    --numNodos;
}

template <typename T>
void AbinVec0<T>::eliminarHijoDrcho(AbinVec0::nodo n)
{
    assert(n >= 0 && n < numNodos); //nodo valido
    nodo hdrcho = nodos[n].hizq;
    assert(hdrcho != NODO_NULO); //existe hdrcho
    assert(nodos[hdrcho].hizq == NODO_NULO &&
           nodos[hdrcho].hder == NODO_NULO); //hizq es hoja

    if (hdrcho != numNodos-1)
    {
        //mover el ult nodo a la pos de hizq
        nodos[hdrcho] = nodos[numNodos-1];
        //actualizar pos del nodo padre
        nodo padre = nodos[hdrcho].padre;
        if (nodos[padre].hizq == numNodos-1)
            nodos[padre].hizq = hdrcho;
        else
            nodos[padre].hder = hdrcho;

        //si el nodo movido tiene hijos actualizar las posiciones de su padre
        if(nodos[hdrcho].hizq != NODO_NULO)
            nodos[nodos[hdrcho].hizq].padre = hdrcho;
        if(nodos[hdrcho].hder != NODO_NULO)
            nodos[nodos[hdrcho].hder].padre = hdrcho;
    }
    nodos[n].hder = NODO_NULO;
    --numNodos;
}

template <typename T>
inline void AbinVec0<T>::eliminarRaiz()
{
    assert(numNodos == 1);
    numNodos = 0;
}

template <typename T>
inline bool AbinVec0<T>::arbolVacio() const
{ return numNodos == 0;}

template <typename T>
inline const T& AbinVec0<T>::elemento(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}

template <typename T>
inline T& AbinVec0<T>::elemento(nodo n)
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elto;
}

template <typename T>
inline typename AbinVec0<T>::nodo AbinVec0<T>::raiz() const
{
    return numNodos > 0 ? 0 : NODO_NULO;
}

template <typename T>
inline typename AbinVec0<T>::nodo AbinVec0<T>::padre(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return  nodos[n].padre;
}

template <typename T>
inline typename AbinVec0<T>::nodo AbinVec0<T>::hijoIzqdo(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].hizq;
}

template <typename T>
inline typename AbinVec0<T>::nodo AbinVec0<T>::hijoDrcho(nodo n) const
{
    assert(n >= 0 && n < numNodos);
    return nodos[n].hder;
}

template <typename T>
AbinVec0<T>::AbinVec0(const AbinVec0<T>& A) :
    nodos(new celda[A.maxNodos]),
    maxNodos(A.maxNodos),
    numNodos(A.numNodos)
{
    //copiar el vector //por que no con memcopy o asi??
    for (nodo n = 0; n <= numNodos-1; n++)
        nodos[n] = A.nodos[n]; //a o A?
}

template <typename T>
inline AbinVec0<T>::~AbinVec0()
{
    delete[] nodos;
}

template <typename T>
AbinVec0<T>& AbinVec0<T>::operator=(const AbinVec0<T> &A)
{
    if (this != &A) //evitar autoasignacion
    {
        //destruir vector y crear uno nuevo si es necesario
        if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new celda[maxNodos];
        }
        //copiar el vector
        numNodos = A.numNodos;
        for (nodo n = 0; n<= numNodos-1; n++)
            nodos[n] = A.nodos[n];
    }

    return *this;
}

#endif //PRACTICA1_ABINVEC0_HPP