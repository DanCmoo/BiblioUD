#include "Edicion.h"
#include <iostream>
using namespace std;

void Edicion::mostrar() const {
    cout << "Edición " << numeroEdicion << " | Fecha: " << fechaPublicacion
         << " | Editorial: " << idEditorial << " | Ciudad: " << ciudadPublicacion << endl;
}