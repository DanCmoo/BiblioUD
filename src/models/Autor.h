#ifndef AUTOR_H
#define AUTOR_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Autor {
private:
    string idAutor;
    string nombre;
    string apellido;
    char sexo; // 'M' (masculino), 'F' (femenino), 'X' (desconocido)
    string fechaNacimiento;
    string ciudadNacimiento;
    string paisNacimiento;
    string ciudadResidencia;
    string formacionBase;
    int anioInicioLiteratura;
    int anioPrimeraObra;

public:
    Autor()
        : idAutor(""), nombre(""), apellido(""), sexo('X'), fechaNacimiento(""),
          ciudadNacimiento(""), paisNacimiento(""), ciudadResidencia(""),
          formacionBase(""), anioInicioLiteratura(0), anioPrimeraObra(0) {}

    Autor(const string& id, const string& nom, const string& ape, char sx,
          const string& fNac, const string& cNac, const string& pNac,
          const string& cRes, const string& form, int anioInicio, int anioPrimera)
        : idAutor(id), nombre(nom), apellido(ape), sexo(toupper(sx)),
          fechaNacimiento(fNac), ciudadNacimiento(cNac), paisNacimiento(pNac),
          ciudadResidencia(cRes), formacionBase(form),
          anioInicioLiteratura(anioInicio), anioPrimeraObra(anioPrimera) {}

    // Getters
    const string& getIdAutor() const { return idAutor; }
    const string& getNombre() const { return nombre; }
    const string& getApellido() const { return apellido; }
    char getSexo() const { return sexo; }
    const string& getFechaNacimiento() const { return fechaNacimiento; }
    const string& getCiudadNacimiento() const { return ciudadNacimiento; }
    const string& getPaisNacimiento() const { return paisNacimiento; }
    const string& getCiudadResidencia() const { return ciudadResidencia; }
    const string& getFormacionBase() const { return formacionBase; }
    int getAnioInicio() const { return anioInicioLiteratura; }
    int getAnioPrimeraObra() const { return anioPrimeraObra; }

    // Setters
    void setIdAutor(const string& id) { idAutor = id; }
    void setNombre(const string& n) { nombre = n; }
    void setApellido(const string& a) { apellido = a; }
    void setSexo(char s) { sexo = toupper(s); }
    void setFechaNacimiento(const string& f) { fechaNacimiento = f; }
    void setCiudadNacimiento(const string& c) { ciudadNacimiento = c; }
    void setPaisNacimiento(const string& p) { paisNacimiento = p; }
    void setCiudadResidencia(const string& c) { ciudadResidencia = c; }
    void setFormacionBase(const string& f) { formacionBase = f; }
    void setAnioInicio(int a) { anioInicioLiteratura = a; }
    void setAnioPrimeraObra(int a) { anioPrimeraObra = a; }

    // Serialización
    string serialize() const {
        return idAutor + "|" +
               nombre + "|" +
               apellido + "|" +
               string(1, sexo) + "|" +
               fechaNacimiento + "|" +
               ciudadNacimiento + "|" +
               paisNacimiento + "|" +
               ciudadResidencia + "|" +
               formacionBase + "|" +
               to_string(anioInicioLiteratura) + "|" +
               to_string(anioPrimeraObra);
    }

    // Deserialización
    void deserialize(const string& linea) {
        istringstream iss(linea);
        string campo;
        getline(iss, idAutor, '|');
        getline(iss, nombre, '|');
        getline(iss, apellido, '|');
        getline(iss, campo, '|'); sexo = campo.empty() ? 'X' : toupper(campo[0]);
        getline(iss, fechaNacimiento, '|');
        getline(iss, ciudadNacimiento, '|');
        getline(iss, paisNacimiento, '|');
        getline(iss, ciudadResidencia, '|');
        getline(iss, formacionBase, '|');
        getline(iss, campo, '|'); anioInicioLiteratura = stoi(campo);
        getline(iss, campo, '|'); anioPrimeraObra = stoi(campo);
    }

    void mostrar();
};

#endif
