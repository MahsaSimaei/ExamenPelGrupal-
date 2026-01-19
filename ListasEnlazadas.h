
#ifndef LISTASENLAZADAS_H
#define LISTASENLAZADAS_H

#include "Nodo.h"
#include <iostream>
using namespace std;

// Clase ListaEnlazada genérica usando plantillas
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza; // Puntero al primer nodo de la lista

public:
    // Constructor
    ListaEnlazada() : cabeza(nullptr) {}

    // Destructor
    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->enlaceNodo();
            delete temp;
        }
    }

    // Obtener la cabeza de la lista
    Nodo<T>* getCabeza() const {
        return cabeza;
    }

    // Modificar la cabeza de la lista
    void setCabeza(Nodo<T>* nuevaCabeza) {
        cabeza = nuevaCabeza;
    }

    // Insertar un elemento al final
    void insertarAlFinal(T dato) {
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->enlaceNodo() != nullptr) {
                actual = actual->enlaceNodo();
            }
            actual->ponerEnlace(nuevoNodo);
        }
    }

    // Imprimir todos los elementos
    void mostrarLista() const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->datoNodo() << " ";
            actual = actual->enlaceNodo();
        }
        cout << endl;
    }
};

#endif //LISTASENLAZADAS_H
