#ifndef AVL_H
#define AVL_H

#include <cstddef>
#include <functional>
#include <stdexcept>

template <typename T, typename Compare = std::less<T>>
class AVL {
private:
    struct Nodo {
        T dato;
        Nodo* izq;
        Nodo* der;
        int altura;
        Nodo(const T& d) : dato(d), izq(nullptr), der(nullptr), altura(1) {}
    };

    Nodo* raiz;
    size_t cantidad;
    Compare comp;

    int altura(Nodo* n) const { return n ? n->altura : 0; }

    int balance(Nodo* n) const { return n ? altura(n->izq) - altura(n->der) : 0; }

    void actualizarAltura(Nodo* n) {
        if (n)
            n->altura = 1 + std::max(altura(n->izq), altura(n->der));
    }

    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izq;
        Nodo* T2 = x->der;
        x->der = y;
        y->izq = T2;
        actualizarAltura(y);
        actualizarAltura(x);
        return x;
    }

    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->der;
        Nodo* T2 = y->izq;
        y->izq = x;
        x->der = T2;
        actualizarAltura(x);
        actualizarAltura(y);
        return y;
    }

    Nodo* insertar(Nodo* nodo, const T& valor) {
        if (!nodo) {
            cantidad++;
            return new Nodo(valor);
        }
        if (comp(valor, nodo->dato))
            nodo->izq = insertar(nodo->izq, valor);
        else if (comp(nodo->dato, valor))
            nodo->der = insertar(nodo->der, valor);
        else
            return nodo; // No permite duplicados

        actualizarAltura(nodo);

        int bal = balance(nodo);

        // Rotaciones
        if (bal > 1 && comp(valor, nodo->izq->dato))
            return rotarDerecha(nodo); // Left Left

        if (bal < -1 && comp(nodo->der->dato, valor))
            return rotarIzquierda(nodo); // Right Right

        if (bal > 1 && comp(nodo->izq->dato, valor)) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo); // Left Right
        }

        if (bal < -1 && comp(valor, nodo->der->dato)) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo); // Right Left
        }

        return nodo;
    }

    T* buscar(Nodo* nodo, const T& valor) {
        if (!nodo) return nullptr;
        if (comp(valor, nodo->dato)) return buscar(nodo->izq, valor);
        if (comp(nodo->dato, valor)) return buscar(nodo->der, valor);
        return &(nodo->dato);
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
    AVL() : raiz(nullptr), cantidad(0), comp(Compare()) {}

    ~AVL() { limpiar(raiz); }

    void insertar(const T& valor) {
        raiz = insertar(raiz, valor);
    }

    T* buscar(const T& valor) {
        return buscar(raiz, valor);
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