#ifndef EDICION_H
#define EDICION_H

#include <string>

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

    // Setters opcionales
    void setNumeroEdicion(int num) { numeroEdicion = num; }
    void setFechaPublicacion(const std::string& fecha) { fechaPublicacion = fecha; }
    void setIdEditorial(const std::string& idEdit) { idEditorial = idEdit; }
    void setCiudadPublicacion(const std::string& ciudad) { ciudadPublicacion = ciudad; }

    void mostrar() const;
};

#endif