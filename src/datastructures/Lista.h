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
    // Constructor por defecto
    Lista() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

    // Constructor de copia
    Lista(const Lista<T>& otra) : cabeza(nullptr), cola(nullptr), cantidad(0) {
        Nodo* actual = otra.cabeza;
        while (actual) {
            agregar(actual->dato);
            actual = actual->siguiente;
        }
    }

    // Operador de asignación
    Lista<T>& operator=(const Lista<T>& otra) {
        if (this != &otra) {
            limpiar();
            Nodo* actual = otra.cabeza;
            while (actual) {
                agregar(actual->dato);
                actual = actual->siguiente;
            }
        }
        return *this;
    }

    // Destructor
    ~Lista() {
        limpiar();
    }

    // Agregar elemento al final
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

    // Obtener por índice (lectura/escritura)
    T& obtener(size_t indice) {
        if (indice >= cantidad) throw std::out_of_range("Índice fuera de rango");
        Nodo* actual = cabeza;
        for (size_t i = 0; i < indice; ++i)
            actual = actual->siguiente;
        return actual->dato;
    }

    // Obtener por índice (solo lectura)
    const T& obtener(size_t indice) const {
        if (indice >= cantidad) throw std::out_of_range("Índice fuera de rango");
        Nodo* actual = cabeza;
        for (size_t i = 0; i < indice; ++i)
            actual = actual->siguiente;
        return actual->dato;
    }

    // Tamaño de la lista
    size_t tamano() const {
        return cantidad;
    }

    // Verificar si está vacía
    bool vacia() const {
        return cantidad == 0;
    }

    // Limpiar la lista
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

        iterator& operator++() {
            if (nodo) nodo = nodo->siguiente;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return nodo != other.nodo;
        }

        T& operator*() {
            return nodo->dato;
        }

        T* operator->() {
            return &nodo->dato;
        }

        friend class Lista<T>; // Permite a Lista acceder a `nodo`
    };

    iterator begin() const { return iterator(cabeza); }
    iterator end() const { return iterator(nullptr); }

    //
    void eliminar(iterator it) {
        if (it.nodo == nullptr || cabeza == nullptr)
            return;

        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;

        while (actual && actual != it.nodo) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (!actual) return; // No encontrado

        if (anterior == nullptr) {
            // Eliminar cabeza
            cabeza = cabeza->siguiente;
            if (cabeza == nullptr) cola = nullptr;
        } else {
            anterior->siguiente = actual->siguiente;
            if (actual == cola) cola = anterior;
        }

        delete actual;
        cantidad--;
    }

};

#endif
