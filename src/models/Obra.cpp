#include "Obra.h"
#include "Edicion.h"
#include <iostream>
using namespace std;

void Obra::mostrar() {
    cout << "Obra: " << nombreObra << " | Tipo: " << tipoPoesia << " | Autor ID: " << idAutor << endl;
    cout << "Ediciones:\n";
    for (const int& e : idEdiciones)
        cout << "Id : e\n";
}
