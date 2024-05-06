#include <iostream>
//#include "../AbinEnla.hpp"
#include "ExamenReflejados.hpp"
#include "ParcialArboles2024.hpp"
#include "AgenEnla.hpp"
#include "agen_E-S.hpp"
void rellenarReflejados(Abin<int> &A, Abin<int> &B)
{

    A.insertarRaiz(0);
    auto n = A.raiz();
    A.insertarHijoIzqdo(n,1);
    A.insertarHijoDrcho(n,1);
    A.insertarHijoIzqdo(A.hijoIzqdo(n),2);
    A.insertarHijoDrcho(A.hijoIzqdo(n),3);
    A.insertarHijoIzqdo(A.hijoDrcho(n),3);
    A.insertarHijoDrcho(A.hijoDrcho(n),2);
    n = A.hijoDrcho(n);
    A.insertarHijoDrcho(A.hijoDrcho(n), 8);

    B.insertarRaiz(0);
    n = B.raiz();
    B.insertarHijoIzqdo(n,1);
    B.insertarHijoDrcho(n,1);
    B.insertarHijoIzqdo(B.hijoIzqdo(n),2);
    B.insertarHijoDrcho(B.hijoIzqdo(n),2);
    B.insertarHijoIzqdo(B.hijoDrcho(n),2);
    B.insertarHijoDrcho(B.hijoDrcho(n),2);

}

int main() {
    Agen<int> R;
    pruebaReflejo(R);
    Agen<int> RR = reflejos(R);
    imprimirAgen(R);
    imprimirAgen(RR);
    Abin<int> A,B;
    rellenarReflejados(A,B);
    std::cout << numNodosReflejados(A) << std::endl;
    std::cout << numNodosReflejados(B) << std::endl;



    std::cout << "Hello, World!" << std::endl;
    return 0;
}



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


//recorrido en anchura o como
//de todas formas la funcion buscar puede ser util en el futuro. No seas vago.
template <typename T>
typename Abin<T>::nodo encontrar(AbinEnla<T>& A,typename AbinEnla<T>::nodo p, T& valor)
{
    if (A.elemento(p) == valor) { //encontrado
        return p;
    }else if (A.elemento(p) < valor) { //seguir recorriendo

    }else { //no está ( so elemento(p) > valor
        return AbinEnla<T>::NODO_NULO;
    }
}

