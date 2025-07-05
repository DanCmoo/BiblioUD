#ifndef EDICION_H
#define EDICION_H

#include <string>
#include <sstream>
using namespace std;
class Edicion {
private:
    int numeroEdicion;
    string fechaPublicacion;
    string idEditorial;
    string ciudadPublicacion;

public:
    Edicion()
        : numeroEdicion(0), fechaPublicacion(""),
          idEditorial(""), ciudadPublicacion("") {}

    Edicion(int num, const string& fecha, const string& idEdit, const string& ciudad)
        : numeroEdicion(num), fechaPublicacion(fecha),
          idEditorial(idEdit), ciudadPublicacion(ciudad) {}

    int getNumeroEdicion() const { return numeroEdicion; }
    const string& getFechaPublicacion() const { return fechaPublicacion; }
    const string& getIdEditorial() const { return idEditorial; }
    const string& getCiudadPublicacion() const { return ciudadPublicacion; }

    void setNumeroEdicion(int num) { numeroEdicion = num; }
    void setFechaPublicacion(const string& fecha) { fechaPublicacion = fecha; }
    void setIdEditorial(const string& idEdit) { idEditorial = idEdit; }
    void setCiudadPublicacion(const string& ciudad) { ciudadPublicacion = ciudad; }

    void mostrar() const;

    // SERIALIZACION
    string serialize() const {
        return to_string(numeroEdicion) + "|" +
               fechaPublicacion + "|" +
               idEditorial + "|" +
               ciudadPublicacion;
    }

    // DESERIALIZACION
    void deserialize(const string& linea) {
        istringstream iss(linea);
        string campo;
        getline(iss, campo, '|'); numeroEdicion = stoi(campo);
        getline(iss, fechaPublicacion, '|');
        getline(iss, idEditorial, '|');
        getline(iss, ciudadPublicacion, '|');
    }
};

#endif