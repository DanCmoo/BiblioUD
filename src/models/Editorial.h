#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <string>
#include <sstream>

class Editorial {
private:
    int idEditorial;
    std::string nombre;
    std::string ciudad;
    std::string pais;

public:
    static int numEDitorial;
    Editorial()
        :  nombre(""), ciudad(""), pais("") {}

    Editorial(const std::string& nom, const std::string& ciu, const std::string& pa)
        : idEditorial(++numEDitorial), nombre(nom), ciudad(ciu), pais(pa) {}

    const int& getIdEditorial() const { return idEditorial; }
    const std::string& getNombre() const { return nombre; }
    void setNombre(const std::string& n){ nombre=  n; }
    const std::string& getCiudad() const { return ciudad; }
    void setCiudad(const std::string& c){ ciudad=  c; }
    const std::string& getPais() const { return pais; }
    void setPais(const std::string& p){ pais=  p; }

    void mostrar();

    // SERIALIZACION
    std::string serialize() const {
        return std::to_string(idEditorial) + "|" + nombre + "|" + ciudad + "|" + pais;
    }

    // DESERIALIZACION
    void deserialize(const std::string& linea) {
        std::istringstream iss(linea);
        std::string idEditorialStr;
        std::getline(iss, idEditorialStr, '|'); idEditorial = std::stoi(idEditorialStr);
        std::getline(iss, nombre, '|');
        std::getline(iss, ciudad, '|');
        std::getline(iss, pais, '|');
    }
};

#endif