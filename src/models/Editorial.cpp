#include "Editorial.h"
#include <iostream>
using namespace std;

int Editorial::numEDitorial = 0;
void Editorial::mostrar() {
    cout << "ID: " << idEditorial << ", Nombre: " << nombre
         << ", Ciudad: " << ciudad << ", Pais: " << pais << endl;
}
