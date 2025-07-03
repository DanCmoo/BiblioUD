#ifndef BST_H
#define BST_H

#include <cstddef>
#include <stdexcept>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class BST {
private:
    struct Nodo {
        T dato;
        Nodo* izq;
        Nodo* der;
        Nodo(const T& d) : dato(d), izq(nullptr), der(nullptr) {}
    };

    Nodo* raiz;
    size_t cantidad;
    Compare comp;

    void insertar(Nodo*& nodo, const T& valor) {
        if (!nodo) {
            nodo = new Nodo(valor);
            cantidad++;
        } else if (comp(valor, nodo->dato)) {
            insertar(nodo->izq, valor);
        } else if (comp(nodo->dato, valor)) {
            insertar(nodo->der, valor);
        } // Si es igual, no se inserta
    }

    bool buscar(Nodo* nodo, const T& valor) const {
        if (!nodo) return false;
        if (comp(valor, nodo->dato)) return buscar(nodo->izq, valor);
        if (comp(nodo->dato, valor)) return buscar(nodo->der, valor);
        return true;
    }

    void inorden(Nodo* nodo, std::function<void(const T&)> f) const {
        if (!nodo) return;
        inorden(nodo->izq, f);
        f(nodo->dato);
        inorden(nodo->der, f);
    }

    void limpiar(Nodo* nodo) {
        if (!nodo) return;
        limpiar(nodo->izq);
        limpiar(nodo->der);
        delete nodo;
    }

public:
    BST() : raiz(nullptr), cantidad(0), comp(Compare()) {}

    ~BST() {
        limpiar(raiz);
    }

    void insertar(const T& valor) {
        insertar(raiz, valor);
    }

    bool existe(const T& valor) const {
        return buscar(raiz, valor);
    }

    size_t tamano() const { return cantidad; }
    bool vacio() const { return cantidad == 0; }

    void recorrerInorden(std::function<void(const T&)> f) const {
        inorden(raiz, f);
    }

    void limpiar() {
        limpiar(raiz);
        raiz = nullptr;
        cantidad = 0;
    }
};

#endif