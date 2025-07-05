#ifndef OBRA_H
#define OBRA_H

#include <string>
#include <sstream>
#include "Edicion.h"
#include "../datastructures/Lista.h"  // Lista<T>

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

    //Setters
    void setNombre(const std::string& nombre) { nombreObra = nombre; }
    void setTipoPoesia(const std::string& tipo) { tipoPoesia = tipo; }
    void setIdAutor(const std::string& id) { idAutor = id; }

    void mostrar();

    // SERIALIZACION: solo serializa los datos base y los números de edición separados por ';'
    std::string serialize() const {
        std::ostringstream oss;
        oss << nombreObra << "|" << tipoPoesia << "|" << idAutor << "|";
        bool primero = true;
        for (auto it = ediciones.begin(); it != ediciones.end(); ++it) {
            if (!primero) oss << ";";
            oss << (*it).getNumeroEdicion();
            primero = false;
        }
        return oss.str();
    }

    // DESERIALIZACION: solo recupera los datos base y los números de edición (los datos completos de cada Edicion se cargan aparte)
    void deserialize(const std::string& linea) {
        std::istringstream iss(linea);
        std::string campo, edicionesStr;
        std::getline(iss, nombreObra, '|');
        std::getline(iss, tipoPoesia, '|');
        std::getline(iss, idAutor, '|');
        std::getline(iss, edicionesStr, '|');

        // Limpiar la lista antes de poblarla
        ediciones.limpiar();
        if (!edicionesStr.empty()) {
            std::istringstream eds(edicionesStr);
            while (std::getline(eds, campo, ';')) {
                int numEdicion = std::stoi(campo);
                Edicion ed;
                ed.setNumeroEdicion(numEdicion);
                ediciones.agregar(ed);
            }
        }
    }
};

#endif