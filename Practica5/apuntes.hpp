//
// Created by epicg on 26/04/2024.
//
/**
 * Meter toda la morralla aqui
 */
#ifndef PRACTICA5_APUNTES_HPP
#define PRACTICA5_APUNTES_HPP

#include "../AbinEnla.hpp"
template <typename T> using Abin = AbinEnla<T>;

/**
 * NUMERO DE NODOS
 */
//Funcion auxiliar para llamada
template <typename T>
int numNodosAbin(Abin<T>& A)
{
    return numNodos_rec(A.raiz(), A);
}

template <typename T>
int numNodos_rec(typename Abin<T>::nodo n, const Abin<T>& A)
{
    if ( n == Abin<T>::NODO_NULO )
        return 0;
    else
        return 1 + numNodos_rec(A.hijoIzqdo(n), A) + numNodos_rec(A.hijoDrcho(n), A) ;
}

/**
 * ALTURA Y PROFUNDIDAD COMO METODOS DE LA CLASE
 * //hacer iterativo en algun momento
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
 */
/** PREORDEN ABIN */
template <typename T>
void preordenAbin(typename Abin<T>::nodo n, const Abin<T>& A,
                  void(*procesar)(typename Abin<T>::nodo, const Abin<T>&))
{
    if ( n != Abin<T>::NODO_NULO)
    {
        procesar(n, A);
        preordenAbin(A.hijoIzqdo(n), A);
        preordenAbin(A.hijoDrcho(n), A);
    }
}

/**
 * PSEUDOCOMPLETO
 */
template <typename T>
bool pseudocompletoAbin(const Abin<T> &A)
{
    int altura = A.altura(A.raiz());
    if ( altura == -1 || altura == 0) //si arbol vacio o solo raiz
        return true;

    if (altura == 1)
    {
        int hijos = 0;
        if (A.hijoIzqdo(A.raiz()) != Abin<T>::NODO_NULO) ++hijos;
        if (A.hijoDrcho(A.raiz()) != Abin<T>::NODO_NULO) ++hijos;
        return (hijos % 2 == 0); //0 o 2 hijos es true
    }

    return pseudocompletoAbinRec(A.raiz(),altura, A);
}

template <typename T>
bool pseudocompletoAbinRec(typename Abin<T>::nodo n, int alturaArbol, const Abin<T> &A)
{
    if(n == Abin<T>::NODO_NULO)
        return true;
    else
    {
        auto hizq = A.hijoIzqdo(n);
        auto hder = A.hijoDrcho(n);
        if (A.profundidad(n) == alturaArbol - 1)
        {
            return ( (hizq == Abin<T>::NODO_NULO) == (hder == Abin<T>::NODO_NULO) );
        }else
        {
            return pseudocompletoAbinRec(hizq,alturaArbol,A) && pseudocompletoAbinRec(hder,alturaArbol,A);
        }
    }
}


/**
 * PRACTICA 2
 */
/**
 *
 * SIMILARES Y AROBLES REFLEJADOS
 */
template <typename T>
bool similares(const Abin<T> &A, const Abin<T> &B){
    //no hace falta if a.vacio return b.vacio pero se puede poner por eficiencia
    return similaresRec(A.raiz(), A, B.raiz(), B);
}


template <typename T>
bool similaresRec(typename Abin<T>::nodo nodo_a,const Abin<T> &A,
                  typename Abin<T>::nodo nodo_b, const Abin<T> &B)
{
    if (nodo_a == Abin<T>::NODO_NULO || nodo_b == Abin<T>::NODO_NULO)
    {
        return ( (nodo_a == Abin<T>::NODO_NULO) == (nodo_b == Abin<T>::NODO_NULO) );
    }else
    {
        return ( similaresRec(A.hijoIzqdo(nodo_a), A, B.hijoIzqdo(nodo_b), B) &&
                 similaresRec(A.hijoDrcho(nodo_a), A, B.hijoDrcho(nodo_b), B) );
    }
}

template <typename T> // por copia? bue
Abin<T> reflejo(const Abin<T> &A){
    Abin<T> B; // si se crea antes para pasar por ref  a la funcion auxiliar
    //no hace falta if a.vacio return b.vacio pero se puede poner por eficiencia
    if (!A.arbolVacio())
    {
        B.insertarRaiz(A.elemento(A.raiz())); //insertamos la raiz en B y ya podemos pasar la referencia
        reflejoRec(A.raiz(), A, B.raiz(), B);
    }
    return B;

}
template <typename T>
void reflejoRec(typename Abin<T>::nodo nodo_a, const Abin<T> &A, typename Abin<T>::nodo nodo_b, Abin<T> &B)
{
    if (nodo_a != Abin<T>::NODO_NULO)
    {
        if ( A.hijoIzqdo(nodo_a) != Abin<T>::NODO_NULO)
        {
            B.insertarHijoDrcho( nodo_b,
                                 A.elemento( A.hijoIzqdo(nodo_a) ) );

            reflejoRec(A.hijoIzqdo(nodo_a), A, B.hijoDrcho(nodo_b), B);
        }
        if (A.hijoDrcho(nodo_a) != Abin<T>::NODO_NULO) {
            B.insertarHijoIzqdo( nodo_b,
                                 A.elemento (A.hijoDrcho(nodo_a) ) );

            reflejoRec(A.hijoDrcho(nodo_a), A, B.hijoIzqdo(nodo_b), B);
        }
    }
}











//de otro chaval
/**
 *
 * PODA AGEN
 */
template <typename T> void poda(Agen<T>& A, const T elto)
{
    typename Agen<T>::nodo objetivo=Agen<T>::NODO_NULO;
    buscar_nodo(A.raiz(),A,elto,objetivo);
    if(objetivo!=Agen<T>::NODO_NULO)
    {
        poda_rec(objetivo,A);
    }
}

//BUSCAR NODO
template <typename T> void buscar_nodo(typename Agen<T>::nodo n, const Agen<T>& A, const T elto, typename Agen<T>::nodo& objetivo)
{
    if(n!=Agen<T>::NODO_NULO && objetivo==Agen<T>::NODO_NULO)
    {
        if(A.elemento(n)==elto)
        {
            objetivo=n;
        }
        else
        {
            typename Agen<T>::nodo aux=A.hijoIzqdo(n);
            while(aux!=Agen<T>::NODO_NULO && objetivo==Agen<T>::NODO_NULO)
            {
                buscar_nodo(aux,A,elto,objetivo);
                aux=A.hermDrcho(aux);
            }
        }
    }
}

//esHoja
template <typename T> bool esHoja(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if(n!=Agen<T>::NODO_NULO)
        return (A.hijoIzqdo(n)==Agen<T>::NODO_NULO);
    else
        return 1;
}

//PODA
template <typename T> void poda_rec(typename Agen<T>::nodo n, Agen<T>& A)
{
    while(A.hijoIzqdo(n)!=Agen<T>::NODO_NULO)
    {
        if(esHoja(A.hijoIzqdo(n),A))
        {
            A.eliminarHijoIzqdo(n);
        }
        else
        {
            poda_rec(A.hijoIzqdo(n),A);
        }
    }
}


#endif //PRACTICA5_APUNTES_HPP
