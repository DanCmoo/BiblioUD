#ifndef OBRA_H
#define OBRA_H

#include <string>
#include "Edicion.h"
#include "Lista.h"  // Lista<T>

class Obra {
private:
    std::string nombreObra;
    std::string tipoPoesia;
    std::string idAutor;
    Lista<Edicion> ediciones; // Estructura genérica

public:
    Obra() : nombreObra(""), tipoPoesia(""), idAutor("") {}

    Obra(const std::string& nombre, const std::string& tipo, const std::string& id)
        : nombreObra(nombre), tipoPoesia(tipo), idAutor(id) {}

    const std::string& getNombre() const { return nombreObra; }
    const std::string& getTipoPoesia() const { return tipoPoesia; }
    const std::string& getIdAutor() const { return idAutor; }

    void agregarEdicion(const Edicion& e) {
        ediciones.agregar(e); // Metodo de tu Lista<T>
    }

    const Lista<Edicion>& getEdiciones() const {
        return ediciones;
    }

    void mostrar() const;
};

#endif