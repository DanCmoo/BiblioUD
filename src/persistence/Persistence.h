#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>
#include <fstream>
#include <stdexcept>
#include "../datastructures/Lista.h"

template <typename T>
class Persistence {
private:
    std::string filename;

public:
    Persistence(const std::string& fname) : filename(fname) {}

    // Guarda todos los elementos de la lista en el archivo (sobrescribe el archivo)
    void saveAll(const Lista<T>& elementos) {
        std::ofstream file(filename.c_str());
        if (!file.is_open())
            throw std::runtime_error("No se pudo abrir el archivo para escritura: " + filename);

        for (auto it = elementos.begin(); it != elementos.end(); ++it) {
            file << (*it).serialize() << "\n";
        }
        file.close();
    }

    // Lee todos los elementos del archivo y los devuelve en una Lista
    Lista<T> loadAll() {
        Lista<T> elementos;
        std::ifstream file(filename.c_str());
        if (!file.is_open())
            throw std::runtime_error("No se pudo abrir el archivo para lectura: " + filename);

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) break; // Detiene la lectura si encuentra una línea vacía
            try {
                T obj;
                obj.deserialize(line);
                elementos.agregar(obj);
            } catch (const std::exception& ex) {
                // Si quieres, puedes loggear el error aquí
                continue;
            }
        }
        file.close();
        return elementos;
    }
};

#endif