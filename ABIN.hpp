//
// Created by epicg on 16/02/2024.
//

#ifndef PRACTICA1_ABIN_HPP
#define PRACTICA1_ABIN_HPP

#include <cassert>

template <typename T>
class ABIN {
    struct celda;
public:
    typedef celda* nodo;
    static const nodo NODO_NULO;
    ABIN();
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
    //publico para que el usuario la use (me parece buena idea)
    bool esDelArbol(nodo n) const; //devuelve true si n es nodo del arbol
    ~ABIN();
    //fuera de especificacion
    ABIN(const ABIN<T>& a);
    ABIN<T>& operator =(const ABIN<T>& A);
private:
    nodo r; //nodo raiz del arbol

    struct celda {
        T elto;
        nodo padre, hizq, hder;
        nodo raiz; //copia de la raiz de este nodo como id del arbol
        celda(const T& e, nodo p = NODO_NULO):                      //this.raiz() pero no se si aqui puede ir
                elto(e), padre(p), hizq(NODO_NULO), hder(NODO_NULO), raiz(raiz()) {}
    };



    void destruirNodos(nodo& n); //metodo auxiliar para el destructor??
    nodo copiar(nodo n);

};


/* Definicion del nodo nulo */
template <typename T>
const typename ABIN<T>::nodo ABIN<T>::NODO_NULO(nullptr);

/**
 * Metodos Públicos
 */

template <typename T>
inline ABIN<T>::ABIN() : r(NODO_NULO){}

template <typename T>
inline void ABIN<T>::insertarRaiz(const T &e)
{
    assert(r == NODO_NULO);
    r = new celda(e);
}

template <typename T>
inline void ABIN<T>::insertarHijoIzqdo(ABIN::nodo n, const T &e)
{
    assert(n != NODO_NULO); //claro n existe. se me olvidó
    assert(esDelArbol(n)); //n es del arbol
    assert(n->hizq == NODO_NULO); //No existe hijo izq
    n->hizq = new celda(e,n);
}

template <typename T>
inline void ABIN<T>::insertarHijoDrcho(ABIN::nodo n, const T &e)
{
    assert(n != NODO_NULO);
    assert(esDelArbol(n)); //n es del arbol
    assert(n->hder == NODO_NULO);
    n->hder = new celda(e,n);
}

template <typename T>
inline void ABIN<T>::eliminarHijoIzqdo(ABIN::nodo n)
{
    assert(n != NODO_NULO); //es 'nodo del arbol'
    assert(esDelArbol(n)); //n es del arbol
    assert(n->hizq != NODO_NULO); //existe hijo izq
    assert(n->hizq->hizq == NODO_NULO &&
           n->hizq->hder == NODO_NULO); //hizq es hoja
    delete n->hizq;
    n->hizq = NODO_NULO;
}

template <typename T>
inline void ABIN<T>::eliminarHijoDrcho(ABIN::nodo n)
{
    assert(n != NODO_NULO);
    assert(esDelArbol(n)); //n es del arbol
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
inline void ABIN<e>::eliminarRaiz()
{
    assert(r != NODO_NULO); //el arbol no está vacio
    assert(r->hizq == NODO_NULO && r->hder == NODO_NULO); //raiz es hoja
    delete r;
    r = NODO_NULO;
}

template <typename T>
inline bool ABIN<T>::arbolVacio() const { return r == NODO_NULO; }

template <typename T>
inline bool ABIN<T>::esDelArbol(ABIN::nodo n) const
{
    //deberia hacerlo con un assert y añadir precondiciones?
    return (r != NODO_NULO && n != NODO_NULO && n->raiz == r ); //así devuelve false si nullptr o arbol vacio
    //deberia volver true si vacio o sea nullptr?
}/

template <typename T>
inline const T& ABIN<T>::elemento(ABIN::nodo n) const
{
    assert(esDelArbol(n)); //n es del arbol
    return n->elto;
}

template <typename T>
inline T& ABIN<T>::elemento(ABIN::nodo n)
{
    assert(esDelArbol(n)); //n es del arbol
    return n->elto;
}

template <typename T>
inline typename ABIN<T>::nodo ABIN<T>::raiz() const { return r;}

template <typename T>
inline typename ABIN<T>::nodo ABIN<T>::padre(nodo n) const
{
    assert(esDelArbol(n)); //n es del arbol
    return n->padre; //creo que ya el padre de raiz guarda NODO_NULO y asi estaria bien
}

template <typename T>
inline typename ABIN<T>::nodo ABIN<T>::hijoIzqdo(ABIN::nodo n) const
{
    assert(esDelArbol(n)); //n es del arbol
    return n->hizq;
}

template <typename T>
inline typename ABIN<T>::nodo ABIN<T>::hijoDrcho(ABIN::nodo n) const
{
    assert(esDelArbol(n)); //n es del arbol
    return n->hder;
}

//ctor copia
template <typename T>
inline ABIN<T>::ABIN(const ABIN<T>& A)
{
    r = copiar(A.r); //ahora lo entenderé
}

template <typename T>
ABIN<T>& ABIN<T>::operator =(const ABIN<T>& A)
{
    if (this != &A)
    {
        destruirNodos(r);
        r = copiar(A.r); //podrias llamar al ctor de copia directamente?
    }
    return *this;
}

template <typename T>
inline ABIN<T>::~ABIN()
{
    destruirNodos(r);
}

/**
 * Metodos Privados
 *
 */

template <typename T>
void ABIN<T>::destruirNodos(nodo& n)
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
//todo pd no se qué hacer con la copia porque la dir de memoria no deberia mantenerse, se me ocurre recorrer el arbol una segunda vez editando el contenido pero...
//devuelve copia de un nodo y todos sus descendientes
template <typename T>
typename ABIN<T>::nodo ABIN<T>::copiar(nodo n)
{
    nodo m = NODO_NULO; //creo que no hace falta inicializarlo... preguntar!

    if (n != NODO_NULO) {
        m = new celda(n->elto); //copia de n
        //m->raiz =
        m->hizq = copiar(n->hizq); //copiar subarbol izq
        if (m->hizq != NODO_NULO) m->hizq->padre = m; //vale guarda al padre desde abajo
        m->hder = copiar(n->hder);
        if (m->hder != NODO_NULO) m->hder->padre = m;
    }
    return m;
}//pq copiar devuelve un nodo?

#endif //PRACTICA1_ABIN_HPP
