#ifndef EDICION_H
#define EDICION_H

#include <string>
#include <sstream>

class Edicion {
private:
    int numeroEdicion;
    std::string fechaPublicacion;
    std::string idEditorial;
    std::string ciudadPublicacion;

public:
    Edicion()
        : numeroEdicion(0), fechaPublicacion(""),
          idEditorial(""), ciudadPublicacion("") {}

    Edicion(int num, const std::string& fecha, const std::string& idEdit, const std::string& ciudad)
        : numeroEdicion(num), fechaPublicacion(fecha),
          idEditorial(idEdit), ciudadPublicacion(ciudad) {}

    int getNumeroEdicion() const { return numeroEdicion; }
    const std::string& getFechaPublicacion() const { return fechaPublicacion; }
    const std::string& getIdEditorial() const { return idEditorial; }
    const std::string& getCiudadPublicacion() const { return ciudadPublicacion; }

    void setNumeroEdicion(int num) { numeroEdicion = num; }
    void setFechaPublicacion(const std::string& fecha) { fechaPublicacion = fecha; }
    void setIdEditorial(const std::string& idEdit) { idEditorial = idEdit; }
    void setCiudadPublicacion(const std::string& ciudad) { ciudadPublicacion = ciudad; }

    void mostrar();

    // SERIALIZACION
    std::string serialize() const {
        return std::to_string(numeroEdicion) + "|" +
               fechaPublicacion + "|" +
               idEditorial + "|" +
               ciudadPublicacion;
    }

    // DESERIALIZACION
    void deserialize(const std::string& linea) {
        std::istringstream iss(linea);
        std::string campo;
        std::getline(iss, campo, '|'); numeroEdicion = std::stoi(campo);
        std::getline(iss, fechaPublicacion, '|');
        std::getline(iss, idEditorial, '|');
        std::getline(iss, ciudadPublicacion, '|');
    }
};

#endif