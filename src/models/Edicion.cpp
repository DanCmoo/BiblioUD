#include "Edicion.h"
#include <iostream>
using namespace std;

int Edicion::numEdicion = 0;

void Edicion::mostrar() const {
    cout << "Edicion " << numeroEdicion << " | Fecha: " << fechaPublicacion
         << " | Editorial: " << idEditorial << " | Ciudad: " << ciudadPublicacion << endl;
}