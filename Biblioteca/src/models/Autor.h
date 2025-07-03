#ifndef AUTOR_H
#define AUTOR_H

#include <string>

class Autor {
private:
    int idAutor;
    std::string nombre;
    std::string apellido;
    bool sexo; // true: Hombre, false: Mujer
    std::string fechaNacimiento;
    std::string ciudadNacimiento;
    std::string paisNacimiento;
    std::string ciudadResidencia;
    std::string formacionBase;
    int anioInicioLiteratura;
    int anioPrimeraObra;

public:
    Autor()
        : idAutor(0), nombre(""), apellido(""), sexo(true), fechaNacimiento(""),
          ciudadNacimiento(""), paisNacimiento(""), ciudadResidencia(""),
          formacionBase(""), anioInicioLiteratura(0), anioPrimeraObra(0) {}
    Autor(int id, const std::string& nom, const std::string& ape, bool sx, const std::string& fNac,
          const std::string& cNac, const std::string& pNac, const std::string& cRes,
          const std::string& form, int anioInicio, int anioPrimera);

    int getIdAutor() const { return idAutor; }
    const std::string& getNombre() const { return nombre; }
    const std::string& getApellido() const { return apellido; }
    bool getSexo() const { return sexo; }
    const std::string& getFechaNacimiento() const { return fechaNacimiento; }
    const std::string& getCiudadNacimiento() const { return ciudadNacimiento; }
    const std::string& getPaisNacimiento() const { return paisNacimiento; }
    const std::string& getCiudadResidencia() const { return ciudadResidencia; }
    const std::string& getFormacionBase() const { return formacionBase; }
    int getAnioInicio() const { return anioInicioLiteratura; }
    int getAnioPrimeraObra() const { return anioPrimeraObra; }

    void setNombre(const std::string& n) { nombre = n; }
    void setApellido(const std::string& a) { apellido = a; }
    void setSexo(bool s) { sexo = s; }
    void setFechaNacimiento(const std::string& f) { fechaNacimiento = f; }
    void setCiudadNacimiento(const std::string& c) { ciudadNacimiento = c; }
    void setPaisNacimiento(const std::string& p) { paisNacimiento = p; }
    void setCiudadResidencia(const std::string& c) { ciudadResidencia = c; }
    void setFormacionBase(const std::string& f) { formacionBase = f; }
    void setAnioInicio(int a) { anioInicioLiteratura = a; }
    void setAnioPrimeraObra(int a) { anioPrimeraObra = a; }

    void mostrar() const;
};

#endif