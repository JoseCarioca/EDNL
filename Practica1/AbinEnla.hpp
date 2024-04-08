//
// Created by epicg on 15/02/2024.
//

#ifndef PRACTICA1_ABINENLA_HPP
#define PRACTICA1_ABINENLA_HPP
#include <cassert>
#include <algorithm>

template <typename T>
class AbinEnla {
    struct celda;
public:
    typedef celda* nodo;
    static const nodo NODO_NULO;
    AbinEnla();
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
    ~AbinEnla();
    //fuera de especificacion
    AbinEnla(const AbinEnla<T>& a);
    AbinEnla<T>& operator =(const AbinEnla<T>& A);
    int altura(nodo n);
    int profundidad(nodo n);
private:
    struct celda {
        T elto;
        nodo padre, hizq, hder;
        //nodo raiz; //copia de la raiz de este nodo como id del arbol
        celda(const T& e, nodo p = NODO_NULO):
        elto(e), padre(p), hizq(NODO_NULO), hder(NODO_NULO) {}
    };

    nodo r; //nodo raiz del arbol

    void destruirNodos(nodo& n); //metodo auxiliar para el destructor??
    nodo copiar(nodo n);

};


/* Definicion del nodo nulo */
template <typename T>
const typename AbinEnla<T>::nodo AbinEnla<T>::NODO_NULO(nullptr);

/**
 * Metodos Públicos
 */

template <typename T>
inline AbinEnla<T>::AbinEnla() : r(NODO_NULO){}

template <typename T>
inline void AbinEnla<T>::insertarRaiz(const T &e)
{
    assert(r == NODO_NULO);
    r = new celda(e);
}

template <typename T>
inline void AbinEnla<T>::insertarHijoIzqdo(AbinEnla::nodo n, const T &e)
{
    assert(n != NODO_NULO); //claro n existe. se me olvidó
    assert(n->hizq == NODO_NULO); //No existe hijo izq
    n->hizq = new celda(e,n);
}

template <typename T>
inline void AbinEnla<T>::insertarHijoDrcho(AbinEnla::nodo n, const T &e)
{
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO);
    n->hder = new celda(e,n);
}

template <typename T>
inline void AbinEnla<T>::eliminarHijoIzqdo(AbinEnla::nodo n)
{
    assert(n != NODO_NULO); //es 'nodo del arbol'
    assert(n->hizq != NODO_NULO); //existe hijo izq
    assert(n->hizq->hizq == NODO_NULO &&
    n->hizq->hder == NODO_NULO); //hizq es hoja
    delete n->hizq;
    n->hizq = NODO_NULO;
}

template <typename T>
inline void AbinEnla<T>::eliminarHijoDrcho(AbinEnla::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO);
    assert(n->hder->hizq == NODO_NULO &&
    n->hder->hdizq == NODO_NULO);
    delete n->hder;
    n->hder = NODO_NULO;
}

/*
 * void eliminarRaiz();
    bool arbolVacio() const;
    const T& elemento(nodo n) const;
    T& elemento(nodo n);
 */

template <typename e>
inline void AbinEnla<e>::eliminarRaiz()
{
    assert(r != NODO_NULO); //el arbol no está vacio
    assert(r->hizq == NODO_NULO && r->hder == NODO_NULO); //raiz es hoja
    delete r;
    r = NODO_NULO;
}

template <typename T>
inline bool AbinEnla<T>::arbolVacio() const { return r == NODO_NULO; }

template <typename T>
inline const T& AbinEnla<T>::elemento(AbinEnla::nodo n) const
{
    assert(n != NODO_NULO); //n es un nodo de algun arbol jsjs
    return n->elto;
}

template <typename T>
inline T& AbinEnla<T>::elemento(AbinEnla::nodo n)
{
    assert(n != NODO_NULO); //n es un nodo de algun arbol jsjs
    return n->elto;
}

template <typename T>
inline typename AbinEnla<T>::nodo AbinEnla<T>::raiz() const { return r;}

template <typename T>
inline typename AbinEnla<T>::nodo AbinEnla<T>::padre(nodo n) const
{
    assert(n != NODO_NULO); //nodo del arbol
    return n->padre; //creo que ya el padre de raiz guarda NODO_NULO y asi estaria bien
}

template <typename T>
inline typename AbinEnla<T>::nodo AbinEnla<T>::hijoIzqdo(AbinEnla::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}

template <typename T>
inline typename AbinEnla<T>::nodo AbinEnla<T>::hijoDrcho(AbinEnla::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hder;
}

//ctor copia
template <typename T>
inline AbinEnla<T>::AbinEnla(const AbinEnla<T>& A)
{
    r = copiar(A.r); //ahora lo entenderé
}

template <typename T>
AbinEnla<T>& AbinEnla<T>::operator =(const AbinEnla<T>& A)
{
    if (this != &A)
    {
        destruirNodos(r);
        r = copiar(A.r); //podrias llamar al ctor de copia directamente?
    }
    return *this;
}

template <typename T>
inline AbinEnla<T>::~AbinEnla()
{
    destruirNodos(r);
}

/**
 * Metodos Privados
 *
 */

template <typename T>
void AbinEnla<T>::destruirNodos(nodo& n)
{
    if (n != NODO_NULO)
    {
        destruirNodos(n->hizq);
        destruirNodos(n->hder);
        delete n;
        n = NODO_NULO;
    }
}
//TODO si hago lo de guardar nodo raiz en cada celda, esta funcion debo modificarla
//devuelve copia de un nodo y todos sus descendientes
template <typename T>
typename AbinEnla<T>::nodo AbinEnla<T>::copiar(nodo n)
{
    nodo m = NODO_NULO;

    if (n != NODO_NULO) {
        m = new celda(n->elto); //copia de n
        m->hizq = copiar(n->hizq); //copiar subarbol izq
        if (m->hizq != NODO_NULO) m->hizq->padre = m; //vale guarda al padre desde abajo
        m->hder = copiar(n->hder);
        if (m->hder != NODO_NULO) m->hder->padre = m;
    }
    return m;
}//pq copiar devuelve un nodo?



template <typename T>
int AbinEnla<T>::altura(AbinEnla::nodo n)
{
    if(n == NODO_NULO)
        return -1;
    else
        return 1 + std::max(altura(n->hizq), altura(n->hder));
}

template <typename T>
int AbinEnla<T>::profundidad(AbinEnla::nodo n)
{
    int prof = 0;
    while (n)
    {
        ++prof;
        n = n->padre;
    }
    return prof;
}
#endif //PRACTICA1_ABINENLA_HPP
