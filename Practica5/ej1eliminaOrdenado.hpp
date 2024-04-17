//
// Created by epicg on 17/04/2024.
//
/**
 * Dado un árbol binario de enteros donde el valor de cada nodo es menor que el de sus
hijos, implementa un subprograma para eliminar un valor del mismo preservando la
propiedad de orden establecida.
 * Precondicion: la propiedad de orden del arbol se cumple.
 * Postcondicion:
 */

#ifndef PRACTICA5_EJ1ELIMINAORDENADO_HPP
#define PRACTICA5_EJ1ELIMINAORDENADO_HPP
#include "../AbinEnla.hpp"

/**
 * Ejercicio 1.
 * ¿y si el abin de entrada no cumple la propiedad?
 * joe si en vez de valor pongo nodo pues es asequible
 * funcionara?
 */
template <typename T>
void eliminaOrdenado(AbinEnla<T>& abin, typename AbinEnla<T>::nodo p)
{
    if (!abin.arbolVacio())
    {

        if ( !abin.hijoIzqdo(p) && !abin.hijoDrcho(p) )
        { //si es hoja

            if (abin.raiz() == p) abin.eliminarRaiz();
            else
            {
                auto padre = abin.padre(p);
                if (abin.hijoIzqdo(padre) == p) { //no sabemos si p es hizq o hder
                    abin.eliminarHijoIzqdo(padre);
                }else abin.eliminarHijoDrcho(padre);
            }

        }else
        { //si NO es hoja
            auto menor = abin.elemento(abin.hijoIzqdo(p)) < abin.elemento(abin.hijoDrcho(p)) ? abin.hijoIzqdo(p) : abin.hijoDrcho(p);
            abin.elemento(p) = abin.elemento(menor);
            eliminaOrdenado(abin, menor); //llama hasta que sea hoja y lo elimine sin problema
        }
    }
}
#endif //PRACTICA5_EJ1ELIMINAORDENADO_HPP
