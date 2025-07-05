#include <iostream>
#include <string>
#include <ctime>
#include "datastructures/AVL.h"
#include "models/Autor.h"
#include "models/Obra.h"
#include "models/Edicion.h"
#include "models/Editorial.h"
#include "datastructures/Lista.h"
#include "persistence/Persistence.h"
// --- Comparadores ---

struct ComparadorAutorPorIdAutor {
    bool operator()(const Autor& a, const Autor& b) const {
        return a.getIdAutor() < b.getIdAutor();
    }
};

struct ComparadorObra {
    bool operator()(const Obra& a, const Obra& b) const {
        if (a.getIdAutor() != b.getIdAutor())
            return a.getIdAutor() < b.getIdAutor();
        if (a.getTipoPoesia() != b.getTipoPoesia())
            return a.getTipoPoesia() < b.getTipoPoesia();
        return a.getNombre() < b.getNombre();
    }
};

// --- Estructuras globales ---

AVL<Autor, ComparadorAutorPorIdAutor> arbolAutores;
AVL<Obra, ComparadorObra> arbolObras;
Lista<Edicion> listaEdiciones;
Lista<Editorial> listaEditoriales;

// --- Prototipos de carga/guarda ---
void cargarAutores(AVL<Autor, ComparadorAutorPorIdAutor>&);
void guardarAutores(const AVL<Autor, ComparadorAutorPorIdAutor>&);
void cargarObras(AVL<Obra, ComparadorObra>&);
void guardarObras(const AVL<Obra, ComparadorObra>&);
void cargarEdiciones(Lista<Edicion>&);
void guardarEdiciones(const Lista<Edicion>&);
void cargarEditoriales(Lista<Editorial>&);
void guardarEditoriales(const Lista<Editorial>&);

// --- Prototipos de submenus y CRUD ---
void menuAutores();
void menuObras();
void menuEdiciones();
void menuEditoriales();

// Prototipos CRUD autores
void insertarAutor();
void buscarAutor();
void modificarAutor();
void eliminarAutor();

// Prototipos CRUD obras
void insertarObra();
void buscarObra();
void modificarObra();
void eliminarObra();

// Prototipos CRUD ediciones
void insertarEdicion();
void buscarEdicion();
void modificarEdicion();
void eliminarEdicion();

// Prototipos CRUD editoriales
void insertarEditorial();
void buscarEditorial();
void modificarEditorial();
void eliminarEditorial();

// --- Prototipos de consultas ---
void consulta1();
void consulta2();
void consulta3();
void consulta4();
void consulta5();
void consulta6();
void consulta7();

void menuPrincipal();
void menuConsultas();

// --- Funciones auxiliares para consultas ---

// Busca una edición por su número en la lista global
const Edicion* buscarEdicionPorNumero(int numero, const Lista<Edicion>& listaEdiciones) {
    for (auto it = listaEdiciones.begin(); it != listaEdiciones.end(); ++it) {
        if (it->getNumeroEdicion() == numero)
            return &(*it);
    }
    return nullptr;
}

// Busca la editorial por su ID en la lista global
const Editorial* buscarEditorialPorId(const std::string& id, const Lista<Editorial>& listaEditoriales) {
    for (auto it = listaEditoriales.begin(); it != listaEditoriales.end(); ++it) {
        if (it->getIdEditorial() == id)
            return &(*it);
    }
    return nullptr;
}

// --- Implementación de menú principal y submenús ---

int main() {
    cargarAutores(arbolAutores);
    cargarObras(arbolObras);
    cargarEdiciones(listaEdiciones);
    cargarEditoriales(listaEditoriales);

    menuPrincipal();

    guardarAutores(arbolAutores);
    guardarObras(arbolObras);
    guardarEdiciones(listaEdiciones);
    guardarEditoriales(listaEditoriales);

    std::cout << "Datos guardados. Saliendo del sistema..." << std::endl;
    return 0;
}

void menuPrincipal() {
    int opcion;
    do {
        std::cout << "\n==== BIBLIOUD ====\n";
        std::cout << "1. Gestionar autores\n";
        std::cout << "2. Gestionar obras\n";
        std::cout << "3. Gestionar ediciones\n";
        std::cout << "4. Gestionar editoriales\n";
        std::cout << "5. Consultas\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 1: menuAutores(); break;
            case 2: menuObras(); break;
            case 3: menuEdiciones(); break;
            case 4: menuEditoriales(); break;
            case 5: menuConsultas(); break;
            case 0: std::cout << "Saliendo...\n"; break;
            default: std::cout << "Opción invalida.\n";
        }
    } while(opcion != 0);
}

void menuConsultas() {
    int opcion;
    do {
        std::cout << "\n==== Consultas ====\n";
        std::cout << "1. Numero total de obras de un autor por editorial y anio\n";
        std::cout << "2. Listado de obras de un autor por tipo de poesia\n";
        std::cout << "3. Autores publicados por una editorial, clasificados por ciudad y anio de inicio\n";
        std::cout << "4. Editoriales con mas de N poetas publicados\n";
        std::cout << "5. Hombres y mujeres publicados por cada editorial, clasificados por ciudad y pais de nacimiento\n";
        std::cout << "6. Autores en rango de edad y formacion, por anio de primera obra\n";
        std::cout << "7. Autores y ediciones por tipo de poesia y editorial\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion de consulta: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 1: consulta1(); break;
            case 2: consulta2(); break;
            case 3: consulta3(); break;
            case 4: consulta4(); break;
            case 5: consulta5(); break;
            case 6: consulta6(); break;
            case 7: consulta7(); break;
            case 0: break;
            default: std::cout << "Opcion invalida.\n";
        }
    } while(opcion != 0);
}

// --- Submenús de gestión CRUD ---

void menuAutores() {
    int op;
    do {
        std::cout << "\n--- Gestion de Autores ---\n";
        std::cout << "1. Insertar autor\n";
        std::cout << "2. Buscar autor\n";
        std::cout << "3. Modificar autor\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> op;
        std::cin.ignore();
        switch(op) {
            case 1: insertarAutor(); break;
            case 2: buscarAutor(); break;
            case 3: modificarAutor(); break;
            case 0: break;
            default: std::cout << "Opcion invalida.\n";
        }
    } while(op != 0);
}

void menuObras() {
    int op;
    do {
        std::cout << "\n--- Gestion de Obras ---\n";
        std::cout << "1. Insertar obra\n";
        std::cout << "2. Buscar obra\n";
        std::cout << "3. Modificar obra\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> op;
        std::cin.ignore();
        switch(op) {
            case 1: insertarObra(); break;
            case 2: buscarObra(); break;
            case 3: modificarObra(); break;
            case 0: break;
            default: std::cout << "Opcion invalida.\n";
        }
    } while(op != 0);
}

void menuEdiciones() {
    int op;
    do {
        std::cout << "\n--- Gestion de Ediciones ---\n";
        std::cout << "1. Insertar edicion\n";
        std::cout << "2. Buscar edicion\n";
        std::cout << "3. Modificar edicion\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> op;
        std::cin.ignore();
        switch(op) {
            case 1: insertarEdicion(); break;
            case 2: buscarEdicion(); break;
            case 3: modificarEdicion(); break;
            case 0: break;
            default: std::cout << "Opcion invalida.\n";
        }
    } while(op != 0);
}

void menuEditoriales() {
    int op;
    do {
        std::cout << "\n--- Gestion de Editoriales ---\n";
        std::cout << "1. Insertar editorial\n";
        std::cout << "2. Buscar editorial\n";
        std::cout << "3. Modificar editorial\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> op;
        std::cin.ignore();
        switch(op) {
            case 1: insertarEditorial(); break;
            case 2: buscarEditorial(); break;
            case 3: modificarEditorial(); break;
            case 0: break;
            default: std::cout << "Opcion invalida.\n";
        }
    } while(op != 0);
}

// -------------- CRUD Autores --------------

void insertarAutor() {
    std::cout << "\n--- Insertar Autor ---\n";
    std::string nombre, apellido, fechaNac, ciudadNac, paisNac, ciudadRes, formacion;
    bool sexo;
    int anioInicio, anioPrimera;
    std::cout << "Nombre: "; std::getline(std::cin, nombre);
    std::cout << "Apellido: "; std::getline(std::cin, apellido);
    std::cout << "Fecha de nacimiento (YYYY-MM-DD): "; std::getline(std::cin, fechaNac);
    std::cout << "Ciudad de nacimiento: "; std::getline(std::cin, ciudadNac);
    std::cout << "Pais de nacimiento: "; std::getline(std::cin, paisNac);
    std::cout << "Ciudad de residencia: "; std::getline(std::cin, ciudadRes);
    std::cout << "Formacion de base: "; std::getline(std::cin, formacion);
    std::cout << "Sexo (1=Hombre, 0=Mujer): "; std::cin >> sexo; std::cin.ignore();
    std::cout << "Anio de inicio en la literatura: "; std::cin >> anioInicio; std::cin.ignore();
    std::cout << "Anio de lanzamiento primera obra: "; std::cin >> anioPrimera; std::cin.ignore();
    Autor nuevo(nombre, apellido, sexo, fechaNac, ciudadNac, paisNac, ciudadRes, formacion, anioInicio, anioPrimera);
    arbolAutores.insertar(nuevo);
    std::cout << "Autor insertado correctamente.\n";

}

void buscarAutor() {
    std::cout << "\n--- Buscar Autor ---\n";
    int id;
    std::cout << "ID: "; std::cin >> id; std::cin.ignore();
    Autor buscado(id);
    Autor* res = arbolAutores.buscar(buscado);
    if (res) {
        std::cout << "Nombre: " << res->getNombre() << "\n";
        std::cout << "Apellido: " << res->getApellido() << "\n";
        std::cout << "Fecha de nacimiento: " << res->getFechaNacimiento() << "\n";
        std::cout << "Ciudad de nacimiento: " << res->getCiudadNacimiento() << "\n";
        std::cout << "País de nacimiento: " << res->getPaisNacimiento() << "\n";
        std::cout << "Ciudad de residencia: " << res->getCiudadResidencia() << "\n";
        std::cout << "Formación de base: " << res->getFormacionBase() << "\n";
        std::cout << "Sexo: " << (res->getSexo() ? "Hombre" : "Mujer") << "\n";
        std::cout << "Anio inicio literatura: " << res->getAnioInicio() << "\n";
        std::cout << "Anio primera obra: " << res->getAnioPrimeraObra() << "\n";

    } else {
        std::cout << "No existe autor con ese ID.\n";
    }
}

void modificarAutor() {
    std::cout << "\n--- Modificar Autor ---\n";
    int id;
    std::cout << "ID: "; std::cin >> id; std::cin.ignore();
    Autor buscado(id);
    Autor* res = arbolAutores.buscar(buscado);
    if (!res) {
        std::cout << "No existe autor con ese ID.\n";
        return;
    }
    std::string nombre, apellido, fechaNac, ciudadNac, paisNac, ciudadRes, formacion;
    bool sexo;
    int anioInicio, anioPrimera;
    std::cout << "Nuevo nombre (" << res->getNombre() << "): "; std::getline(std::cin, nombre);
    std::cout << "Nuevo apellido (" << res->getApellido() << "): "; std::getline(std::cin, apellido);
    std::cout << "Nueva fecha de nacimiento (" << res->getFechaNacimiento() << "): "; std::getline(std::cin, fechaNac);
    std::cout << "Nueva ciudad de nacimiento (" << res->getCiudadNacimiento() << "): "; std::getline(std::cin, ciudadNac);
    std::cout << "Nuevo país de nacimiento (" << res->getPaisNacimiento() << "): "; std::getline(std::cin, paisNac);
    std::cout << "Nueva ciudad de residencia (" << res->getCiudadResidencia() << "): "; std::getline(std::cin, ciudadRes);
    std::cout << "Nueva formación de base (" << res->getFormacionBase() << "): "; std::getline(std::cin, formacion);
    std::cout << "Nuevo sexo (1=Hombre, 0=Mujer) (" << (res->getSexo() ? "Hombre" : "Mujer") << "): "; std::cin >> sexo; std::cin.ignore();
    std::cout << "Nuevo anio de inicio en la literatura (" << res->getAnioInicio() << "): "; std::cin >> anioInicio; std::cin.ignore();
    std::cout << "Nuevo anio de primera obra (" << res->getAnioPrimeraObra() << "): "; std::cin >> anioPrimera; std::cin.ignore();

    res->setNombre(nombre);
    res->setApellido(apellido);
    res->setFechaNacimiento(fechaNac);
    res->setCiudadNacimiento(ciudadNac);
    res->setPaisNacimiento(paisNac);
    res->setCiudadResidencia(ciudadRes);
    res->setFormacionBase(formacion);
    res->setSexo(sexo);
    res->setAnioInicio(anioInicio);
    res->setAnioPrimeraObra(anioPrimera);

    std::cout << "Autor modificado correctamente.\n";
}


// --- CRUD de Obras ---

void insertarObra() {
    std::cout << "\n--- Insertar Obra ---\n";
    int idAutor;
    std::string nombre, tipoPoesia;
    std::cout << "ID del Autor: "; std::cin >> idAutor; std::cin.ignore();
    std::cout << "Nombre de la obra: "; std::getline(std::cin, nombre);
    std::cout << "Tipo de poesia: "; std::getline(std::cin, tipoPoesia);
    Obra nueva(nombre, tipoPoesia, idAutor);
    arbolObras.insertar(nueva);
    std::cout << "Obra insertada correctamente.\n";

}

void buscarObra() {
    std::cout << "\n--- Buscar Obra ---\n";
    int idAutor;
    std::string nombre, tipoPoesia;
    std::cout << "ID del Autor: "; std::cin >> idAutor; std::cin.ignore();
    std::cout << "Nombre de la obra: "; std::getline(std::cin, nombre);
    std::cout << "Tipo de poesia: "; std::getline(std::cin, tipoPoesia);
    Obra buscada(nombre, tipoPoesia, idAutor);
    Obra* res = arbolObras.buscar(buscada);
    if (res) {
        std::cout << "Obra encontrada. ID Autor: " << res->getIdAutor()
                  << ", Nombre: " << res->getNombre()
                  << ", Tipo de poesia: " << res->getTipoPoesia() << "\n";
    } else {
        std::cout << "No existe esa obra.\n";
    }
}

void modificarObra() {
    std::cout << "\n--- Modificar Obra ---\n";
    int idAutor;
    std::string nombre, tipoPoesia;
    std::cout << "ID del Autor: "; std::cin >> idAutor; std::cin.ignore();
    std::cout << "Nombre de la obra: "; std::getline(std::cin, nombre);
    std::cout << "Tipo de poesia: "; std::getline(std::cin, tipoPoesia);
    Obra buscada(nombre, tipoPoesia, idAutor);
    Obra* res = arbolObras.buscar(buscada);
    if (!res) {
        std::cout << "No existe esa obra.\n";
        return;
    }
    std::string nuevoNombre, nuevoTipoPoesia;
    std::cout << "Nuevo nombre de la obra (" << res->getNombre() << "): "; std::getline(std::cin, nuevoNombre);
    std::cout << "Nuevo tipo de poesia (" << res->getTipoPoesia() << "): "; std::getline(std::cin, nuevoTipoPoesia);
    res->setNombre(nuevoNombre);
    res->setTipoPoesia(nuevoTipoPoesia);
    std::cout << "Obra modificada correctamente.\n";
}



// --- CRUD de Ediciones ---

void insertarEdicion() {
    std::cout << "\n--- Insertar Ediciin ---\n";
    std::string idEditorial, fechaPublicacion, ciudadPublicacion;
    std::cout << "ID de la editorial: "; std::getline(std::cin, idEditorial);
    std::cout << "Fecha de publicacion (YYYY-MM-DD): "; std::getline(std::cin, fechaPublicacion);
    std::cout << "Ciudad de publicacion: "; std::getline(std::cin, ciudadPublicacion);
    Edicion nueva(fechaPublicacion, idEditorial, ciudadPublicacion);
    listaEdiciones.agregar(nueva);
    std::cout << "Edicion insertada correctamente.\n";
}

void buscarEdicion() {
    std::cout << "\n--- Buscar Edición ---\n";
    int numeroEdicion;
    std::cout << "Número de edición: "; std::cin >> numeroEdicion; std::cin.ignore();
    const Edicion* ed = buscarEdicionPorNumero(numeroEdicion, listaEdiciones);
    if (ed) {
        std::cout << "Edición encontrada. Número: " << ed->getNumeroEdicion()
                  << ", Editorial: " << ed->getIdEditorial()
                  << ", Fecha: " << ed->getFechaPublicacion() << "\n";
    } else {
        std::cout << "No existe esa edición.\n";
    }
}

void modificarEdicion() {
    std::cout << "\n--- Modificar Edición ---\n";
    int numeroEdicion;
    std::cout << "Número de edición: "; std::cin >> numeroEdicion; std::cin.ignore();
    for (auto it = listaEdiciones.begin(); it != listaEdiciones.end(); ++it) {
        if (it->getNumeroEdicion() == numeroEdicion) {
            std::string idEditorial, fechaPublicacion;
            std::cout << "Nuevo ID de editorial (" << it->getIdEditorial() << "): "; std::getline(std::cin, idEditorial);
            std::cout << "Nueva fecha de publicación (" << it->getFechaPublicacion() << "): "; std::getline(std::cin, fechaPublicacion);
            it->setIdEditorial(idEditorial);
            it->setFechaPublicacion(fechaPublicacion);
            std::cout << "Edición modificada correctamente.\n";
            return;
        }
    }
    std::cout << "No existe esa edición.\n";
}

void eliminarEdicion() {
    std::cout << "\n--- Eliminar Edición ---\n";
    int numeroEdicion;
    std::cout << "Número de edición: "; std::cin >> numeroEdicion; std::cin.ignore();
    for (auto it = listaEdiciones.begin(); it != listaEdiciones.end(); ++it) {
        if (it->getNumeroEdicion() == numeroEdicion) {
            listaEdiciones.eliminar(it);
            std::cout << "Edición eliminada correctamente.\n";
            return;
        }
    }
    std::cout << "No existe esa edición.\n";
}

// --- CRUD de Editoriales ---

void insertarEditorial() {
    std::cout << "\n--- Insertar Editorial ---\n";
    std::string idEditorial, nombre, ciudad, pais;
    std::cout << "ID de la editorial: "; std::getline(std::cin, idEditorial);
    std::cout << "Nombre: "; std::getline(std::cin, nombre);
    std::cout << "Ciudad: "; std::getline(std::cin, ciudad);
    std::cout << "País: "; std::getline(std::cin, pais);
    Editorial nueva(idEditorial, nombre, ciudad, pais);
    listaEditoriales.agregar(nueva);
    std::cout << "Editorial insertada correctamente.\n";
}

void buscarEditorial() {
    std::cout << "\n--- Buscar Editorial ---\n";
    std::string idEditorial;
    std::cout << "ID de la editorial: "; std::getline(std::cin, idEditorial);
    for (auto it = listaEditoriales.begin(); it != listaEditoriales.end(); ++it) {
        if (it->getIdEditorial() == idEditorial) {
            std::cout << "Nombre: " << it->getNombre()
                      << ", Ciudad: " << it->getCiudad()
                      << ", País: " << it->getPais() << "\n";
            return;
        }
    }
    std::cout << "No existe esa editorial.\n";
}

void modificarEditorial() {
    std::cout << "\n--- Modificar Editorial ---\n";
    std::string idEditorial;
    std::cout << "ID de la editorial: "; std::getline(std::cin, idEditorial);
    for (auto it = listaEditoriales.begin(); it != listaEditoriales.end(); ++it) {
        if (it->getIdEditorial() == idEditorial) {
            std::string nombre, ciudad, pais;
            std::cout << "Nuevo nombre (" << it->getNombre() << "): "; std::getline(std::cin, nombre);
            std::cout << "Nueva ciudad (" << it->getCiudad() << "): "; std::getline(std::cin, ciudad);
            std::cout << "Nuevo país (" << it->getPais() << "): "; std::getline(std::cin, pais);
            it->setNombre(nombre);
            it->setCiudad(ciudad);
            it->setPais(pais);
            std::cout << "Editorial modificada correctamente.\n";
            return;
        }
    }
    std::cout << "No existe esa editorial.\n";
}

void eliminarEditorial() {
    std::cout << "\n--- Eliminar Editorial ---\n";
    std::string idEditorial;
    std::cout << "ID de la editorial: "; std::getline(std::cin, idEditorial);
    for (auto it = listaEditoriales.begin(); it != listaEditoriales.end(); ++it) {
        if (it->getIdEditorial() == idEditorial) {
            listaEditoriales.eliminar(it);
            std::cout << "Editorial eliminada correctamente.\n";
            return;
        }
    }
    std::cout << "No existe esa editorial.\n";
}

// ------ Consultas ------

void consulta1() {
    std::cout << "[Consulta 1] Número total de obras de un autor por editorial y año de publicación\n";
    int idAutor;
    std::cout << "Ingrese el ID del autor: ";
    std::cin >> idAutor;
    std::cin.ignore();

    struct ConteoEditorialAnio {
        std::string nombreEditorial;
        int anio;
        int cantidad;
    };
    Lista<ConteoEditorialAnio> conteos;

    arbolObras.recorrerInorden([&](const Obra& obra) {
        if (obra.getIdAutor() == idAutor) {
            for (auto idEdIt = obra.getIdEdiciones().begin(); idEdIt != obra.getIdEdiciones().end(); ++idEdIt) {
                int idEdicion = *idEdIt;
                const Edicion* ed = buscarEdicionPorNumero(idEdicion, listaEdiciones);
                if (ed) {
                    std::string idEditorial = ed->getIdEditorial();
                    const Editorial* editorial = buscarEditorialPorId(idEditorial, listaEditoriales);
                    std::string nombreEditorial = editorial ? editorial->getNombre() : "Desconocida";
                    std::string fecha = ed->getFechaPublicacion();
                    int anio = 0;
                    if (fecha.size() >= 4) anio = std::stoi(fecha.substr(0, 4));

                    bool encontrado = false;
                    for (auto it = conteos.begin(); it != conteos.end(); ++it) {
                        if (it->nombreEditorial == nombreEditorial && it->anio == anio) {
                            it->cantidad++;
                            encontrado = true;
                            break;
                        }
                    }
                    if (!encontrado) {
                        ConteoEditorialAnio nuevo;
                        nuevo.nombreEditorial = nombreEditorial;
                        nuevo.anio = anio;
                        nuevo.cantidad = 1;
                        conteos.agregar(nuevo);
                    }
                }
            }
        }
    });

    std::cout << "\nObras del autor clasificadas por editorial y año de publicación:\n";
    for (auto it = conteos.begin(); it != conteos.end(); ++it) {
        std::cout << "Editorial: " << it->nombreEditorial
                  << " | Año: " << it->anio
                  << " | Obras: " << it->cantidad << "\n";
    }
}

void consulta2() {
    std::cout << "[Consulta 2] Listado de obras de un autor por tipo de poesía\n";
    int idAutor;
    std::cout << "Ingrese el ID del autor: ";
    std::cin >> idAutor;
    std::cin.ignore();

    struct InfoObraEdicion {
        std::string nombreObra;
        int numeroEdicion;
        std::string fechaPublicacion;
    };

    struct GrupoTipoPoesia {
        std::string tipoPoesia;
        Lista<InfoObraEdicion> obras;
    };

    Lista<GrupoTipoPoesia> grupos;

    arbolObras.recorrerInorden([&](const Obra& obra) {
        if (obra.getIdAutor() == idAutor) {
            std::string tipo = obra.getTipoPoesia();
            GrupoTipoPoesia* grupo = nullptr;
            for (auto it = grupos.begin(); it != grupos.end(); ++it) {
                if (it->tipoPoesia == tipo) {
                    grupo = &(*it);
                    break;
                }
            }
            if (!grupo) {
                GrupoTipoPoesia nuevoGrupo;
                nuevoGrupo.tipoPoesia = tipo;
                grupos.agregar(nuevoGrupo);
                for (auto it = grupos.begin(); it != grupos.end(); ++it) {
                    if (it->tipoPoesia == tipo) {
                        grupo = &(*it);
                        break;
                    }
                }
            }
            for (auto idEdIt = obra.getIdEdiciones().begin(); idEdIt != obra.getIdEdiciones().end(); ++idEdIt) {
                int idEdicion = *idEdIt;
                const Edicion* ed = buscarEdicionPorNumero(idEdicion, listaEdiciones);
                if (ed) {
                    InfoObraEdicion info;
                    info.nombreObra = obra.getNombre();
                    info.numeroEdicion = ed->getNumeroEdicion();
                    info.fechaPublicacion = ed->getFechaPublicacion();
                    grupo->obras.agregar(info);
                }
            }
        }
    });

    std::cout << "\nObras del autor clasificadas por tipo de poesía:\n";
    for (auto itGrupo = grupos.begin(); itGrupo != grupos.end(); ++itGrupo) {
        std::cout << "\nTipo de poesía: " << itGrupo->tipoPoesia << "\n";
        for (auto itObra = itGrupo->obras.begin(); itObra != itGrupo->obras.end(); ++itObra) {
            std::cout << "  Obra: " << itObra->nombreObra
                      << ", Edición: " << itObra->numeroEdicion
                      << ", Fecha de publicación: " << itObra->fechaPublicacion
                      << std::endl;
        }
    }
}

void consulta3() {
    std::cout << "[Consulta 3] Autores publicados por una editorial, clasificados por ciudad de residencia y año de inicio\n";
    std::string idEditorial;
    std::cout << "Ingrese el ID de la editorial: ";
    std::getline(std::cin, idEditorial);

    struct InfoAutor {
        std::string nombre;
        std::string apellido;
        std::string ciudadNacimiento;
        std::string ciudadResidencia;
        int anioInicioLiteratura;
    };

    struct GrupoCiudadAnio {
        std::string ciudadResidencia;
        int anioInicio;
        Lista<InfoAutor> autores;
    };

    Lista<GrupoCiudadAnio> grupos;
    Lista<int> idsAutoresUnicos;

    arbolObras.recorrerInorden([&](const Obra& obra) {
        for (auto idEdIt = obra.getIdEdiciones().begin(); idEdIt != obra.getIdEdiciones().end(); ++idEdIt) {
            int idEdicion = *idEdIt;
            const Edicion* ed = buscarEdicionPorNumero(idEdicion, listaEdiciones);
            if (ed && ed->getIdEditorial() == idEditorial) {
                bool yaAgregado = false;
                for (auto it = idsAutoresUnicos.begin(); it != idsAutoresUnicos.end(); ++it) {
                    if (*it == obra.getIdAutor()) {
                        yaAgregado = true;
                        break;
                    }
                }
                if (!yaAgregado) {
                    idsAutoresUnicos.agregar(obra.getIdAutor());
                }
                break;
            }
        }
    });

    for (auto itAutorId = idsAutoresUnicos.begin(); itAutorId != idsAutoresUnicos.end(); ++itAutorId) {
        Autor buscado(*itAutorId);
        Autor* autorPtr = arbolAutores.buscar(buscado);
        if (!autorPtr) continue;

        InfoAutor info;
        info.nombre = autorPtr->getNombre();
        info.apellido = autorPtr->getApellido();
        info.ciudadNacimiento = autorPtr->getCiudadNacimiento();
        info.ciudadResidencia = autorPtr->getCiudadResidencia();
        info.anioInicioLiteratura = autorPtr->getAnioInicio();

        GrupoCiudadAnio* grupo = nullptr;
        for (auto it = grupos.begin(); it != grupos.end(); ++it) {
            if (it->ciudadResidencia == info.ciudadResidencia && it->anioInicio == info.anioInicioLiteratura) {
                grupo = &(*it);
                break;
            }
        }
        if (!grupo) {
            GrupoCiudadAnio nuevoGrupo;
            nuevoGrupo.ciudadResidencia = info.ciudadResidencia;
            nuevoGrupo.anioInicio = info.anioInicioLiteratura;
            grupos.agregar(nuevoGrupo);
            for (auto it = grupos.begin(); it != grupos.end(); ++it) {
                if (it->ciudadResidencia == info.ciudadResidencia && it->anioInicio == info.anioInicioLiteratura) {
                    grupo = &(*it);
                    break;
                }
            }
        }
        grupo->autores.agregar(info);
    }

    std::cout << "\nAutores publicados por la editorial '" << idEditorial << "', clasificados por ciudad de residencia y año de inicio:\n";
    for (auto itGrupo = grupos.begin(); itGrupo != grupos.end(); ++itGrupo) {
        std::cout << "\nCiudad de residencia: " << itGrupo->ciudadResidencia << ", Año de inicio: " << itGrupo->anioInicio << "\n";
        for (auto itAutor = itGrupo->autores.begin(); itAutor != itGrupo->autores.end(); ++itAutor) {
            std::cout << "  Nombre: " << itAutor->nombre
                      << ", Apellido: " << itAutor->apellido
                      << ", Ciudad de nacimiento: " << itAutor->ciudadNacimiento << "\n";
        }
    }
}

void consulta4() {
    std::cout << "[Consulta 4] Editoriales con más de N poetas publicados\n";
    int n;
    std::cout << "Ingrese el número mínimo de poetas publicados: ";
    std::cin >> n;
    std::cin.ignore();

    struct InfoEditorial {
        std::string idEditorial;
        std::string nombre;
        std::string ciudad;
        std::string pais;
        int cantidadPoetas;
    };

    Lista<InfoEditorial> resultado;

    for (auto itEd = listaEditoriales.begin(); itEd != listaEditoriales.end(); ++itEd) {
        std::string idEditorial = itEd->getIdEditorial();
        Lista<int> idsPoetas;

        arbolObras.recorrerInorden([&](const Obra& obra) {
            bool publicadoPorEstaEditorial = false;
            for (auto idEdIt = obra.getIdEdiciones().begin(); idEdIt != obra.getIdEdiciones().end(); ++idEdIt) {
                int idEdicion = *idEdIt;
                const Edicion* ed = buscarEdicionPorNumero(idEdicion, listaEdiciones);
                if (ed && ed->getIdEditorial() == idEditorial) {
                    publicadoPorEstaEditorial = true;
                    break;
                }
            }
            if (publicadoPorEstaEditorial) {
                bool yaAgregado = false;
                for (auto itId = idsPoetas.begin(); itId != idsPoetas.end(); ++itId) {
                    if (*itId == obra.getIdAutor()) {
                        yaAgregado = true;
                        break;
                    }
                }
                if (!yaAgregado) {
                    idsPoetas.agregar(obra.getIdAutor());
                }
            }
        });

        if (idsPoetas.tamano() > n) {
            InfoEditorial info;
            info.idEditorial = idEditorial;
            info.nombre = itEd->getNombre();
            info.ciudad = itEd->getCiudad();
            info.pais = itEd->getPais();
            info.cantidadPoetas = (int)idsPoetas.tamano();
            resultado.agregar(info);
        }
    }

    if (resultado.vacia()) {
        std::cout << "No hay editoriales con más de " << n << " poetas publicados.\n";
    } else {
        std::cout << "\nEditoriales con más de " << n << " poetas publicados:\n";
        for (auto it = resultado.begin(); it != resultado.end(); ++it) {
            std::cout << "Editorial: " << it->nombre
                      << " | Ciudad: " << it->ciudad
                      << " | País: " << it->pais
                      << " | Cantidad de poetas: " << it->cantidadPoetas << "\n";
        }
    }
}

void consulta5() {
    std::cout << "[Consulta 5] Hombres y mujeres publicados por cada editorial, clasificados por ciudad y país de nacimiento\n";

    struct ConteoGeneroLugar {
        std::string ciudadNacimiento;
        std::string paisNacimiento;
        int hombres;
        int mujeres;
    };

    struct InfoEditorial {
        std::string nombreEditorial;
        Lista<ConteoGeneroLugar> conteos;
    };

    for (auto itEd = listaEditoriales.begin(); itEd != listaEditoriales.end(); ++itEd) {
        std::string idEditorial = itEd->getIdEditorial();
        std::string nombreEditorial = itEd->getNombre();

        Lista<int> idsAutoresUnicos;

        arbolObras.recorrerInorden([&](const Obra& obra) {
            bool publicadoPorEstaEditorial = false;
            for (auto idEdIt = obra.getIdEdiciones().begin(); idEdIt != obra.getIdEdiciones().end(); ++idEdIt) {
                int idEdicion = *idEdIt;
                const Edicion* ed = buscarEdicionPorNumero(idEdicion, listaEdiciones);
                if (ed && ed->getIdEditorial() == idEditorial) {
                    publicadoPorEstaEditorial = true;
                    break;
                }
            }
            if (publicadoPorEstaEditorial) {
                bool yaAgregado = false;
                for (auto it = idsAutoresUnicos.begin(); it != idsAutoresUnicos.end(); ++it) {
                    if (*it == obra.getIdAutor()) {
                        yaAgregado = true;
                        break;
                    }
                }
                if (!yaAgregado) {
                    idsAutoresUnicos.agregar(obra.getIdAutor());
                }
            }
        });

        InfoEditorial infoEdit;
        infoEdit.nombreEditorial = nombreEditorial;

        for (auto itAutorId = idsAutoresUnicos.begin(); itAutorId != idsAutoresUnicos.end(); ++itAutorId) {
            Autor buscado(*itAutorId);
            Autor* autorPtr = arbolAutores.buscar(buscado);
            if (!autorPtr) continue;

            std::string ciudadNac = autorPtr->getCiudadNacimiento();
            std::string paisNac = autorPtr->getPaisNacimiento();
            bool sexo = autorPtr->getSexo();

            ConteoGeneroLugar* grupo = nullptr;
            for (auto it = infoEdit.conteos.begin(); it != infoEdit.conteos.end(); ++it) {
                if (it->ciudadNacimiento == ciudadNac && it->paisNacimiento == paisNac) {
                    grupo = &(*it);
                    break;
                }
            }
            if (!grupo) {
                ConteoGeneroLugar nuevoGrupo;
                nuevoGrupo.ciudadNacimiento = ciudadNac;
                nuevoGrupo.paisNacimiento = paisNac;
                nuevoGrupo.hombres = 0;
                nuevoGrupo.mujeres = 0;
                infoEdit.conteos.agregar(nuevoGrupo);
                for (auto it = infoEdit.conteos.begin(); it != infoEdit.conteos.end(); ++it) {
                    if (it->ciudadNacimiento == ciudadNac && it->paisNacimiento == paisNac) {
                        grupo = &(*it);
                        break;
                    }
                }
            }
            if (sexo)
                grupo->hombres++;
            else
                grupo->mujeres++;
        }

        std::cout << "\nEditorial: " << infoEdit.nombreEditorial << "\n";
        for (auto it = infoEdit.conteos.begin(); it != infoEdit.conteos.end(); ++it) {
            std::cout << "  Ciudad de nacimiento: " << it->ciudadNacimiento
                      << ", País de nacimiento: " << it->paisNacimiento
                      << " | Hombres: " << it->hombres
                      << " | Mujeres: " << it->mujeres << "\n";
        }
    }
}

void consulta6() {
    std::cout << "[Consulta 6] Autores en rango de edad y formación, por año de primera obra\n";
    int edadMin, edadMax;
    std::string formacionBase;
    std::cout << "Ingrese la edad mínima: ";
    std::cin >> edadMin;
    std::cout << "Ingrese la edad máxima: ";
    std::cin >> edadMax;
    std::cin.ignore();
    std::cout << "Ingrese la formación de base: ";
    std::getline(std::cin, formacionBase);

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int anioActual = now->tm_year + 1900;

    struct InfoAutor {
        std::string nombre;
        std::string apellido;
        int anioPrimeraObra;
    };

    struct GrupoAnio {
        int anioPrimeraObra;
        Lista<InfoAutor> autores;
    };

    Lista<GrupoAnio> grupos;

    arbolAutores.recorrerInorden([&](const Autor& autor) {
        int edad = anioActual - autor.getAnioNacimiento();
        if (edad >= edadMin && edad <= edadMax && autor.getFormacionBase() == formacionBase) {
            int anioPrimeraObra = -1;
            arbolObras.recorrerInorden([&](const Obra& obra) {
                if (obra.getIdAutor() == autor.getIdAutor()) {
                    for (auto idEdIt = obra.getIdEdiciones().begin(); idEdIt != obra.getIdEdiciones().end(); ++idEdIt) {
                        const Edicion* ed = buscarEdicionPorNumero(*idEdIt, listaEdiciones);
                        if (ed) {
                            std::string fecha = ed->getFechaPublicacion();
                            if (fecha.size() >= 4) {
                                int anio = std::stoi(fecha.substr(0,4));
                                if (anioPrimeraObra == -1 || anio < anioPrimeraObra) {
                                    anioPrimeraObra = anio;
                                }
                            }
                        }
                    }
                }
            });

            if (anioPrimeraObra != -1) {
                GrupoAnio* grupo = nullptr;
                for (auto it = grupos.begin(); it != grupos.end(); ++it) {
                    if (it->anioPrimeraObra == anioPrimeraObra) {
                        grupo = &(*it);
                        break;
                    }
                }
                if (!grupo) {
                    GrupoAnio nuevo;
                    nuevo.anioPrimeraObra = anioPrimeraObra;
                    grupos.agregar(nuevo);
                    for (auto it = grupos.begin(); it != grupos.end(); ++it) {
                        if (it->anioPrimeraObra == anioPrimeraObra) {
                            grupo = &(*it);
                            break;
                        }
                    }
                }
                InfoAutor info;
                info.nombre = autor.getNombre();
                info.apellido = autor.getApellido();
                info.anioPrimeraObra = anioPrimeraObra;
                grupo->autores.agregar(info);
            }
        }
    });

    std::cout << "\nAutores en el rango de edad y formación seleccionados, clasificados por año de publicación de su primera obra:\n";
    for (auto itGrupo = grupos.begin(); itGrupo != grupos.end(); ++itGrupo) {
        std::cout << "\nAño de primera obra: " << itGrupo->anioPrimeraObra << "\n";
        for (auto itAutor = itGrupo->autores.begin(); itAutor != itGrupo->autores.end(); ++itAutor) {
            std::cout << "  Nombre: " << itAutor->nombre
                      << ", Apellido: " << itAutor->apellido
                      << "\n";
        }
    }
}

void consulta7() {
    std::cout << "[Consulta 7] Autores y ediciones por tipo de poesía y editorial\n";
    std::string tipoPoesia, idEditorial;
    std::cout << "Ingrese el tipo de poesía: ";
    std::getline(std::cin, tipoPoesia);
    std::cout << "Ingrese el ID de la editorial: ";
    std::getline(std::cin, idEditorial);

    struct InfoEdicion {
        int numeroEdicion;
        std::string fechaPublicacion;
        std::string tituloObra;
    };
    struct InfoAutor {
        int idAutor;
        std::string nombreAutor;
        std::string apellidoAutor;
        Lista<InfoEdicion> ediciones;
    };
    Lista<InfoAutor> autores;

    arbolObras.recorrerInorden([&](const Obra& obra) {
        if (obra.getTipoPoesia() == tipoPoesia) {
            Lista<InfoEdicion> edicionesMatch;
            for (auto idEdIt = obra.getIdEdiciones().begin(); idEdIt != obra.getIdEdiciones().end(); ++idEdIt) {
                int idEdicion = *idEdIt;
                const Edicion* ed = buscarEdicionPorNumero(idEdicion, listaEdiciones);
                if (ed && ed->getIdEditorial() == idEditorial) {
                    InfoEdicion infoEd;
                    infoEd.numeroEdicion = ed->getNumeroEdicion();
                    infoEd.fechaPublicacion = ed->getFechaPublicacion();
                    infoEd.tituloObra = obra.getNombre();
                    edicionesMatch.agregar(infoEd);
                }
            }
            if (!edicionesMatch.vacia()) {
                Autor buscado(obra.getIdAutor());
                Autor* autorPtr = arbolAutores.buscar(buscado);
                if (!autorPtr) return;
                InfoAutor* autorInfo = nullptr;
                for (auto it = autores.begin(); it != autores.end(); ++it) {
                    if (it->idAutor == obra.getIdAutor()) {
                        autorInfo = &(*it);
                        break;
                    }
                }
                if (!autorInfo) {
                    InfoAutor nuevo;
                    nuevo.idAutor = obra.getIdAutor();
                    nuevo.nombreAutor = autorPtr->getNombre();
                    nuevo.apellidoAutor = autorPtr->getApellido();
                    autores.agregar(nuevo);
                    for (auto it = autores.begin(); it != autores.end(); ++it) {
                        if (it->idAutor == obra.getIdAutor()) {
                            autorInfo = &(*it);
                            break;
                        }
                    }
                }
                for (auto itEd = edicionesMatch.begin(); itEd != edicionesMatch.end(); ++itEd) {
                    autorInfo->ediciones.agregar(*itEd);
                }
            }
        }
    });

    std::cout << "\nAutores y ediciones para tipo de poesía '" << tipoPoesia << "' y editorial '" << idEditorial << "':\n";
    for (auto itAutor = autores.begin(); itAutor != autores.end(); ++itAutor) {
        std::cout << "\nAutor: " << itAutor->nombreAutor << " " << itAutor->apellidoAutor << "\n";
        for (auto itEd = itAutor->ediciones.begin(); itEd != itAutor->ediciones.end(); ++itEd) {
            std::cout << "  Obra: " << itEd->tituloObra
                      << ", Edición: " << itEd->numeroEdicion
                      << ", Fecha de publicación: " << itEd->fechaPublicacion << "\n";
        }
    }
}

// ------- Carga y guarda de datos (prototipos) -------

void cargarAutores(AVL<Autor, ComparadorAutorPorIdAutor>& arbolAutores) {
    Persistence<Autor> persist("../src/data/autores.txt");
    Lista<Autor> lista = persist.loadAll();
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        arbolAutores.insertar(*it);
    }
}

void guardarAutores(const AVL<Autor, ComparadorAutorPorIdAutor>& arbolAutores) {
    Persistence<Autor> persist("../src/data/autores.txt");
    Lista<Autor> lista;
    arbolAutores.recorrerInorden([&](const Autor& autor) {
        lista.agregar(autor);
    });
    persist.saveAll(lista);
}

// --- Obra ---
void cargarObras(AVL<Obra, ComparadorObra>& arbolObras) {
    Persistence<Obra> persist("../src/data/obras.txt");
    Lista<Obra> lista = persist.loadAll();
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        arbolObras.insertar(*it);
    }
}

void guardarObras(const AVL<Obra, ComparadorObra>& arbolObras) {
    Persistence<Obra> persist("../src/data/obras.txt");
    Lista<Obra> lista;
    arbolObras.recorrerInorden([&](const Obra& obra) {
        lista.agregar(obra);
    });
    persist.saveAll(lista);
}

// --- Edicion ---
void cargarEdiciones(Lista<Edicion>& listaEdiciones) {
    Persistence<Edicion> persist("../src/data/ediciones.txt");
    listaEdiciones = persist.loadAll();
}

void guardarEdiciones(const Lista<Edicion>& listaEdiciones) {
    Persistence<Edicion> persist("../src/data/ediciones.txt");
    persist.saveAll(listaEdiciones);
}

// --- Editorial ---
void cargarEditoriales(Lista<Editorial>& listaEditoriales) {
    Persistence<Editorial> persist("../src/data/editoriales.txt");
    listaEditoriales = persist.loadAll();
}

void guardarEditoriales(const Lista<Editorial>& listaEditoriales) {
    Persistence<Editorial> persist("../src/data/editoriales.txt");
    persist.saveAll(listaEditoriales);
}