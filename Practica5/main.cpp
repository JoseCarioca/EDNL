#include <iostream>
#include "../AbinEnla.hpp"
int main() {
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
AbinEnla<T>::nodo encontrar(AbinEnla<T>& A,typename AbinEnla<T>::nodo p, T& valor)
{
    if (A.elemento(p) == valor) { //encontrado
        return p;
    }else if (A.elemento(p) < valor) { //seguir recorriendo

    }else { //no está ( so elemento(p) > valor
        return AbinEnla<T>::NODO_NULO;
    }
}

