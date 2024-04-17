//
// Created by epicg on 22/01/2024.
//PILAENLA ES PILA (por defecto)
//

#ifndef PRACTICA4_PILAENLA_H
#define PRACTICA4_PILAENLA_H
#include <cstddef> //size_t
#include <cassert>

template <typename T>
class Pila {
public:
    Pila();
    bool vacia() const;
    size_t tama() const;
    const T& tope() const;
    void pop();
    void push(const T& x);
    Pila(const Pila& P); //ctor. de copia
    Pila& operator =(const Pila& P); //asignacion entre pilas
    ~Pila();
private:
    struct nodo {
        T elto;
        nodo* sig;
        nodo(const T& e, nodo* p= nullptr) : elto(e), sig(p) {}
    };

    nodo* tope_; //tope
    size_t n_eltos; //n ya lo cambiare

    void copiar(const Pila& P);
};

template <typename T>
inline Pila<T>::Pila() :
    tope_(nullptr),
    n_eltos(0)
{}

template <typename T>
inline bool Pila<T>::vacia() const {return n_eltos == 0;}

template <typename T>
inline size_t Pila<T>::tama() const {return n_eltos;}

template <typename T>
inline const T& Pila<T>::tope() const
{
    assert(!vacia());
    return tope_->elto;
}

template <typename T>
inline void Pila<T>::pop()
{
    assert(!vacia());
    nodo *p = tope_;
    tope_ = p->sig;
    delete p;
    --n_eltos;

}

template <typename T>
inline void Pila<T>::push(const T &x)
{

    tope_ = new nodo(x, tope_);
    ++n_eltos;
}

//constructor de copia
template <typename T>
inline Pila<T>::Pila(const Pila& P) : Pila()
{
    copiar(P);
}

//asignacion
template <typename T>
Pila<T>& Pila<T>::operator=(const Pila<T> &P)
{
    if (this != &P) {
        this->~Pila();
        copiar(P);

    }
    return *this;
}

//detructor
template <typename T>
Pila<T>::~Pila()
{
    nodo *p;
    while (tope_) {
        p = tope_->sig;
        delete tope_;
        tope_ = p;
    }
    n_eltos = 0;
}


//metodo privado
template <typename T>
void Pila<T>::copiar(const Pila<T> &P)
//PRE: *this esta vacia
//post: *this es copia de P
{
    if (!P.vacia()) {
        tope_ = new nodo(P.tope_->elto);
        n_eltos = 1;
        //copiar el resto hasta el fondo de la pila
        nodo *p = tope_;
        nodo *q = P.tope_->sig;
        while (q) {
            p->sig = new nodo(q->elto);
            ++n_eltos;
            p = p->sig;
            q = q->sig;
        }
    }
}


#endif //PRACTICA4_PILAENLA_H
