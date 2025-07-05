#include "Autor.h"
#include <iostream>
using namespace std;

void Autor::mostrar() {
    cout << "ID: " << idAutor << ", Nombre: " << nombre << " " << apellido
         << ", Formación: " << formacionBase << endl;
}
