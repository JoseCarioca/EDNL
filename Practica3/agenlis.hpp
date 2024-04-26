//
// Árbol general implementación vectorial mediante listas de hijos

//

#ifndef PRACTICA3_AGENLIS_HPP
#define PRACTICA3_AGENLIS_HPP

#include <cassert>
#include "../listaenla.h"
template <typename T> using Lista = Listaenla<T>;
template <typename T> class Agen {
public:
    typedef size_t nodo;
    static const nodo NODO_NULO;

    explicit Agen(size_t maxNodos);
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHermDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHermDrcho(nodo n);
    void eliminarRaiz();
    const T& elemento(nodo n) const;
    T& elemento(nodo n);
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hermDrcho(nodo n) const;

    Agen(const Agen<T>& A); // Ctor. de copia
    Agen<T>& operator =(const Agen<T>& A); // Asignación de árboles
    ~Agen();

private:
    struct celda {
        T elto;
        nodo padre;
        Lista<nodo> hijos;
    };
    celda * nodos;
    size_t maxNodos;
    size_t numNodos;
};

/* Definición del nodo nulo */
template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(SIZE_MAX);

template <typename T>
inline Agen<T>::Agen(size_t maxNodos) :
    nodos(new celda[maxNodos]),
    maxNodos(maxNodos),
    numNodos(0)
{
    for(nodo i = 0; i < maxNodos; ++i)
        nodos[i].padre = NODO_NULO;
}

template <typename T>
inline void Agen<T>::insertarRaiz(const T &e)
{
    assert(numNodos == 0); //arbol vacio

    numNodos = 1;
    nodos[0].elto = e; //hijos vacia y padre en nodo_nulo (ojo)
}
/**
 *
 * Pre: n es un nodo del árbol.
 * Post: Inserta el elemento e como hijo izquierdo del nodo n. Si ya existe hijo
 * izquierdo, éste se convierte en el hermano derecho del nuevo nodo
 */
template <typename T>
void Agen<T>::insertarHijoIzqdo(Agen::nodo n, const T &e)
{
    assert(numNodos > 0); //arbol no está vacio
    assert(n>= 0 && n < maxNodos); // n pertenece al vector
    assert(n == 0 /*es la raiz*/ || nodos[n].padre != NODO_NULO); //celda ocupada
    assert(numNodos < maxNodos); //arbol no está lleno

    //añadir nuevo nodo en primera celda libre
    //todo parece que no reagrupamos quizas por eficiencia? Listas son grandes
    nodo hizqdo;
    for(hizqdo = 1; nodos[hizqdo].padre != NODO_NULO; ++hizqdo);
    nodos[hizqdo].elto = e;
    nodos[hizqdo].padre = n;
    //insertar nuevo nodo al inicio de la lista de hijos de n
    auto Lh = nodos[n].hijos;
    Lh.insertar(hizqdo, Lh.primera());
    ++numNodos;
}

template <typename T>
void Agen<T>::insertarHermDrcho(nodo n, const T& e)
{
    assert(n >/*=*/ 0 && n < maxNodos); // n es un nodo válido. n=0 no lo pongo y así compruebo raiz antes
    assert(nodos[n].padre != NODO_NULO); // n existe y no es la raíz.
    assert(numNodos < maxNodos); // Árbol no lleno.
// Añadir el nuevo nodo en la primera celda libre.
    nodo hedrcho;
    for (hedrcho = 1; nodos[hedrcho].padre != NODO_NULO; ++hedrcho);
    nodos[hedrcho].elto = e;
    nodos[hedrcho].padre = nodos[n].padre; //todos los nodos tienen acceso O(1) al padre pero ellos solo a hizq
// Insertar el nuevo nodo en la lista de hijos del padre
// en la posición siguiente a la de n.
    Lista<nodo>& Lhp = nodos[nodos[n].padre].hijos; // Lista de hijos
                                                    // del padre.
    Lista<nodo>::posicion p = Lhp.primera();
    while (n != Lhp.elemento(p)) p = Lhp.siguiente(p); //busca n en la LH del padre para poder insertar
    Lhp.insertar(hedrcho, Lhp.siguiente(p));
    ++numNodos;
}

//todo leer y entender a partir de aqui

template <typename T>
void Agen<T>::eliminarHijoIzqdo(Agen::nodo n)
{
    nodo hizqdo;
    assert(numNodos > 0); // Árbol no vacío.
    assert(n >= 0 && n <= maxNodos-1); // n es una celda del vector
    assert(n == 0 || nodos[n].padre != NODO_NULO); // que está ocupada.
    Lista<nodo>& Lh = nodos[n].hijos; // Lista de hijos.
    assert(Lh.primera() != Lh.fin()); // Lista no vacía, n tiene hijos.
    hizqdo = Lh.elemento(Lh.primera());
    assert(nodos[hizqdo].hijos.primera() == // Lista vacía, hijo izq.
           nodos[hizqdo].hijos.fin()); // de n es una hoja.
// Eliminar hijo izqdo. de n.
    nodos[hizqdo].padre = NODO_NULO; // Marcar celda libre.
    Lh.eliminar(Lh.primera()); // Eliminar primer nodo de la
// lista de hijos de n.
    --numNodos;
}

template <typename T>
void Agen<T>::eliminarHermDrcho(nodo n)
{
    nodo hdrcho;
    Lista<nodo>::posicion p;
    assert(n >= 0 && n <= maxNodos-1); // n es un nodo válido.
    assert(nodos[n].padre != NODO_NULO); // n existe y no es la raíz.
// Buscar hermano drcho. de n en la lista de hijos del padre.
    Lista<nodo>& Lhp = nodos[nodos[n].padre].hijos; // Lista de hijos
// del padre.
    Lista<nodo>::posicion p = Lhp.primera();
    while (n != Lhp.elemento(p)) p = Lhp.siguiente(p);
    p = Lhp.siguiente(p);
    assert(p != Lhp.fin()); // n tiene hermano drcho.
    hdrcho = Lhp.elemento(p);
    assert(nodos[hdrcho].hijos.primera() == // Lista vacía, hermano
           nodos[hdrcho].hijos.fin()); // drcho. de n es hoja.
// Eliminar hermano drcho. de n.
    nodos[hdrcho].padre = NODO_NULO; // Marcar celda libre.
    Lhp.eliminar(p); // Eliminar hermano de la lista
// de hijos del padre.
    --numNodos;
}

template <typename T>
inline void Agen<T>::eliminarRaiz()
{
    assert(numNodos == 1);
    numNodos = 0;
}
template <typename T>
inline const T& Agen<T>::elemento(nodo n) const
{
    assert(numNodos > 0); // Árbol no vacío.
    assert(n >= 0 && n <= maxNodos-1); // n es una celda del vector
    assert(n == 0 || nodos[n].padre != NODO_NULO); // que está ocupada
    return nodos[n].elto;
}
template <typename T>
inline T& Agen<T>::elemento(nodo n)
{
    assert(numNodos > 0); // Árbol no vacío.
    assert(n >= 0 && n <= maxNodos-1); // n es una celda del vector
    assert(n == 0 || nodos[n].padre != NODO_NULO); // que está ocupada
    return nodos[n].elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const
{
    return (numNodos > 0) ? 0 : NODO_NULO;
}
template <typename T>
inline typename Agen<T>::nodo Agen<T>::padre(nodo n) const
{
    assert(numNodos > 0); // Árbol no vacío.
    assert(n >= 0 && n <= maxNodos-1); // n es una celda del vector
    assert(n == 0 || nodos[n].padre != NODO_NULO); // que está ocupada
    return nodos[n].padre;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hijoIzqdo(nodo n) const
{
    assert(numNodos > 0); // Árbol no vacío.
    assert(n >= 0 && n <= maxNodos-1); // n es una celda del vector
    assert(n == 0 || nodos[n].padre != NODO_NULO); // que está ocupada.
    Lista<nodo>& Lh = nodos[n].hijos;
    if (Lh.primera() != Lh.fin()) // Lista no vacía.
        return Lh.elemento(Lh.primera());
    else
        return NODO_NULO;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hermDrcho(nodo n) const
{
    Lista<nodo>::posicion p;
    assert(numNodos > 0); // Árbol no vacío.
    assert(n >= 0 && n <= maxNodos-1); // n es una celda del vector
    assert(n == 0 || nodos[n].padre != NODO_NULO); // que está ocupada.
    if (n == 0) // n es la raíz.
        return NODO_NULO;
    else
    {
        Lista<nodo>& Lhp = nodos[nodos[n].padre].hijos; // Lista de hijos
// del padre.
        Lista<nodo>::posicion p = Lhp.primera();
        while (n != Lhp.elemento(p)) p = Lhp.siguiente(p);
        p = Lhp.siguiente(p);
        return p != Lhp.fin() ? // n tiene hermano drcho.
               Lhp.elemento(p) : NODO_NULO;
    }
}

template <typename T>
Agen<T>::Agen(const Agen<T>& A) :
        nodos(new celda[A.maxNodos]),
        maxNodos(A.maxNodos), numNodos(A.numNodos)
{
    for (nodo n = 0; n <= maxNodos-1; n++) // Copiar el vector.
        nodos[n] = A.nodos[n];
}
template <typename T>
Agen<T>& Agen<T>::operator =(const Agen<T>& A)
{
    if (this != &A) { // Evitar autoasignación.
// Destruir el vector y crear uno nuevo si es necesario.
        if (maxNodos != A.maxNodos) {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new celda[maxNodos];
        }
        numNodos = A.numNodos;
        for (nodo n = 0; n <= maxNodos-1; n++) // Copiar el vector.
            nodos[n] = A.nodos[n];
    }
    return *this;
}

template <typename T>
inline Agen<T>::~Agen()
{
    delete[] nodos; // También destruye las listas de hijos.
}
#endif //PRACTICA3_AGENLIS_HPP
