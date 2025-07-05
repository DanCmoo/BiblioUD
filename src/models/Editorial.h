#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <string>
#include <sstream>

class Editorial {
private:
    std::string idEditorial;
    std::string nombre;
    std::string ciudad;
    std::string pais;

public:
    Editorial()
        : idEditorial(""), nombre(""), ciudad(""), pais("") {}

    Editorial(const std::string& id, const std::string& nom, const std::string& ciu, const std::string& pa)
        : idEditorial(id), nombre(nom), ciudad(ciu), pais(pa) {}

    //getters
    const std::string& getIdEditorial() const { return idEditorial; }
    const std::string& getNombre() const { return nombre; }
    const std::string& getCiudad() const { return ciudad; }
    const std::string& getPais() const { return pais; }

    //Setters
    void setIdEditorial(const std::string& id) { idEditorial = id; }
    void setNombre(const std::string& nom) { nombre = nom; }
    void setCiudad(const std::string& ciu) { ciudad = ciu; }
    void setPais(const std::string& pa) { pais = pa; }

    void mostrar();

    // SERIALIZACION
    std::string serialize() const {
        return idEditorial + "|" + nombre + "|" + ciudad + "|" + pais;
    }

    // DESERIALIZACION
    void deserialize(const std::string& linea) {
        std::istringstream iss(linea);
        std::getline(iss, idEditorial, '|');
        std::getline(iss, nombre, '|');
        std::getline(iss, ciudad, '|');
        std::getline(iss, pais, '|');
    }
};

#endif