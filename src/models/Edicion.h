#ifndef EDICION_H
#define EDICION_H

#include <string>
#include <sstream>

class Edicion {
private:
    int numeroEdicion;
    std::string fechaPublicacion;
    int idEditorial;
    std::string ciudadPublicacion;
    std::string nombreObra;
    int idAutor;

public:
    static int numEdicion;
    Edicion()
        : numeroEdicion(0), fechaPublicacion(""),
          idEditorial(0), ciudadPublicacion("") {}

    Edicion(const std::string& fecha, const int& idEdit, const std::string& ciudad,const std::string&nombreObra,const int&idAutor)
        : numeroEdicion(++numEdicion), fechaPublicacion(fecha),
          idEditorial(idEdit), ciudadPublicacion(ciudad),nombreObra(nombreObra),idAutor(idAutor) {}

    int getNumeroEdicion() const { return numeroEdicion; }
    const std::string& getFechaPublicacion() const { return fechaPublicacion; }
    const int& getIdEditorial() const { return idEditorial; }
    const std::string& getCiudadPublicacion() const { return ciudadPublicacion; }
    const std::string& getNombreObra() const { return nombreObra; }
    const int getIdAutor() const { return idAutor; }
    void setNumeroEdicion(int num) { numeroEdicion = num; }
    void setFechaPublicacion(const std::string& fecha) { fechaPublicacion = fecha; }
    void setIdEditorial(const int& idEdit) { idEditorial = idEdit; }
    void setCiudadPublicacion(const std::string& ciudad) { ciudadPublicacion = ciudad; }

    void mostrar() const;

    // SERIALIZACION
    std::string serialize() const {
        return std::to_string(numeroEdicion) + "|" +
               fechaPublicacion + "|" +
               std::to_string(idEditorial) + "|" +
               ciudadPublicacion + "|" +
               nombreObra + "|" +
               std::to_string(idAutor);
    }

    // DESERIALIZACION
    void deserialize(const std::string& linea) {
        std::istringstream iss(linea);
        std::string campo;
        std::getline(iss, campo, '|'); numeroEdicion = std::stoi(campo);
        std::getline(iss, fechaPublicacion, '|');
        std::getline(iss, campo, '|'); idEditorial = std::stoi(campo);
        std::getline(iss, ciudadPublicacion, '|');
        std::getline(iss, nombreObra, '|');
        std::getline(iss, campo, '|'); idAutor = std::stoi(campo);
    }
};

#endif