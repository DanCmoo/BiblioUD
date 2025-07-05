#ifndef OBRA_H
#define OBRA_H

#include <string>
#include <sstream>
#include "../datastructures/Lista.h"  // Lista<T>

class Obra {
private:
    std::string nombreObra;
    std::string tipoPoesia;
    int idAutor;
    Lista<int> idEdiciones; // Ahora solo almacena los IDs de las ediciones

public:
    Obra() : nombreObra(""), tipoPoesia(""), idAutor(0) {}

    Obra(const std::string& nombre, const std::string& tipo, const int& id)
        : nombreObra(nombre), tipoPoesia(tipo), idAutor(id) {}

    const std::string& getNombre() const { return nombreObra; }
    void setNombre(const std::string& n){nombreObra = n; }
    const std::string& getTipoPoesia() const { return tipoPoesia; }
    void setTipoPoesia(const std::string& p){tipoPoesia = p; }
    const int& getIdAutor() const { return idAutor; }

    void agregarIdEdicion(int idEdicion) {
        idEdiciones.agregar(idEdicion);
    }

    const Lista<int>& getIdEdiciones() const {
        return idEdiciones;
    }

    void mostrar();

    // SERIALIZACION: solo serializa los datos base y los IDs de ediciones separados por ';'
    std::string serialize() const {
        std::ostringstream oss;
        oss << nombreObra << "|" << tipoPoesia << "|" << idAutor << "|";
        bool primero = true;
        for (auto it = idEdiciones.begin(); it != idEdiciones.end(); ++it) {
            if (!primero) oss << ";";
            oss << *it;
            primero = false;
        }
        return oss.str();
    }

    // DESERIALIZACION: solo recupera los datos base y los IDs de ediciones
    void deserialize(const std::string& linea) {
        std::istringstream iss(linea);
        std::string campo, idEdicionesStr;
        std::getline(iss, nombreObra, '|');
        std::getline(iss, tipoPoesia, '|');
        std::getline(iss, campo, '|'); idAutor = std::stoi(campo);
        std::getline(iss, idEdicionesStr, '|');

        // Limpiar la lista antes de poblarla
        idEdiciones.limpiar();
        if (!idEdicionesStr.empty()) {
            std::istringstream eds(idEdicionesStr);
            while (std::getline(eds, campo, ';')) {
                int idEdicion = std::stoi(campo);
                idEdiciones.agregar(idEdicion);
            }
        }
    }
};

#endif