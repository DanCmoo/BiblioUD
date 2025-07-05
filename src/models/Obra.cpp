#include "Obra.h"
#include <iostream>
using namespace std;

void Obra::mostrar() {
    cout << "Obra: " << nombreObra << " | Tipo: " << tipoPoesia << " | Autor ID: " << idAutor << endl;
    cout << "Ediciones:\n";
    for (const Edicion& e : ediciones)
        e.mostrar();
}
