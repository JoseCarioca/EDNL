//
// Created by epicg on 19/02/2024.
//

#ifndef PRACTICA1_ABINVEC1_HPP
#define PRACTICA1_ABINVEC1_HPP
#include <cassert>

template <typename T> class AbinRel {
public:
    typedef size_t nodo; //entre 0 y maxnodos-1
    static  const nodo NODO_NULO;

    explicit  AbinRel(size_t maxNodos, const T& e_nulo = T()); //eNulo llama al
    //constructor por defecto de ese tipo? creo que si
    //AH NO el usuario pasa un valor especifico como 'elto_nulo' a su eleccion

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
    AbinRel(const AbinRel<T>& A);
    AbinRel<T>& operator =(const AbinRel<T>& A);
    ~AbinRel();

    //extra poner en otro lado
    friend void minMaxinsertar(nodo n, const T& e);
private:
    T* nodos;
    size_t maxNodos;
    T ELTO_NULO; //marca celdas vacias
};

template <typename T>
const typename AbinRel<T>::nodo AbinRel<T>::NODO_NULO(SIZE_MAX);

template <typename T>
AbinRel<T>::AbinRel(size_t maxNodos, const T &e_nulo) :
    nodos(new T[maxNodos]),
    maxNodos(maxNodos),
    ELTO_NULO(e_nulo)
{
        //marcar todas las celdas libres
        for (nodo n = 0; n<=maxNodos-1; ++n)
            nodos[n] = ELTO_NULO;
}

template <typename T>
inline void AbinRel<T>::insertarRaiz(const T &e)
{
    assert(nodos[0] == ELTO_NULO);
    nodos[0] = e;
}

template <typename T>
void AbinRel<T>::insertarHijoIzqdo(AbinRel::nodo n, const T &e)
{
    assert(n >= 0 && n <= maxNodos-1); //Nodo valido (dentro del rango)
    assert(nodos[n] != ELTO_NULO); //nodo del arbol (elemento no nulo)
    assert(2*n+1 < maxNodos); //hizq cabe en arbol (dentro del rango)
    assert(nodos[2*n+1] == ELTO_NULO); //n no tiene hizq

    nodos[2*n+1] = e;
}

template <typename T>
void AbinRel<T>::insertarHijoDrcho(AbinRel::nodo n, const T &e)
{
    assert(n >= 0 && n <= maxNodos-1); //nodo valido
    assert(nodos[n] != ELTO_NULO); //nodo del arbol (existe)
    assert(2*n+2 < maxNodos); //hder dentro del ranog //xq ponen aqui <maxnodos y otras <= maxnodos-1
    assert(nodos[2*n+2] == ELTO_NULO); //n no tiene hder

    nodos[2*n+2] = e;
}

template <typename T>
void AbinRel<T>::eliminarHijoIzqdo(AbinRel::nodo n)
{
    assert(n >= 0 && n <= maxNodos-1); //Nodo valido (dentro del rango)
    assert(nodos[n] != ELTO_NULO); //nodo del arbol (elemento no nulo)
    assert(2*n+1 < maxNodos); //hizq cabe en arbol (dentro del rango)
    assert(nodos[2*n+1] != ELTO_NULO); //n SI tiene hizq

    //Vemos si hizq de n es hoja.
    size_t hizqHijo= 2*(2*n+1)+1; //hijo izq de hijo izq
    size_t hderHijo = hizqHijo + 1; //hijo der de hijo izq
    if( hderHijo < maxNodos) //miramos si los posibles hijos de hizq estan en el rango
        assert(nodos[hizqHijo] == ELTO_NULO && //hizq
        nodos[hderHijo == ELTO_NULO]); //es hoja?
    //puede que hderHijo fuera de rango pero hizqHijo justo no
    else if (nodos[hizqHijo] == maxNodos-1) //es justo el ultimo
        assert(nodos[hizqHijo] == ELTO_NULO); //y es hoja

    nodos[2*n+1] = ELTO_NULO;
}

template <typename T>
void AbinRel<T>::eliminarHijoDrcho(AbinRel::nodo n)
{
    assert(n >= 0 && n <= maxNodos-1); //Nodo valido (dentro del rango)
    assert(nodos[n] != ELTO_NULO); //nodo del arbol (elemento no nulo)
    assert(2*n+2 < maxNodos); //hder cabe en arbol (dentro del rango)
    assert(nodos[2*n+2] != ELTO_NULO); //n SI tiene hder

    //Vemos si hizq de n es hoja.
    size_t hizqHijo= 2*(2*n+2)+1; //hijo izq de hijo izq
    size_t hderHijo = hizqHijo + 1; //hijo der de hijo izq
    if( hderHijo < maxNodos) //miramos si los posibles hijos de hder estan en el rango
        assert(nodos[hizqHijo] == ELTO_NULO && //hder
               nodos[hderHijo == ELTO_NULO]); //es hoja?
        //puede que hderHijo fuera de rango pero hizqHijo justo no
    else if (nodos[hizqHijo] == maxNodos-1) //es justo el ultimo
        assert(nodos[hizqHijo] == ELTO_NULO); //y es hoja

    nodos[2*n+2] = ELTO_NULO;
}

template <typename T>
void AbinRel<T>::eliminarRaiz()
{
    assert(nodos[0] != ELTO_NULO); //si arbol no vacio
    assert(nodos[1] == ELTO_NULO &&
    nodos[2] == ELTO_NULO); //y raiz es hoja

    nodos[0] = ELTO_NULO;
}

template <typename T>
inline bool AbinRel<T>::arbolVacio() const
{
    return (nodos[0] == ELTO_NULO);
}

template <typename T>
inline const T& AbinRel<T>::elemento(AbinRel::nodo n) const
{
    assert(n >= 0 && n <= maxNodos-1); //nodo valido
    assert(nodos[n] != ELTO_NULO); //nodo del arbol
    return nodos[n];
}

template <typename T>
inline T& AbinRel<T>::elemento(nodo n)
{
    assert(n >= 0 && n <= maxNodos-1); //nodo valido
    assert(nodos[n] != ELTO_NULO); //nodo del arbol
    return nodos[n];
}

template <typename T>
inline typename AbinRel<T>::nodo AbinRel<T>::raiz() const
{
    return (nodos[0] == ELTO_NULO) ? NODO_NULO : 0;
}

template <typename T>
inline typename AbinRel<T>::nodo AbinRel<T>::padre(AbinRel::nodo n) const
{
    //¿qué dice la especificacion?? ¿Padre de raiz se puede hacer? Respuesta: Sí
    assert(n >= 0 && n <= maxNodos-1); //nodo valido
    assert(nodos[n] != ELTO_NULO);

    return (n == 0) ? NODO_NULO : (n-1)/2;
}

//again comprobar la especificacion pls todo
//Respuesta: si no existe, devuelve NODO_NULO
template <typename T>
inline typename AbinRel<T>::nodo AbinRel<T>::hijoIzqdo(AbinRel::nodo n) const
{
    assert(n >= 0 && n <= maxNodos-1); //nodo valido
    assert( nodos[n] != ELTO_NULO); //nodo existe (nodo del arbol bue)
    //assert(2*n +)
    return (2*n+1 >= maxNodos || nodos[2*n+1] == ELTO_NULO) ? NODO_NULO : 2*n+1;

}

template <typename T>
inline typename AbinRel<T>::nodo AbinRel<T>::hijoDrcho(AbinRel::nodo n) const
{
    assert(n >= 0 && n <= maxNodos-1);
    assert(nodos[n] != ELTO_NULO);
                                //claro si es eltonulo no puedes devolverlo, tiene
                                //que devolver NODO_NULO
    return (2*n+2 >= maxNodos || nodos[2*n+2] == ELTO_NULO) ? NODO_NULO : 2*n+2;
}

//copia
template <typename T>
AbinRel<T>::AbinRel(const AbinRel<T>& A) :
    nodos(new T[A.maxNodos]),
    maxNodos(A.maxNodos),
    ELTO_NULO(A.ELTO_NULO)
{
    for(nodo n = 0; n<=maxNodos-1; ++n)
        nodos[n] = A.nodos[n];
}

template <typename T>
inline AbinRel<T>::~AbinRel()
{
    delete[] nodos;
}

template <typename T>
AbinRel<T>& AbinRel<T>::operator =(const AbinRel<T>& A)
{
    if (this != & A)
    {
        //destruir el vector y crear uno nuevo si es necesario
        if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        ELTO_NULO = A.ELTO_NULO;
        //copiar
        for (nodo n = 0; n<=maxNodos-1; ++n)
            nodos[n] = A.nodos[n];
    }
    return *this;
}

#endif //PRACTICA1_ABINVEC1_HPP
