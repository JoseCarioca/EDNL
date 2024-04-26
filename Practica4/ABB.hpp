//
// Created by epicg on 22/04/2024.
//

#ifndef PRACTICA4_ABB_HPP
#define PRACTICA4_ABB_HPP
#include <cassert>

template <typename T> class Abb
{
public:
    Abb();
    const Abb& buscar(const T& e) const;
    void insertar(const T& e);
    void eliminar(const T& e);
    bool vacio() const;
    const T& elemento() const;
    const Abb& izqdo() const;
    const Abb& drcho() const;
    Abb(const Abb& A); //ctor de copia
    Abb& operator =(const Abb& A); //operador de asignacion
    ~Abb(); //destructor
private:
    struct arbol{
        T elto;
        Abb izq, der; //sin &¿? por copia? no porque es un objeto? no se
        arbol(const T& e): elto{e}, izq{}, der{} {} //{} abb vacio
    };

    arbol* r; //raiz del arbol

    T borrarMin(); //funcion auxiliar que ya veremos pa que
};

template <typename T>
inline Abb<T>::Abb(): r(nullptr) {}

template <typename T>
inline bool Abb<T>::vacio() const { return (r == nullptr); }

template <typename T>
const Abb<T>& Abb<T>::buscar(const T &e) const
{
    if (r == nullptr)
        return *this;
    else if (e < r->elto)
        return r->izq.buscar(e); //claro izq es abb asi que puedes buscar
    else if (e > r->elto)
        return r->der.buscar(e);
    else return *this;
}

template <typename T>
void Abb<T>::insertar(const T &e)
{
    if(r == nullptr)
        r = new arbol(e);
    else if(e < r->elto)
        r->izq.insertar(e);
    else if(e > r->elto)
        r->der.insertar(e);
}

template <typename T>
void Abb<T>::eliminar(const T &e)
{
    if (r != nullptr){
        if (e < r->elto)
            r->izq.eliminar(e);
        else if (e > r->elto)
            r->der.eliminar(e);
        else //quitar e de la raiz
            if (!r->izq && !r->der) //1. raiz es hoja
            {
                delete r;
                r = nullptr;
            }else if (!r->der) //2. solo hizq
            {
                arbol* i = r->izq.r; //xq .r y no r->izq a secas?
                r->izq.r = nullptr;
                delete r;
                r = i;
            }else if (!r->izq)
            {
                arbol* d = r->der.r;
                r->der.r = nullptr;
                delete r;
                r = d;
            }else
                //eliminar min del subarbol derecho y sustituir el elemento de la raiz por este
                r->elto = r->der.borrarMin();
    }
}

//metodo privado

template <typename T>
T Abb<T>::borrarMin()
{
    if (r->izq.r == nullptr)
    {
        T e = r->elto;
        arbol* hder = r->der.r;
        r->der.r = nullptr; //evita destruit subarbol der
        delete r;
        r = hder; //sustituye r por subarbol der
        return e;
    }
    else return r->izq.borrarMin(); //sino recursiva
}
//seguimos
template <typename T>
inline const T& Abb<T>::elemento() const
{
    assert(r != nullptr); //pre: arbol no vacio
    return r->elto;
}

template <typename T>
inline const Abb<T>& Abb<T>::izqdo() const
{
    assert(r!= nullptr);
    return r->izq;
}

template <typename T>
inline const Abb<T>& Abb<T>::drcho() const
{
    assert(r!= nullptr);
    return r->der;
}

template <typename T>
inline Abb<T>::Abb(const Abb<T> &A) : r(nullptr)
{
    if (A.r != nullptr)
        r = new arbol(*A.r);
}

template <typename T>
Abb<T>& Abb<T>::operator=(const Abb<T> &A)
{
    if (this != &A)
    {
        this->~Abb();
        if (A.r != nullptr)
            r = new arbol(*A.r);
    }
    return *this;
}

template <typename T>
Abb<T>::~Abb()
{
    if (r != nullptr) { // Árbol no vacío.
        delete r; // Destruir raíz y descendientes con r->~arbol()
        r = nullptr; // El árbol queda vacío.
    }
}
#endif //PRACTICA4_ABB_HPP
