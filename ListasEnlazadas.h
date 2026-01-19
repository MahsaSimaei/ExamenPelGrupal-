#ifndef LISTASENLAZADAS_H
#define LISTASENLAZADAS_H

#include "Nodo.h"
#include <iostream>
using namespace std;

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza; 

    // --- MÉTODOS PRIVADOS RECURSIVOS (AYUDANTES) ---

    // Ayudante para insertar: Busca el final llamándose a sí mismo
    void insertarRecursivo(Nodo<T>* actual, T dato) {
        // Caso base: Si el siguiente es nulo, insertamos aquí
        if (actual->enlaceNodo() == nullptr) {
            Nodo<T>* nuevoNodo = new Nodo<T>(dato);
            actual->ponerEnlace(nuevoNodo);
        } else {
            // Paso recursivo: Seguimos buscando en el siguiente
            insertarRecursivo(actual->enlaceNodo(), dato);
        }
    }

    // Ayudante para mostrar: Imprime y llama al siguiente
    void mostrarRecursivo(Nodo<T>* actual) const {
        if (actual == nullptr) {
            return; // Caso base: fin de la lista
        }
        // Asumimos que T es un puntero (Soldado*) y tiene mostrarInfo()
        // Si T es un tipo básico, usa cout << actual->datoNodo()
        // Para el examen, como son punteros a Soldado, idealmente:
        // actual->datoNodo()->mostrarInfo(); 
        
        // Mantengo tu lógica genérica:
        cout << actual->datoNodo() << " "; 
        
        mostrarRecursivo(actual->enlaceNodo()); // Paso recursivo
    }

    // Ayudante para borrar todo (Destructor)
    void borrarTodoRecursivo(Nodo<T>* actual) {
        if (actual == nullptr) return;
        
        // Primero borro el resto de la lista (post-orden)
        borrarTodoRecursivo(actual->enlaceNodo());
        
        // Luego borro este nodo
        delete actual;
    }

public:
    // Constructor
    ListaEnlazada() : cabeza(nullptr) {}

    // Destructor Recursivo
    ~ListaEnlazada() {
        borrarTodoRecursivo(cabeza);
    }

    // Insertar un elemento al final (Recursivo)
    void insertarAlFinal(T dato) {
        // Caso especial: lista vacía
        if (cabeza == nullptr) {
            cabeza = new Nodo<T>(dato);
        } else {
            // Llamamos al ayudante recursivo
            insertarRecursivo(cabeza, dato);
        }
    }

    // Imprimir todos los elementos (Recursivo)
    void mostrarLista() const {
        mostrarRecursivo(cabeza);
        cout << endl;
    }
    
    // Obtener la cabeza (necesario para otras funciones recursivas externas)
    Nodo<T>* getCabeza() const {
        return cabeza;
    }
    
    // Método extra útil para el juego: Comprobar si está vacía
    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

#endif //LISTASENLAZADAS_H