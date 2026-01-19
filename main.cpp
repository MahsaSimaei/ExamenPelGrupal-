#include <string>
#include <iostream>
#include "LinkedList.h"
using namespace std;

// Suponemos que existe un enum llamado TipoItem
enum class TipoItem {
    BOOST_EXPERIENCIA,
    BOOST_PODER,
    CURACION,
    // ... puedes añadir más según necesites
};

// Clase base Item
class Item {
private:
    string nombre;
    TipoItem tipo;
    int valor;

public:
    Item(const string& nombre = "", TipoItem tipo = TipoItem::BOOST_EXPERIENCIA, int valor = 0)
        : nombre(nombre), tipo(tipo), valor(valor) {}

    // ✅ Evitar copias: devolver referencia const
    const string& getNombre() const { return nombre; }
    TipoItem getTipo() const { return tipo; }
    int getValor() const { return valor; }

    void setNombre(const string& nombre) { this->nombre = nombre; }
    void setTipo(TipoItem tipo) { this->tipo = tipo; }
    void setValor(int valor) { this->valor = valor; }

    // ✅ Evitar copias: devolver literal (const char*)
    const char* getTipoString() const {
        switch (tipo) {
            case TipoItem::BOOST_EXPERIENCIA: return "Boost Experiencia";
            case TipoItem::BOOST_PODER:       return "Boost Poder";
            case TipoItem::CURACION:          return "Curacion";
            default:                          return "Desconocido";
        }
    }

    void mostrarInfo() const {
        cout << "Item: " << nombre
             << " | Tipo: " << getTipoString()
             << " | Valor: " << valor << endl;
    }
};

// Clase Soldado
class Soldado {
private:
    string nombre;
    bool esAliado;
    int nivel;
    int poderCombate;
    int experienciaActual;
    int experienciaParaNivel;

    // ✅ Reemplaza el while por recursividad (por si la exigencia prohíbe bucles)
    void procesarSubidasNivel() {
        if (experienciaActual < experienciaParaNivel) return;
        subirNivel();
        procesarSubidasNivel();
    }

public:
    Soldado(const string& nombre = "", bool esAliado = true, int nivel = 1,
            int poderCombate = 10, int expActual = 0, int expParaNivel = 100)
        : nombre(nombre), esAliado(esAliado), nivel(nivel),
          poderCombate(poderCombate), experienciaActual(expActual),
          experienciaParaNivel(expParaNivel) {}

    // Getters
    // ✅ Evitar copias: devolver referencia const
    const string& getNombre() const { return nombre; }
    bool getEsAliado() const { return esAliado; }
    int getNivel() const { return nivel; }
    int getPoderCombate() const { return poderCombate; }
    int getExperienciaActual() const { return experienciaActual; }
    int getExperienciaParaNivel() const { return experienciaParaNivel; }

    // Setters
    void setNombre(const string& nombre) { this->nombre = nombre; }
    void setEsAliado(bool aliado) { this->esAliado = aliado; }
    void setNivel(int nivel) { this->nivel = nivel; }
    void setPoderCombate(int poder) { this->poderCombate = poder; }

    void ganarExperiencia(int exp) {
        experienciaActual += exp;
        cout << nombre << " gana " << exp << " de experiencia." << endl;

        // ✅ Sin bucles: usar recursividad
        procesarSubidasNivel();
    }

    void subirNivel() {
        nivel++;
        experienciaActual -= experienciaParaNivel;
        // Ejemplo: cada nivel requiere 50% más experiencia
        experienciaParaNivel = static_cast<int>(experienciaParaNivel * 1.5);
        poderCombate = static_cast<int>(poderCombate * 1.2); // +20% de poder por nivel

        cout << nombre << " sube al nivel " << nivel << "!" << endl;
    }

    // ✅ “Puros punteros”: aplicar item por puntero
    void aplicarItem(const Item* item) {
        if (item == nullptr) return;

        cout << nombre << " usa el item: " << item->getNombre() << endl;

        switch (item->getTipo()) {
            case TipoItem::BOOST_EXPERIENCIA:
                ganarExperiencia(item->getValor());
                break;
            case TipoItem::BOOST_PODER:
                setPoderCombate(poderCombate + item->getValor());
                cout << "Poder de combate aumentado en " << item->getValor() << endl;
                break;
            case TipoItem::CURACION:
                // Aquí podrías tener vida máxima y actual, pero no está en el diseño
                cout << "Curacion de " << item->getValor() << " (no implementada completamente)" << endl;
                break;
        }
    }

    void recibirDanio(int danio) {
        // Nota: no hay atributo de vida en la clase actual
        cout << nombre << " recibe " << danio << " de dano." << endl;
    }

    bool estaVivo() const {
        // Sin vida explícita → por ahora siempre vivo
        return true;
    }

    void mostrarInfo() const {
        cout << "Soldado: " << nombre << " ("
             << (esAliado ? "Aliado" : "Enemigo") << ")\n"
             << "  Nivel: " << nivel
             << " | Poder: " << poderCombate
             << " | Exp: " << experienciaActual << "/" << experienciaParaNivel << endl;
    }
};

//Clase Tropa
class Tropa {
private:
    Soldado* soldados[5];
    string nombreTropa;

    void aplicarItemRecursivo(const Item& it, int indice) {
        if(indice >= 5) return;
        if(soldados[indice] != nullptr) {
            soldados[indice]->aplicarItem(&it);
        }
        aplicarItemRecursivo(it, indice + 1);
    }
public:
    Tropa() {
        for(int i=0; i<5; i++) soldados[i] = nullptr;
    }

    bool agregarSoldado(Soldado* s) {
        for(int i=0; i<5; i++) {
            if(soldados[i] == nullptr) {
                soldados[i] = s;
                return true;
            }
        }
        return false;
    }

    void aplicarItemATodos(const Item& it) {
        aplicarItemRecursivo(it, 0);
    }

    // En la clase Tropa
    void mostrarTropaRecursiva(int i) const {
        if (i >= 5) return; // Caso base (Estructura fija de 5 datos)

        if (soldados[i] != nullptr) {
            soldados[i]->mostrarInfo();
        } else {
            cout << "  [" << i + 1 << "] --- Vacio ---" << endl;
        }
        mostrarTropaRecursiva(i + 1); // Paso recursivo
    }
};

//Clase Ejercito
class Ejercito {
private:
    Tropa** tropas;
    string nombreEjercito;
    bool esAliado;
    int numTropas;

public:
    // CORRECCIÓN 1: Constructor que acepta nombre
    Ejercito(string nombre = "Ejercito", bool aliado = true)
        : nombreEjercito(nombre), esAliado(aliado), tropas(nullptr), numTropas(0) {}

    // Destructor (OBLIGATORIO para evitar fugas con array dinámico)
    ~Ejercito() {
        if (tropas != nullptr) delete[] tropas;
    }

    void agregarTropa(Tropa* t) {
        // (Nota: Mantengo su lógica de array manual, aunque es ineficiente)
        Tropa** nuevaLista = new Tropa*[numTropas + 1];
        for(int i=0; i<numTropas; i++) nuevaLista[i] = tropas[i];
        nuevaLista[numTropas] = t;

        if (tropas != nullptr) delete[] tropas;
        tropas = nuevaLista;
        numTropas++;
    }

    void aplicarItemATodos(const Item& it) {
        for(int i=0; i<numTropas; i++) {
            tropas[i]->aplicarItemATodos(it);
        }
    }

    // CORRECCIÓN 2: Getters necesarios para que Jugador funcione
    int getNumTropas() const { return numTropas; }

    Tropa* getTropa(int index) {
        if (index >= 0 && index < numTropas) {
            return tropas[index];
        }
        return nullptr;
    }

    void mostrarInfo() const {
        cout << "Ejercito: " << nombreEjercito << " | Tropas: " << numTropas << endl;
    }
};

//Clase jugador
class Jugador {
private:
    string nombre;
    Ejercito* ejercitoActivo;
    ListaEnlazada<Item*> mochila;
    ListaEnlazada<Soldado*>* reservas;

    // Lógica recursiva para encontrar hueco en el ejército
    bool buscarHuecoEnEjercito(int indexTropa, Soldado* s) {
        if (indexTropa >= ejercitoActivo->getNumTropas()) return false;

        Tropa* t = ejercitoActivo->getTropa(indexTropa);
        // Asumimos que Tropa tiene un método para saber si cabe alguien
        // Como su clase Tropa original devuelve false si falla el agregar:
        if (t && t->agregarSoldado(s)) {
            return true;
        }
        return buscarHuecoEnEjercito(indexTropa + 1, s);
    }

public:
    Jugador(string n) : nombre(n) {
        // Ahora sí coincide con el constructor de Ejercito corregido
        ejercitoActivo = new Ejercito("Ejercito de " + n);
        reservas = new ListaEnlazada<Soldado*>();
    }

    ~Jugador() {
        delete ejercitoActivo;
        delete reservas;
    }

    Ejercito* getEjercitoActual() { return ejercitoActivo; }
    ListaEnlazada<Item*>& getMochila() { return mochila; }
    ListaEnlazada<Soldado*>* getReservas() { return reservas; }

    void reclutar(Soldado* s) { reservas->insertarAlFinal(s); }
    void cogerItem(Item* i) { mochila.insertarAlFinal(i); }

    // Función de refuerzos
    void llamarRefuerzos() {
        cout << "Buscando refuerzos..." << endl;
        // (Lógica implementada en respuestas anteriores, aquí resumida para que compile)
        if (!reservas->estaVacia()) {
            Soldado* s = reservas->getCabeza()->datoNodo(); // Simplificado
            if (buscarHuecoEnEjercito(0, s)) {
                cout << "Refuerzo enviado." << endl;
                reservas->eliminar(0);
            }
        }
    }
};
void mostrarMochilaR(Nodo<Item*>* nodo, int i) {
    if (nodo == nullptr) return;
    cout << "[" << i << "] ";
    nodo->datoNodo()->mostrarInfo();
    mostrarMochilaR(nodo->enlaceNodo(), i + 1);
}

void inventarioComandante(Jugador* j) {
    cout << "\n--- INVENTARIO DE COMANDANTE ---" << endl;

    // ERROR ORIGINAL: mostrarMochilaR(j->getMochila().obtener(), 1);

    // CORRECCIÓN: Usar getCabeza()
    mostrarMochilaR(j->getMochila().getCabeza(), 1);

    int op;
    cout << "\nSeleccione item a usar (0 para volver): ";
    cin >> op;

    if(op > 0) {
        // Aquí también arreglamos el acceso para usar getCabeza()
        Nodo<Item*>* aux = j->getMochila().getCabeza();

        for(int i=1; i < op && aux != nullptr; i++) aux = aux->enlaceNodo();

        if(aux != nullptr) {
            j->getEjercitoActual()->aplicarItemATodos(*(aux->datoNodo()));
        }
    }
}

void menuPrincipal() {
    int opcion = -1;

    // Encabezado estilizado según la imagen
    cout << "====================================================" << endl;
    cout << "||                                                ||" << endl;
    cout << "||      BIENVENIDO AL SISTEMA DE BATALLA GISBERIA ||" << endl;
    cout << "||                                                ||" << endl;
    cout << "====================================================" << endl << endl;

    cout << "=== PARTIDAS GUARDADAS ===" << endl << endl;

    cout << "[1] Geo_partida.json" << endl;
    cout << "[2] Crear nueva partida" << endl;
    cout << "[0] Salir" << endl << endl;

    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            cout << "\nCargando partida...\n" << endl;
            // Aquí iría la lógica para cargar el objeto Jugador y su Ejercito
            break;
        case 2:
            cout << "\nIniciando configuracion de nueva partida...\n" << endl;
            break;
        case 0:
            cout << "Saliendo del sistema..." << endl;
            return; // ✅ caso base: termina la recursión
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            break;
    }

    menuPrincipal();
}

void menuGestionSoldados(Jugador* j) {
    int opcion = -1;
    cout << "\n.____________________________________________." << endl;
    cout << "|        GESTION DE SOLDADOS Y TROPAS        |" << endl;
    cout << "|____________________________________________|" << endl;
    cout << "| 1. Crear nueva tropa                       |" << endl;
    cout << "| 2. Modificar tropas del ejercito           |" << endl;
    cout << "| 3. Entrenar soldados de una tropa          |" << endl;
    cout << "| 4. Ver soldados disponibles                |" << endl;
    cout << "| 5. Ver tropas existentes                   |" << endl;
    cout << "| 6. Volver al menu principal                |" << endl;
    cout << "|____________________________________________|" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 4: // Ver soldados disponibles (Lista Enlazada)
            cout << "\n--- SOLDADOS DISPONIBLES EN RESERVA ---" << endl;

            break;

        case 5: // Ver tropas existentes (Estructura fija de 5)
            cout << "\n=== TROPAS EXISTENTES ===" << endl;
            break;

        case 6:
            return; // Caso base para salir de la recursión del menú

        default:
            cout << "Opcion no implementada o no valida." << endl;
            break;
    }

    // Llamada recursiva para mantener el menú activo sin usar while
    menuGestionSoldados(j);
}

// --- MENU PRINCIPAL - EJERCITO (Imagen Blanca) ---
void subMenuEjercito(Jugador* j) {
    int op;
    cout << "\n .____________________________________________." << endl;
    cout << " |          MENU PRINCIPAL - EJERCITO         |" << endl;
    cout << " |____________________________________________|" << endl;
    cout << " |                                            |" << endl;
    cout << " | 1. Ver Informacion del ejercito activo     |" << endl;
    cout << " | 2. Gestionar soldados                      |" << endl;
    cout << " | 3. Inventario de comandante                |" << endl;
    cout << " | 4. Hoguera de Batalla                      |" << endl;
    cout << " | 5. Salir                                   |" << endl;
    cout << " .____________________________________________." << endl;
    cout << " Seleccione una opcion: "; cin >> op;

    switch(op) {
        case 1: j->getEjercitoActual()->aplicarItemATodos(Item("Info", TipoItem::BOOST_PODER, 0)); break;
        case 2: menuGestionSoldados(j); break;
        case 3: inventarioComandante(j); break;
        case 5: return;
    }
    subMenuEjercito(j); // Paso recursivo
}

int main() {
    // Menú principal
    menuPrincipal();

    // ✅ Ejemplo de uso rápido con “puros punteros”
    Soldado* s1 = new Soldado("Legionario", true, 1, 15);
    Item* pocion = new Item("Pocion de Fuerza", TipoItem::BOOST_PODER, 8);

    s1->mostrarInfo();
    s1->aplicarItem(pocion);
    s1->ganarExperiencia(70);
    s1->mostrarInfo();

    // ✅ Liberación (en el proyecto real dependerá del ownership)
    delete pocion;
    delete s1;

    return 0;
}