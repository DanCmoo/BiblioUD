#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm> // Para std::sort
#include <limits>

#include "datastructures/Lista.h"
#include "datastructures/BST.h"

#include "models/Autor.h"
#include "models/Edicion.h"
#include "models/Editorial.h"
#include "models/Obra.h"
using namespace std;


Lista<Autor> listaAutores;
Lista<Editorial> listaEditoriales;
Lista<Obra> listaObras;

bool autoresCargados = false;
bool editorialesCargadas = false;
bool obrasCargadas = false;

// Elimina espacios en blanco al inicio y al final de una cadena
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";

    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Retorna el nombre de una editorial dado su ID, o "(Editorial desconocida)" si no existe
string obtenerNombreEditorial(const string& idEditorial) {
    for (auto it = listaEditoriales.begin(); it != listaEditoriales.end(); ++it) {
        if (it->getIdEditorial() == idEditorial) {
            return it->getNombre();
        }
    }
    return "(Editorial desconocida)";
}

// Carga los autores desde el archivo 'autores.txt' y los agrega a la lista global
void cargarAutores() {
    ifstream archivo("autores.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo 'autores.txt'.\n";
        return;
    }
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, apellido, sexoStr, fechaNac, ciudadNac, paisNac, ciudadRes, formacion;
        int anioInicio, anioPrimera;
        getline(ss, id, '|');
        getline(ss, nombre, '|');
        getline(ss, apellido, '|');
        getline(ss, sexoStr, '|');
        char sexo = (sexoStr.empty() ? 'X' : sexoStr[0]); // X como valor desconocido
        getline(ss, fechaNac, '|');
        getline(ss, ciudadNac, '|');
        getline(ss, paisNac, '|');
        getline(ss, ciudadRes, '|');
        getline(ss, formacion, '|');

        ss >> anioInicio;
        ss.ignore();
        ss >> anioPrimera;

        Autor a(id, nombre, apellido, sexo, fechaNac, ciudadNac, paisNac, ciudadRes, formacion, anioInicio, anioPrimera);
        listaAutores.agregar(a);

    }

    archivo.close();
    cout << "Autores cargados correctamente.\n";
}

void mostrarAutores() {
    if (listaAutores.vacia()) {
        cout << "No hay autores cargados.\n";
        return;
    }
    for (auto it = listaAutores.begin(); it != listaAutores.end(); ++it)
        it->mostrar();

}

// Guarda todos los autores en el archivo 'autores.txt' sobrescribiendo el contenido anterior
void guardarAutores() {
    if (listaAutores.vacia()) {
        cout << "No hay autores para guardar.\n";
        return;
    }

    ofstream archivo("autores.txt");
    if (!archivo) {
        cerr << "[ERROR] No se pudo abrir el archivo 'autores.txt' para escritura.\n";
        return;
    }

    for (const Autor& a : listaAutores) {
        archivo << a.getIdAutor() << "|"
        << a.getNombre() << "|"
        << a.getApellido() << "|"
        << a.getSexo() << "|"
        << a.getFechaNacimiento() << "|"
        << a.getCiudadNacimiento() << "|"
        << a.getPaisNacimiento() << "|"
        << a.getCiudadResidencia() << "|"
        << a.getFormacionBase() << "|"
        << a.getAnioInicio() << "|"
        << a.getAnioPrimeraObra() << "\n";

    }
    archivo.flush();
    archivo.close();
    cout << "Autores guardados correctamente (" << listaAutores.tamano() << " autores).\n";
}

// Agrega un nuevo autor a la lista si no existe otro con el mismo ID
void agregarAutor() {
    string id, nombre, apellido, fechaNacimiento, ciudadNac, paisNac, ciudadRes, formacion;
    char sexo;
    int anioInicio, anioPrimeraObra;

    cout << "\n--- Registro de nuevo autor ---\n";

    cout << "ID del autor: ";
    cin >> id;

    // Verifica que no exista ese ID
    for (const Autor& a : listaAutores) {
        if (a.getIdAutor() == id) {
            cout << "Ya existe un autor con ese ID.\n";
            return;
        }
    }

    cout << "Nombre: ";
    cin.ignore(); getline(cin, nombre);

    cout << "Apellido: ";
    getline(cin, apellido);

    cout << "Sexo (M/F): ";
    cin >> sexo;

    cout << "Fecha de nacimiento (YYYY-MM-DD): ";
    cin.ignore(); getline(cin, fechaNacimiento);

    cout << "Ciudad de nacimiento: ";
    getline(cin, ciudadNac);

    cout << "País de nacimiento: ";
    getline(cin, paisNac);

    cout << "Ciudad de residencia: ";
    getline(cin, ciudadRes);

    cout << "Formación base: ";
    getline(cin, formacion);

    cout << "Año de inicio en la literatura: ";
    cin >> anioInicio;

    cout << "Año de publicación de la primera obra: ";
    cin >> anioPrimeraObra;

    Autor nuevo(id, nombre, apellido, sexo, fechaNacimiento, ciudadNac, paisNac, ciudadRes, formacion, anioInicio, anioPrimeraObra);
    listaAutores.agregar(nuevo);

    cout << "Autor agregado exitosamente.\n";
}

// Permite modificar uno de los campos del autor dado su ID
void modificarAutor() {
    string id;
    cout << "\n--- Modificar autor ---\n";
    cout << "Ingrese el ID del autor que desea modificar: ";
    cin >> id;

    // Buscar el autor
    bool encontrado = false;
    for (Autor& a : listaAutores) {
        if (a.getIdAutor() == id) {
            encontrado = true;

            cout << "\nDatos actuales:\n";
            a.mostrar();

            cout << "\n--- Campos modificables ---\n";
            cout << "1. Nombre\n";
            cout << "2. Apellido\n";
            cout << "3. Sexo\n";
            cout << "4. Fecha de nacimiento\n";
            cout << "5. Ciudad de nacimiento\n";
            cout << "6. País de nacimiento\n";
            cout << "7. Ciudad de residencia\n";
            cout << "8. Formación base\n";
            cout << "9. Año de inicio en literatura\n";
            cout << "10. Año de primera obra\n";
            cout << "0. Cancelar\n";
            cout << "Seleccione una opción: ";

            int opcion;
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: {
                    string nuevo;
                    cout << "Nuevo nombre: ";
                    getline(cin, nuevo);
                    a.setNombre(nuevo);
                    break;
                }
                case 2: {
                    string nuevo;
                    cout << "Nuevo apellido: ";
                    getline(cin, nuevo);
                    a.setApellido(nuevo);
                    break;
                }
                case 3: {
                    char nuevo;
                    cout << "Nuevo sexo (M/F): ";
                    cin >> nuevo;
                    a.setSexo(nuevo);
                    break;
                }
                case 4: {
                    string nuevo;
                    cout << "Nueva fecha de nacimiento (YYYY-MM-DD): ";
                    getline(cin, nuevo);
                    a.setFechaNacimiento(nuevo);
                    break;
                }
                case 5: {
                    string nuevo;
                    cout << "Nueva ciudad de nacimiento: ";
                    getline(cin, nuevo);
                    a.setCiudadNacimiento(nuevo);
                    break;
                }
                case 6: {
                    string nuevo;
                    cout << "Nuevo país de nacimiento: ";
                    getline(cin, nuevo);
                    a.setPaisNacimiento(nuevo);
                    break;
                }
                case 7: {
                    string nuevo;
                    cout << "Nueva ciudad de residencia: ";
                    getline(cin, nuevo);
                    a.setCiudadResidencia(nuevo);
                    break;
                }
                case 8: {
                    string nuevo;
                    cout << "Nueva formación base: ";
                    getline(cin, nuevo);
                    a.setFormacionBase(nuevo);
                    break;
                }
                case 9: {
                    int nuevo;
                    cout << "Nuevo año de inicio en literatura: ";
                    cin >> nuevo;
                    a.setAnioInicio(nuevo);
                    break;
                }
                case 10: {
                    int nuevo;
                    cout << "Nuevo año de primera obra: ";
                    cin >> nuevo;
                    a.setAnioPrimeraObra(nuevo);
                    break;
                }
                case 0:
                    cout << "Modificación cancelada.\n";
                    return;
                default:
                    cout << "Opción inválida.\n";
                    return;
            }

            cout << "Autor modificado exitosamente.\n";
            return;
        }
    }

    if (!encontrado) {
        cout << "No se encontró un autor con ese ID.\n";
    }
}

// Permite modificar nombre, tipo de poesía o ID del autor de una obra existente
void modificarObra() {
    string nombre;
    cout << "\n=== Modificar Obra ===\n";
    cout << "Ingrese el nombre de la obra que desea modificar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombre);

    for (Obra& o : listaObras) {
        if (o.getNombre() == nombre) {
            cout << "\nObra encontrada. ¿Qué desea modificar?\n";
            cout << "1. Nombre\n";
            cout << "2. Tipo de poesía\n";
            cout << "3. ID del autor\n";
            cout << "0. Cancelar\n";
            cout << "Opción: ";

            int opcion;
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: {
                    string nuevoNombre;
                    cout << "Nuevo nombre de la obra: ";
                    getline(cin, nuevoNombre);
                    o.setNombre(nuevoNombre);
                    break;
                }
                case 2: {
                    string nuevoTipo;
                    cout << "Nuevo tipo de poesía: ";
                    getline(cin, nuevoTipo);
                    o.setTipoPoesia(nuevoTipo);
                    break;
                }
                case 3: {
                    string nuevoAutor;
                    cout << "Nuevo ID del autor: ";
                    getline(cin, nuevoAutor);
                    o.setIdAutor(nuevoAutor);
                    break;
                }
                case 0:
                    cout << "Modificación cancelada.\n";
                return;
                default:
                    cout << "Opción inválida.\n";
                return;
            }

            cout << "Obra modificada correctamente.\n";
            return;
        }
    }

    cout << "No se encontró una obra con ese nombre.\n";
}

// Permite modificar los datos de una editorial existente
void modificarEditorial() {
    string id;
    cout << "\n=== Modificar Editorial ===\n";
    cout << "Ingrese el ID de la editorial que desea modificar: ";
    cin >> id;

    for (Editorial& e : listaEditoriales) {
        if (e.getIdEditorial() == id) {
            cout << "\nEditorial encontrada. ¿Qué desea modificar?\n";
            cout << "1. Nombre\n";
            cout << "2. Ciudad\n";
            cout << "3. País\n";
            cout << "0. Cancelar\n";
            cout << "Opción: ";

            int opcion;
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
                case 1: {
                    string nuevo;
                    cout << "Nuevo nombre: ";
                    getline(cin, nuevo);
                    e.setNombre(nuevo);
                    break;
                }
                case 2: {
                    string nuevo;
                    cout << "Nueva ciudad: ";
                    getline(cin, nuevo);
                    e.setCiudad(nuevo);
                    break;
                }
                case 3: {
                    string nuevo;
                    cout << "Nuevo país: ";
                    getline(cin, nuevo);
                    e.setPais(nuevo);
                    break;
                }
                case 0:
                    cout << "Modificación cancelada.\n";
                return;
                default:
                    cout << "Opción inválida.\n";
                return;
            }

            cout << "Editorial modificada correctamente.\n";
            return;
        }
    }

    cout << "No se encontró una editorial con ese ID.\n";
}

// Carga todas las editoriales desde el archivo 'editoriales.txt' a la lista
void cargarEditoriales() {
    ifstream archivo("editoriales.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, ciudad, pais;
        getline(ss, id, '|');
        getline(ss, nombre, '|');
        getline(ss, ciudad, '|');
        getline(ss, pais, '|');


        Editorial e(id, nombre, ciudad, pais);
        listaEditoriales.agregar(e);
    }

    archivo.close();
    cout << "Editoriales cargadas correctamente.\n";
}

void mostrarEditoriales() {
    if (listaEditoriales.vacia()) {
        cout << "No hay editoriales cargadas.\n";
        return;
    }

    for (auto it = listaEditoriales.begin(); it != listaEditoriales.end(); ++it)
        it->mostrar();

}

// Guarda las editoriales en el archivo 'editoriales.txt'
void guardarEditoriales() {
    ofstream archivo("editoriales.txt");
    for (const Editorial& e : listaEditoriales) {
        archivo << e.getIdEditorial() << "|"
        << e.getNombre() << "|"
        << e.getCiudad() << "|"
        << e.getPais() << "\n";
    }
    archivo.flush();
    archivo.close();
    cout << "Editoriales guardadas correctamente.\n";
}

// Carga todas las obras desde el archivo 'obras.txt', incluyendo sus ediciones
void cargarObras() {
    ifstream archivo("obras.txt");
    if (!archivo) {
        cout << "[ERROR] No se pudo abrir obras.txt (¿está en la ruta correcta?).\n";
        return;
    }
    string linea;
    //cout << "[INFO] Leyendo archivo obras.txt...\n";

    while (getline(archivo, linea)) {
        //cout << "[DEBUG] Línea RAW: " << linea << "\n";

        stringstream ss(linea);

        string nombre, tipo, idAutor;

        getline(ss, nombre, '|');
        getline(ss, tipo, '|');
        getline(ss, idAutor, '|');


        //cout << "[DEBUG] Campos base: nombre=" << nombre << ", tipo=" << tipo << ", autor=" << idAutor << endl;

        Obra obra(nombre, tipo, idAutor);

        while (ss.good()) {
            string numEdStr, fecha, idEdit, ciudad;

            getline(ss, numEdStr, '|');
            if (numEdStr.empty()) break;

            getline(ss, fecha, '|');
            getline(ss, idEdit, '|');
            getline(ss, ciudad, '|');

            try {
                int numEd = stoi(numEdStr);
                Edicion ed(numEd, fecha, idEdit, ciudad);
                obra.agregarEdicion(ed);
            } catch (const exception& e) {
                cout << "Error leyendo edición: " << e.what() << endl;
                break;
            }
        }

        listaObras.agregar(obra);
    }

    archivo.close();
    cout << "Obras cargadas correctamente.\n";
}

void mostrarObras() {
    if (listaObras.vacia()) {
        cout << "No hay obras cargadas.\n";
        return;
    }

    for (auto it = listaObras.begin(); it != listaObras.end(); ++it)
        it->mostrar();

}

// Guarda todas las obras y sus ediciones en el archivo 'obras.txt'
void guardarObras() {
    ofstream archivo("obras.txt");

    for (const Obra& o : listaObras) {
        archivo << o.getNombre() << "|"
        << o.getTipoPoesia() << "|"
        << o.getIdAutor();

        for (const Edicion& e : o.getEdiciones()) {
            archivo << "|" << e.getNumeroEdicion()
                    << "|" << e.getFechaPublicacion()
                    << "|" << e.getIdEditorial()
                    << "|" << e.getCiudadPublicacion();
        }
        archivo << "\n";

    }
    archivo.flush();
    archivo.close();
    cout << "Obras guardadas correctamente.\n";
}

// Agrega una nueva obra, asociada a un autor, junto con sus ediciones
void agregarObra() {
    string nombreObra, tipoPoesia, idAutor;
    int cantidadEdiciones;

    cout << "\n--- Registro de nueva obra ---\n";

    cout << "Nombre de la obra: ";
    cin.ignore(); getline(cin, nombreObra);

    cout << "Tipo de poesía (soneto, haiku, etc.): ";
    getline(cin, tipoPoesia);

    cout << "ID del autor: ";
    getline(cin, idAutor);

    // Verifica si el autor existe
    bool autorExiste = false;
    for (auto it = listaAutores.begin(); it != listaAutores.end(); ++it) {
        if ((*it).getIdAutor() == idAutor){
            autorExiste = true;
            break;
        }
    }

    if (!autorExiste) {
        cout << "No existe un autor con ese ID. Cancela la operación.\n";
        return;
    }

    Obra nuevaObra(nombreObra, tipoPoesia, idAutor);

    cout << "¿Cuántas ediciones deseas registrar para esta obra?: ";
    cin >> cantidadEdiciones;

    for (int i = 0; i < cantidadEdiciones; i++) {
        int numEd;
        string fecha, idEditorial, ciudad;

        cout << "\n--- Edición " << (i + 1) << " ---\n";

        cout << "Número de edición: ";
        cin >> numEd;

        cin.ignore();
        cout << "Fecha de publicación (YYYY-MM-DD): ";
        getline(cin, fecha);

        cout << "ID de la editorial: ";
        getline(cin, idEditorial);

        // Verifica si la editorial existe (opcional)
        bool editorialExiste = false;
        for (const Editorial& e : listaEditoriales) {
            if (e.getIdEditorial() == idEditorial) {
                editorialExiste = true;
                break;
            }
        }

        if (!editorialExiste) {
            cout << "Advertencia: la editorial no existe (se puede agregar más tarde).\n";
        }

        cout << "Ciudad de publicación: ";
        getline(cin, ciudad);

        Edicion ed(numEd, fecha, idEditorial, ciudad);
        nuevaObra.agregarEdicion(ed);
    }

    listaObras.agregar(nuevaObra);
    cout << "Obra registrada exitosamente.\n";
}

struct ComparadorAutorCiudadAnio {
    bool operator()(const Autor& a, const Autor& b) const {
        if (a.getCiudadResidencia() != b.getCiudadResidencia())
            return a.getCiudadResidencia() < b.getCiudadResidencia();
        return a.getAnioInicio() < b.getAnioInicio();
    }
};

// Lista los autores que han sido publicados por una editorial específica
void consultarAutoresPorEditorial() {
    string idEditorial;
    cout << "Ingrese el ID de la editorial: ";
    cin >> idEditorial;

    set<string> idsAutoresPublicados;

    // Buscar autores que tengan al menos una obra publicada por esta editorial
    for (const Obra& o : listaObras) {
        for (const Edicion& ed : o.getEdiciones()) {
            if (ed.getIdEditorial() == idEditorial) {
                idsAutoresPublicados.insert(o.getIdAutor());
                break;
            }
        }
    }

    if (idsAutoresPublicados.empty()) {
        cout << "Ningún autor ha sido publicado por esa editorial.\n";
        return;
    }

    // Mostrar datos de los autores encontrados, clasificados por ciudad de residencia y año de inicio
    cout << "\nAutores publicados por la editorial " << idEditorial << ":\n";

    BST<Autor, ComparadorAutorCiudadAnio> autoresOrdenados;
    for (auto it = listaAutores.begin(); it != listaAutores.end(); ++it) {
        const Autor& a = *it;
        if (idsAutoresPublicados.count(a.getIdAutor())) {
            autoresOrdenados.insertar(a);
        }
    }

    // Mostrar resultados
    autoresOrdenados.recorrerInorden([](const Autor& a) {
        cout << "Nombre: " << a.getNombre() << " " << a.getApellido() << endl;
        cout << "Lugar de nacimiento: " << a.getCiudadNacimiento() << ", " << a.getPaisNacimiento() << endl;
        cout << "Ciudad de residencia: " << a.getCiudadResidencia() << " | Año inicio: " << a.getAnioInicio() << endl;
        cout << "---------------------------------------\n";
    });
}
// Muestra cuántas obras ha publicado un autor dado, clasificadas por editorial y año
void contarObrasPorEditorialYAnio() {
    string idAutor;
    cout << "Ingrese el ID del autor: ";
    cin >> idAutor;

    map<string, map<int, int>> resumen;

    for (const Obra& obra : listaObras) {
        if (trim(obra.getIdAutor()) == trim(idAutor)) {
            for (const Edicion& ed : obra.getEdiciones()) {
                string editorial = ed.getIdEditorial();

                // Obtener el año de la fecha (YYYY-MM-DD)
                string fecha = ed.getFechaPublicacion();
                int anio = 0;
                try {
                    anio = stoi(fecha.substr(0, 4));
                } catch (...) {
                    continue; // si hay error, lo ignora
                }

                resumen[editorial][anio]++;
            }
        }
    }

    if (resumen.empty()) {
        cout << "No se encontraron obras para ese autor.\n";
        return;
    }

    cout << "\nResumen de obras por editorial y año:\n";
    for (const auto& parEditorial : resumen) {
        cout << "Editorial: " << obtenerNombreEditorial(parEditorial.first) << endl;
        for (const auto& parAnio : parEditorial.second) {
            cout << "  Año " << parAnio.first << ": " << parAnio.second << " obras\n";
        }
        cout << "-----------------------------------\n";
    }
}

// Lista todas las obras de un autor clasificadas por tipo de poesía
void listarObrasPorAutorPorTipo() {
    string idAutor;
    cout << "Ingrese el ID del autor: ";
    cin >> idAutor;

    // Map: tipo de poesía -> lista de obras
    map<string, vector<Obra>> obrasPorTipo;

    for (const Obra& o : listaObras) {
        if (trim(o.getIdAutor()) == trim(idAutor)) {
            obrasPorTipo[o.getTipoPoesia()].push_back(o);
        }
    }

    if (obrasPorTipo.empty()) {
        cout << "No se encontraron obras para ese autor.\n";
        return;
    }

    cout << "\nObras del autor " << idAutor << " clasificadas por tipo de poesía:\n";

    for (const auto& par : obrasPorTipo) {
        cout << "\nTipo de poesía: " << par.first << "\n";

        for (const Obra& o : par.second) {
            cout << "Obra: " << o.getNombre() << "\n";
            for (const Edicion& e : o.getEdiciones()) {
                cout << "  Edición " << e.getNumeroEdicion()
                     << " | Fecha: " << e.getFechaPublicacion() << "\n";
            }
        }
        cout << "-----------------------------------\n";
    }
}

// Muestra editoriales que han publicado obras de más de N autores diferentes
void mostrarEditorialesConMuchosPoetas() {
    int minimoPoetas;
    cout << "Ingrese el número mínimo de poetas: ";
    cin >> minimoPoetas;

    // Mapeo: ID de editorial -> conjunto de IDs de autores
    map<string, set<string>> editorialAutores;

    for (const Obra& obra : listaObras) {
        const string& autorId = obra.getIdAutor();
        for (const Edicion& ed : obra.getEdiciones()) {
            editorialAutores[ed.getIdEditorial()].insert(autorId);
        }
    }

    bool alguna = false;
    cout << "\nEditoriales con más de " << minimoPoetas << " poetas:\n";

    for (const auto& par : editorialAutores) {
        const string& idEdit = par.first;
        int cantidadPoetas = par.second.size();

        if (cantidadPoetas > minimoPoetas) {
            alguna = true;
            // Buscar la editorial en la lista
            Editorial* edPtr = nullptr;
            for (auto it = listaEditoriales.begin(); it != listaEditoriales.end(); ++it) {
                if (it->getIdEditorial() == idEdit) {
                    edPtr = &(*it);
                    break;
                }
            }

            if (edPtr) {
                cout << "Editorial: " << edPtr->getNombre() << " (" << idEdit << ")\n";
                cout << "Ciudad: " << edPtr->getCiudad() << ", País: " << edPtr->getPais() << "\n";
                cout << "Cantidad de poetas: " << cantidadPoetas << "\n";
                cout << "-----------------------------------\n";
            }
        }
    }

    if (!alguna) {
        cout << "Ninguna editorial supera el número de poetas especificado.\n";
    }
}

// Cuenta la cantidad de hombres y mujeres publicados por cada editorial
void contarGeneroPorEditorial() {
    cout << "\nResumen de autores por editorial (clasificado por ciudad y país de nacimiento):\n";

    for (const Editorial& editorial : listaEditoriales) {
        string idEditorial = editorial.getIdEditorial();

        // Usamos un set para evitar contar autores repetidos por varias ediciones
        set<string> autoresContados;
        int hombres = 0, mujeres = 0;

        for (const Obra& obra : listaObras) {
            if (obra.getIdAutor().empty()) continue;

            for (const Edicion& ed : obra.getEdiciones()) {
                if (ed.getIdEditorial() == idEditorial) {
                    string idAutor = obra.getIdAutor();
                    if (autoresContados.count(idAutor)) continue;

                    // Buscar al autor en listaAutores
                    for (const Autor& a : listaAutores) {
                        if (a.getIdAutor() == idAutor) {
                            autoresContados.insert(idAutor);

                            // Imprimir autor
                            cout << "Editorial: " << editorial.getNombre()
                                 << " (" << editorial.getCiudad() << ", " << editorial.getPais() << ")\n";
                            cout << "Autor: " << a.getNombre() << " " << a.getApellido()
                                 << " | Ciudad: " << a.getCiudadNacimiento()
                                 << " | País: " << a.getPaisNacimiento()
                                 << " | Sexo: " << a.getSexo() << "\n";

                            // Contar por sexo
                            char sexo = toupper(a.getSexo());
                            if (sexo == 'M') hombres++;
                            else if (sexo == 'F') mujeres++;
                            else
                                cout << "[Advertencia] Sexo desconocido para " << a.getNombre() << "\n";
                            break;
                        }
                    }
                }
            }
        }

        // Imprimir resumen por editorial
        if (!autoresContados.empty()) {
            cout << "Total Hombres: " << hombres << "\n";
            cout << "Total Mujeres: " << mujeres << "\n";
            cout << "---------------------------------------\n";
        }
    }
}

// Calcula la edad actual del autor a partir de su fecha de nacimiento
int obtenerEdadDesdeFecha(const string& fechaNacimiento) {
    // Supone formato YYYY-MM-DD
    int anioNacimiento = stoi(fechaNacimiento.substr(0, 4));

    // Obtener el año actual
    time_t t = time(nullptr);
    tm* tiempo = localtime(&t);
    int anioActual = tiempo->tm_year + 1900;

    return anioActual - anioNacimiento;
}

// Convierte una cadena a minúsculas y sin espacios para comparaciones insensibles a formato
string aMinusculasYSinEspacios(string str) {
    string limpio;
    for (char c : str) {
        if (!isspace(c)) limpio += tolower(c);
    }
    return limpio;
}

// Muestra autores dentro de un rango de edad y con determinada formación
void consultarAutoresPorEdadYFormacion() {
    int edadMin, edadMax;
    string formacionInput;

    cout << "Ingrese edad mínima: ";
    cin >> edadMin;

    cout << "Ingrese edad máxima: ";
    cin >> edadMax;

    cout << "Ingrese formación base: ";
    cin.ignore();
    getline(cin, formacionInput);

    string formacionLimpiada = aMinusculasYSinEspacios(formacionInput);

    // Filtramos autores válidos
    vector<Autor> autoresFiltrados;
    for (const Autor& a : listaAutores) {
        int edad = obtenerEdadDesdeFecha(a.getFechaNacimiento());

        string formacionAutor = aMinusculasYSinEspacios(a.getFormacionBase());

        if (edad >= edadMin && edad <= edadMax && formacionAutor == formacionLimpiada) {
            autoresFiltrados.push_back(a);
        }
    }

    if (autoresFiltrados.empty()) {
        cout << "No se encontraron autores con esos criterios.\n";
        return;
    }

    // Ordenar por año de publicación de la primera obra
    sort(autoresFiltrados.begin(), autoresFiltrados.end(), [](const Autor& a, const Autor& b) {
        return a.getAnioPrimeraObra() < b.getAnioPrimeraObra();
    });

    cout << "\nAutores entre " << edadMin << " y " << edadMax
         << " años con formación en " << formacionInput << ":\n";

    for (const Autor& a : autoresFiltrados) {
        int edad = obtenerEdadDesdeFecha(a.getFechaNacimiento());
        cout << "Nombre: " << a.getNombre() << " " << a.getApellido()
             << " | Año primera obra: " << a.getAnioPrimeraObra()
             << " | Edad actual: " << edad << "\n";
    }
}

// Muestra autores que escribieron un tipo específico de poesía para una editorial determinada
void consultarAutoresPorTipoYEditorial() {
    string tipoPoesia, idEditorial;
    cout << "Ingrese el tipo de poesía: ";
    cin.ignore();
    getline(cin, tipoPoesia);

    cout << "Ingrese el ID de la editorial: ";
    getline(cin, idEditorial);

    set<string> idsAutores;

    for (const Obra& o : listaObras) {
        if (trim(o.getTipoPoesia()) == trim(tipoPoesia)) {
            for (const Edicion& ed : o.getEdiciones()) {
                if (ed.getIdEditorial() == idEditorial) {
                    idsAutores.insert(o.getIdAutor());
                    break;
                }
            }
        }
    }

    if (idsAutores.empty()) {
        cout << "No se encontraron autores con esas características.\n";
        return;
    }

    cout << "\nAutores con obras tipo '" << tipoPoesia << "' en la editorial " << idEditorial << ":\n";

    for (const string& id : idsAutores) {
        // Buscar autor
        for (const Autor& a : listaAutores) {
            if (a.getIdAutor() == id) {
                cout << "\nAutor: " << a.getNombre() << " " << a.getApellido() << endl;
                break;
            }
        }

        // Mostrar ediciones
        for (const Obra& o : listaObras) {
            if (o.getIdAutor() == id && o.getTipoPoesia() == tipoPoesia) {
                for (const Edicion& ed : o.getEdiciones()) {
                    if (ed.getIdEditorial() == idEditorial) {
                        cout << "  Obra: " << o.getNombre()
                             << " | Edición: " << ed.getNumeroEdicion()
                             << " | Fecha: " << ed.getFechaPublicacion()
                             << " | Ciudad: " << ed.getCiudadPublicacion() << "\n";
                    }
                }
            }
        }
        cout << "-----------------------------------\n";
    }
}

// Elimina un autor de la lista por ID
void eliminarAutor() {
    string id;
    cout << "\n=== Eliminar Autor ===\n";
    cout << "Ingrese el ID del autor a eliminar: ";
    cin >> id;

    for (auto it = listaAutores.begin(); it != listaAutores.end(); ++it) {
        if (it->getIdAutor() == id) {
            listaAutores.eliminar(it);
            cout << "Autor eliminado correctamente.\n";
            return;
        }
    }

    cout << "No se encontró un autor con ese ID.\n";
}

// Elimina una obra de la lista por nombre
void eliminarObra() {
    string nombre;
    cout << "\n=== Eliminar Obra ===\n";
    cout << "Ingrese el nombre de la obra a eliminar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombre);

    for (auto it = listaObras.begin(); it != listaObras.end(); ++it) {
        if (it->getNombre() == nombre) {
            listaObras.eliminar(it);
            cout << "Obra eliminada correctamente.\n";
            return;
        }
    }

    cout << "No se encontró una obra con ese nombre.\n";
}

// Elimina una editorial de la lista por ID
void eliminarEditorial() {
    string id;
    cout << "\n=== Eliminar Editorial ===\n";
    cout << "Ingrese el ID de la editorial a eliminar: ";
    cin >> id;

    for (auto it = listaEditoriales.begin(); it != listaEditoriales.end(); ++it) {
        if (it->getIdEditorial() == id) {
            listaEditoriales.eliminar(it);
            cout << "Editorial eliminada correctamente.\n";
            return;
        }
    }

    cout << "No se encontró una editorial con ese ID.\n";
}

// Punto de entrada del programa. Carga los datos y presenta el menú principal.
int main() {
    // Carga automática de datos al iniciar el programa
    cargarAutores();
    autoresCargados = true;

    cargarEditoriales();
    editorialesCargadas = true;

    cargarObras();
    obrasCargadas = true;

    cout << "Datos cargados automáticamente desde archivos.\n";

    int opcion;
do {
    cout << "\n========== MENÚ PRINCIPAL ==========\n";

    cout << "\n--- Mostrar datos ---\n";
    cout << " 1. Mostrar autores\n";
    cout << " 2. Mostrar editoriales\n";
    cout << " 3. Mostrar obras\n";

    cout << "\n--- Consultas y reportes ---\n";
    cout << " 4. Listar obras por autor y tipo de poesía\n";
    cout << " 5. Autores publicados por una editorial (ordenados)\n";
    cout << " 6. Contar obras por editorial y año (para un autor)\n";
    cout << " 7. Editoriales con más de N poetas\n";
    cout << " 8. Cantidad de hombres y mujeres publicados por editorial\n";
    cout << " 9. Autores según rango de edad y formación\n";
    cout << "10. Autores por tipo de poesía y editorial (con ediciones)\n";

    cout << "\n--- Gestión de datos ---\n";
    cout << "11. Agregar nuevo autor\n";
    cout << "12. Agregar nueva obra con ediciones\n";
    cout << "13. Modificar autor\n";
    cout << "14. Modificar obra\n";
    cout << "15. Modificar editorial\n";
    cout << "16. Eliminar autor\n";
    cout << "17. Eliminar obra\n";
    cout << "18. Eliminar editorial\n";

    cout << "\n 0. Salir y guardar cambios\n";
    cout << "=====================================\n";
    cout << "Opción: ";
    cin >> opcion;

    switch (opcion) {
        // Mostrar
        case 1: mostrarAutores(); break;
        case 2: mostrarEditoriales(); break;
        case 3: mostrarObras(); break;

        // Consultas
        case 4: listarObrasPorAutorPorTipo(); break;
        case 5: consultarAutoresPorEditorial(); break;
        case 6: contarObrasPorEditorialYAnio(); break;
        case 7: mostrarEditorialesConMuchosPoetas(); break;
        case 8: contarGeneroPorEditorial(); break;
        case 9: consultarAutoresPorEdadYFormacion(); break;
        case 10: consultarAutoresPorTipoYEditorial(); break;

        // Gestión
        case 11: agregarAutor(); break;
        case 12: agregarObra(); break;
        case 13: modificarAutor(); break;
        case 14: modificarObra(); break;
        case 15: modificarEditorial(); break;
        case 16: eliminarAutor(); break;
        case 17: eliminarObra(); break;
        case 18: eliminarEditorial(); break;

        case 0:
            cout << "\nGuardando datos...\n";
            guardarAutores();
            guardarEditoriales();
            guardarObras();
            cout << "¡Hasta pronto!\n";
            break;

        default:
            cout << "Opción inválida. Intente de nuevo.\n";
    }

} while (opcion != 0);

    return 0;
}
