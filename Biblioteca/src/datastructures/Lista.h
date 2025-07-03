#ifndef LISTA_H
#define LISTA_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class Lista {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    Nodo* cola;
    size_t cantidad;

public:
    Lista() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

    ~Lista() {
        limpiar();
    }

    void agregar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);
        if (!cabeza) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        cantidad++;
    }

    T& obtener(size_t indice) {
        if (indice >= cantidad) throw std::out_of_range("Índice fuera de rango");
        Nodo* actual = cabeza;
        for (size_t i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }

    const T& obtener(size_t indice) const {
        if (indice >= cantidad) throw std::out_of_range("Índice fuera de rango");
        Nodo* actual = cabeza;
        for (size_t i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }

    size_t tamano() const {
        return cantidad;
    }

    bool vacia() const {
        return cantidad == 0;
    }

    void limpiar() {
        Nodo* actual = cabeza;
        while (actual) {
            Nodo* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
        cabeza = cola = nullptr;
        cantidad = 0;
    }

    // Iterador simple
    class iterator {
        Nodo* nodo;
    public:
        iterator(Nodo* n) : nodo(n) {}
        iterator& operator++() { nodo = nodo->siguiente; return *this; }
        bool operator!=(const iterator& other) const { return nodo != other.nodo; }
        T& operator*() { return nodo->dato; }
    };

    iterator begin() { return iterator(cabeza); }
    iterator end() { return iterator(nullptr); }
};

#endif