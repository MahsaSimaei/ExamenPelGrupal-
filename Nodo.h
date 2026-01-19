//
// Created by Medias on 19/01/2026.
//

#ifndef NODO_H
#define NODO_H
template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;
public:
    Nodo(T d) : dato(d), siguiente(nullptr) {}

    T datoNodo() const { return dato; }
    Nodo<T>* enlaceNodo() const { return siguiente; }
    void ponerEnlace(Nodo<T>* sig) { siguiente = sig; }
};
#endif //NODO_H
