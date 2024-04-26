//
// Created by epicg on 11/12/2023.
//

#ifndef PRACTICA6_LISTAENLA_H
#define PRACTICA6_LISTAENLA_H

#include <cstddef>
#include <cassert>
template <typename T> class Listaenla {
    struct nodo; //declaracion adelantada privada
public:
    typedef nodo* posicion;
    Listaenla(); //no se si esta bien aun porqué ponia explicit antes?
    bool vacia() const;
    size_t tama() const;
    void insertar(const T& x, posicion p);
    void eliminar(posicion p);
    const T& elemento(posicion p) const;
    T& elemento(posicion p);
    posicion siguiente(posicion p) const;
    posicion anterior(posicion p) const;
    posicion primera() const;
    posicion fin() const;
    Listaenla(const Listaenla& L);
    Listaenla& operator =(const Listaenla& L);
    ~Listaenla();
private:
    struct nodo
    {
        T elto;
        nodo* sig;
        nodo(const T& e = T(), nodo* p= nullptr) : elto(e), sig(p) {} //antes tenia explicit , xq?
    };

    nodo* L; //cabecera
    size_t n; // longitud lista

    //nuevo def
    void copiar(const Listaenla& Lis);
};


template <typename T>
//inline Listaenla<T>::Listaenla() : L(nullptr), n(0) {} //enla0
inline Listaenla<T>::Listaenla() : //enla1
    L(new nodo), //crea cabecera
    n(0)
{
        L->sig = L; //estructura circular
}

//enladef
template <typename T>
inline bool Listaenla<T>::vacia() const { return n == 0;}

template <typename T>
inline size_t Listaenla<T>::tama() const { return n; }

template <typename T>
inline const T& Listaenla<T>::elemento(posicion p) const
{
    assert(p != fin());
    return p->sig->elto;
}

template <typename T>
inline T& Listaenla<T>::elemento (posicion p)
{
    assert(p != fin());
    return p->sig->elto;
}


template <typename T> //enla1
inline typename Listaenla<T>::posicion  Listaenla<T>::siguiente(posicion p) const
{
    // enla 1//assert(p->sig != nullptr); //en enla0 es p != fin()
    assert(p != fin()); //claro ya es de coste 1
    return p->sig;
}

template <typename T> //enladef es igual
inline typename Listaenla<T>::posicion Listaenla<T>::anterior(posicion p) const
{
    assert( p != primera());
    posicion q = primera();
    while (q->sig != p) q = q->sig;
    return q;
}//no entiendo porque en enla1 no cambia si la definicion de posicion ha cambiado...
//bueno aun asi el anterior es siempre el de antes y hay que buscarlo

template <typename T>
inline typename Listaenla<T>::posicion Listaenla<T>::primera() const
{return L->sig;} //enla1 es L? miralo ah claro L en circular apunta al final lol

template <typename T> //enla1
inline typename Listaenla<T>::posicion Listaenla<T>::fin() const
{
    return L; //circular
}
/**
template <typename T> //segunda opcion enla0 2 supongo
void Listaenla<T>::insertar(const T &x, posicion& p)
{
    if (p != fin())
        *p = nodo(x, new nodo(*p));
    else { //insercion el final
        if (vacia())
            p = L = new nodo(x);
        else {
            posicion q = anterior(fin());
            p = q->sig = new nodo(x);
        }
    }
    ++n;
}
*/

template <typename T>
inline void Listaenla<T>::insertar(const T &x, posicion p) //con cabecera y p por valor todo ok
{
    p->sig = new nodo(x, p->sig);
    //el nodo anterior (o sea p) ahora apunta al nuevo?
    if(p == fin())
        L = p->sig; //Nuevo ultimo (fin y cabecera (listacir))
    ++n;
}

/**
template <typename T>
void Listaenla<T>::eliminar(posicion p) //ENLA0 V2
{
    assert(p != nullptr);
    nodo* q = p->sig;
    p->sig = q->sig;
    delete q;
    --n;
}
 //Eliminar enla0
template <typename T>
void Listaenla<T>::eliminar(posicion& p)
{
    assert(p != fin());
    if (p == primera())
    {
        L = p->sig;
        delete p;
        p = primera();
    }
    else {
        posicion q = anterior(p);
        q->sig = p->sig;
        delete p;
        p = q->sig;
    }
    --n;
}
*/

template <typename T>
inline void Listaenla<T>::eliminar(Listaenla::posicion p)
{
    assert(p != fin());
    posicion q = p->sig;
    if (q == fin())
        L = p;
    p->sig = q->sig; //por qué no poner p?
    delete q;
    --n;
}
/*
template <typename T>
inline void Listaenla<T>::eliminar(posicion p)
{
    assert(p->sig != nullptr);
    nodo* q = p->sig;
    p->sig = q->sig;
    delete q;
    --n;
}
*/


//const copia
template <typename T>
inline Listaenla<T>::Listaenla(const Listaenla& Lis) : Listaenla()
{
    copiar(Lis);
}

//asignacion
template <typename T>
Listaenla<T>& Listaenla<T>::operator =(const Listaenla& Lis)
{
    if (this != &Lis){
        while (!vacia()) eliminar(primera());
        copiar(Lis); //buah no entiendo nada
    }
    return *this;
}

//Destructor
template <typename T>
Listaenla<T>::~Listaenla()
{
    nodo* p;
    while (L != L->sig){
        p = L->sig;
        L->sig = p->sig;
        delete p;
    }
    delete L;
}

//Metodo privado
//pero implementado fuera no entiendo bue
template <typename T>
void Listaenla<T>::copiar(const Listaenla& Lis)

{
    for (nodo *p = Lis.L->sig; p != Lis.L; p = p->sig, ++n)
        L = L->sig = new nodo(p->sig->elto, L->sig);

}


#endif //PRACTICA6_LISTAENLA_H
