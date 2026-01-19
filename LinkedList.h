
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Nodo.h"
#include <iostream>
#include <functional> // Necesario para pasar funciones
using namespace std;

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int tamano;


    void aplicarRecursivo(Nodo<T>* nodo, function<void(T)> accion) const {
        if (nodo == nullptr) return;
        accion(nodo->datoNodo()); // Ejecuta la acción (mostrar, curar, atacar...)
        aplicarRecursivo(nodo->enlaceNodo(), accion); // Llamada recursiva
    }

    // Ayudante para obtener por índice (Recursivo)
    T getRecursivo(Nodo<T>* nodo, int index, int contador) const {
        if (nodo == nullptr) return nullptr; // O manejar error
        if (contador == index) return nodo->datoNodo();
        return getRecursivo(nodo->enlaceNodo(), index, contador + 1);
    }

    // Ayudante para eliminar por índice (Recursivo)
    Nodo<T>* eliminarRecursivo(Nodo<T>* nodo, int index, int contador, bool& eliminado) {
        if (nodo == nullptr) return nullptr;

        if (contador == index) {
            Nodo<T>* temp = nodo->enlaceNodo();
            // Nota: Aquí NO hacemos delete del dato T, solo del nodo de la lista.
            // La gestión de memoria del objeto T es responsabilidad de quien usa la lista.
            delete nodo;
            eliminado = true;
            return temp;
        }

        nodo->ponerEnlace(eliminarRecursivo(nodo->enlaceNodo(), index, contador + 1, eliminado));
        return nodo;
    }

public:
    ListaEnlazada() : cabeza(nullptr), tamano(0) {}

    // Insertar (puedes dejar tu versión recursiva, está bien)
    void insertarAlFinal(T dato) {
        if (cabeza == nullptr) {
            cabeza = new Nodo<T>(dato);
        } else {
            insertarAux(cabeza, dato);
        }
        tamano++;
    }

    void insertarAux(Nodo<T>* nodo, T dato) {
        if (nodo->enlaceNodo() == nullptr) {
            nodo->ponerEnlace(new Nodo<T>(dato));
        } else {
            insertarAux(nodo->enlaceNodo(), dato);
        }
    }

    // --- MÉTODOS CLAVE PARA LA RÚBRICA ---

    // 1. Ejecutar algo en todos los elementos (RECURSIVO)
    // Esto sustituye a los bucles for/while fuera de la lista
    void paraCadaElemento(function<void(T)> accion) {
        aplicarRecursivo(cabeza, accion);
    }

    // 2. Obtener elemento (necesario para reforzar tropas)
    T obtener(int indice) {
        return getRecursivo(cabeza, indice, 0);
    }

    // 3. Eliminar (necesario para mover soldado de Reserva a Tropa)
    void eliminar(int indice) {
        bool eliminado = false;
        cabeza = eliminarRecursivo(cabeza, indice, 0, eliminado);
        if (eliminado) tamano--;
    }

    int getTamano() const { return tamano; }
    bool estaVacia() const { return cabeza == nullptr; }
};
#endif //LINKEDLIST_H
