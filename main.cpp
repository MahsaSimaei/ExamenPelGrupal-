#include <string>
#include <iostream>
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

    string getNombre() const { return nombre; }
    TipoItem getTipo() const { return tipo; }
    int getValor() const { return valor; }

    void setNombre(const string& nombre) { this->nombre = nombre; }
    void setTipo(TipoItem tipo) { this->tipo = tipo; }
    void setValor(int valor) { this->valor = valor; }

    string getTipoString() const {
        switch (tipo) {
            case TipoItem::BOOST_EXPERIENCIA: return "Boost Experiencia";
            case TipoItem::BOOST_PODER:       return "Boost Poder";
            case TipoItem::CURACION:          return "Curación";
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

public:
    Soldado(const string& nombre = "", bool esAliado = true, int nivel = 1,
            int poderCombate = 10, int expActual = 0, int expParaNivel = 100)
        : nombre(nombre), esAliado(esAliado), nivel(nivel),
          poderCombate(poderCombate), experienciaActual(expActual),
          experienciaParaNivel(expParaNivel) {}

    // Getters
    string getNombre() const { return nombre; }
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

        while (experienciaActual >= experienciaParaNivel) {
            subirNivel();
        }
    }

    void subirNivel() {
        nivel++;
        experienciaActual -= experienciaParaNivel;
        // Ejemplo: cada nivel requiere 50% más experiencia
        experienciaParaNivel = static_cast<int>(experienciaParaNivel * 1.5);
        poderCombate = static_cast<int>(poderCombate * 1.2); // +20% de poder por nivel

        cout << nombre << " sube al nivel " << nivel << "!" << endl;
    }

    void aplicarItem(const Item& item) {
        cout << nombre << " usa el item: " << item.getNombre() << endl;

        switch (item.getTipo()) {
            case TipoItem::BOOST_EXPERIENCIA:
                ganarExperiencia(item.getValor());
                break;
            case TipoItem::BOOST_PODER:
                setPoderCombate(poderCombate + item.getValor());
                cout << "Poder de combate aumentado en " << item.getValor() << endl;
                break;
            case TipoItem::CURACION:
                // Aquí podrías tener vida máxima y actual, pero no está en el diseño
                cout << "Curación de " << item.getValor() << " (no implementada completamente)" << endl;
                break;
        }
    }

    void recibirDanio(int danio) {
        // Nota: no hay atributo de vida en la clase actual
        cout << nombre << " recibe " << danio << " de daño." << endl;
        // Podrías añadir lógica de vida aquí si se expande la clase
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

// Las clases Tropas, Ejercito y Jugador están incompletas en las fotos
// Si quieres que continúe con ellas (Tropa, Ejercito, Jugador) dime
// qué implementación prefieres para las listas (vector, lista enlazada, array dinámico...)
// y te ayudo a completarlas.

int main() {
    // Ejemplo de uso rápido
    Soldado s1("Legionario", true, 1, 15);
    Item pocion("Poción de Fuerza", TipoItem::BOOST_PODER, 8);

    s1.mostrarInfo();
    s1.aplicarItem(pocion);
    s1.ganarExperiencia(70);
    s1.mostrarInfo();

    return 0;
}