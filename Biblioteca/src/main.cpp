#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>     // Para std::set
#include <algorithm> // Para std::sort


#include "models/Autor.h"
#include "models/Edicion.h"
#include "models/Editorial.h"
#include "models/Obra.h"
using namespace std;

vector<Autor> listaAutores;
vector<Editorial> listaEditoriales;
vector<Obra> listaObras;

bool autoresCargados = false;
bool editorialesCargadas = false;
bool obrasCargadas = false;

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
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, sexoStr, ',');
        getline(ss, fechaNac, ',');
        getline(ss, ciudadNac, ',');
        getline(ss, paisNac, ',');
        getline(ss, ciudadRes, ',');
        getline(ss, formacion, ',');
        ss >> anioInicio;
        ss.ignore();
        ss >> anioPrimera;

        Autor a(id, nombre, apellido, sexoStr[0], fechaNac, ciudadNac, paisNac, ciudadRes, formacion, anioInicio, anioPrimera);
        listaAutores.push_back(a);
    }

    archivo.close();
    cout << "Autores cargados correctamente.\n";
}

void mostrarAutores() {
    if (listaAutores.empty()) {
        cout << "No hay autores cargados.\n";
        return;
    }
    for (Autor a : listaAutores)
        a.mostrar();
}

void guardarAutores() {
    if (listaAutores.empty()) {
        cout << "No hay autores para guardar.\n";
        return;
    }

    ofstream archivo("autores.txt");
    for (const Autor& a : listaAutores) {
        archivo << a.getIdAutor() << ","
                << a.getNombre() << ","
                << a.getApellido() << ","
                << a.getSexo() << ","
                << a.getFechaNacimiento() << ","
                << a.getCiudadNacimiento() << ","
                << a.getPaisNacimiento() << ","
                << a.getCiudadResidencia() << ","
                << a.getFormacionBase() << ","
                << a.getAnioInicio() << ","
                << a.getAnioPrimeraObra() << "\n";
    }
    archivo.close();
    cout << "Autores guardados correctamente (" << listaAutores.size() << " autores).\n";
}

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
    listaAutores.push_back(nuevo);

    cout << "Autor agregado exitosamente.\n";
}

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

void cargarEditoriales() {
    ifstream archivo("editoriales.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, nombre, ciudad, pais;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, ciudad, ',');
        getline(ss, pais, ',');

        Editorial e(id, nombre, ciudad, pais);
        listaEditoriales.push_back(e);
    }

    archivo.close();
    cout << "Editoriales cargadas correctamente.\n";
}

void mostrarEditoriales() {
    if (listaEditoriales.empty()) {
        cout << "No hay editoriales cargadas.\n";
        return;
    }

    for (Editorial e : listaEditoriales)
        e.mostrar();
}

void guardarEditoriales() {
    ofstream archivo("editoriales.txt");
    for (const Editorial& e : listaEditoriales) {
        archivo << e.getIdEditorial() << ","
                << e.getNombre() << ","
                << e.getCiudad() << ","
                << e.getPais() << "\n";
    }
    archivo.close();
    cout << "Editoriales guardadas correctamente.\n";
}

void cargarObras() {
    ifstream archivo("obras.txt");
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, tipo, idAutor;
        getline(ss, nombre, ',');
        getline(ss, tipo, ',');
        getline(ss, idAutor, ',');

        Obra obra(nombre, tipo, idAutor);

        while (ss.peek() != EOF) {
            int numEd;
            string fecha, idEdit, ciudad;
            ss >> numEd;
            ss.ignore();
            getline(ss, fecha, ',');
            getline(ss, idEdit, ',');
            getline(ss, ciudad, ',');
            Edicion ed(numEd, fecha, idEdit, ciudad);
            obra.agregarEdicion(ed);
        }

        listaObras.push_back(obra);
    }

    archivo.close();
    cout << "Obras cargadas correctamente.\n";
}

void mostrarObras() {
    if (listaObras.empty()) {
        cout << "No hay obras cargadas.\n";
        return;
    }

    for (Obra o : listaObras)
        o.mostrar();
}

void guardarObras() {
    ofstream archivo("obras.txt");

    for (const Obra& o : listaObras) {
        archivo << o.getNombre() << ","
                << o.getTipoPoesia() << ","
                << o.getIdAutor();

        for (const Edicion& e : o.getEdiciones()) {
            archivo << "," << e.getNumeroEdicion()
                    << "," << e.getFechaPublicacion()
                    << "," << e.getIdEditorial()
                    << "," << e.getCiudadPublicacion();
        }
        archivo << "\n";
    }

    archivo.close();
    cout << "Obras guardadas correctamente.\n";
}
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
    for (const Autor& a : listaAutores) {
        if (a.getIdAutor() == idAutor) {
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

    listaObras.push_back(nuevaObra);
    cout << "Obra registrada exitosamente.\n";
}

void consultarObrasPorAutor() {
    string idAutor;
    cout << "Ingrese el ID del autor: ";
    cin >> idAutor;

    bool encontrado = false;

    for (Obra& o : listaObras) {
        if (o.getIdAutor() == idAutor) {
            if (!encontrado) {
                cout << "\nObras del autor " << idAutor << ":\n";
                encontrado = true;
            }

            cout << "\nTipo de poesia: " << o.getTipoPoesia() << endl;
            cout << "Obra: " << o.getNombre() << endl;

            const vector<Edicion>& eds = o.getEdiciones();
            for (const Edicion& e : eds) {
                cout << "  Edicion " << e.getNumeroEdicion()
                     << " | Fecha: " << e.getFechaPublicacion() << endl;
            }
        }
    }

    if (!encontrado)
        cout << "No se encontraron obras para ese autor.\n";
}
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

    vector<Autor> autoresFiltrados;
    for (const Autor& a : listaAutores) {
        if (idsAutoresPublicados.count(a.getIdAutor())) {
            autoresFiltrados.push_back(a);
        }
    }

    // Ordenar por ciudad de residencia y año de inicio
    sort(autoresFiltrados.begin(), autoresFiltrados.end(), [](const Autor& a, const Autor& b) {
        if (a.getCiudadResidencia() == b.getCiudadResidencia())
            return a.getAnioInicio() < b.getAnioInicio();
        return a.getCiudadResidencia() < b.getCiudadResidencia();
    });

    // Mostrar resultados
    for (const Autor& a : autoresFiltrados) {
        cout << "Nombre: " << a.getNombre() << " " << a.getApellido() << endl;
        cout << "Lugar de nacimiento: " << a.getCiudadNacimiento() << ", " << a.getPaisNacimiento() << endl;
        cout << "Ciudad de residencia: " << a.getCiudadResidencia() << " | Año inicio: " << a.getAnioInicio() << endl;
        cout << "---------------------------------------\n";
    }
}

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
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Mostrar autores\n";
        cout << "2. Mostrar editoriales\n";
        cout << "3. Mostrar obras\n";
        cout << "4. Consultar obras por autor (tipo de poesía)\n";
        cout << "5. Autores publicados por una editorial (agrupados)\n";
        cout << "6. Agregar nuevo autor\n";
        cout << "7. Agregar nueva obra con ediciones\n";
        cout << "8. Modificar autor\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarAutores();
            break;
            case 2:
                mostrarEditoriales();
            break;
            case 3:
                mostrarObras();
            break;
            case 4:
                consultarObrasPorAutor();
            break;
            case 5:
                consultarAutoresPorEditorial();
            break;
            case 6:
                agregarAutor();
            break;
            case 7:
                agregarObra();
            break;
            case 8:
                modificarAutor();
            break;
            case 0:
                cout << "Guardando datos...\n";
            guardarAutores();
            guardarEditoriales();
            guardarObras();
            cout << "Saliendo del programa...\n";
            break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 0);

    return 0;
}

