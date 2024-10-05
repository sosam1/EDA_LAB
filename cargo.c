#include "cargo.h"
#include <iostream>

using namespace std;

// Estructura del nodo_cargo
struct nodo_cargo {
    Cadena nombre_cargo;
    Cargo ph;
    Cargo sh;
};

// Implementación de la función que crea un nuevo cargo
Cargo CrearNuevoCargo(Cadena nombre) {
    Cargo c = new(nodo_cargo);
    if (c != NULL) {
        c->nombre_cargo = nombre;
        c->ph = NULL;
        c->sh = NULL;
    }
    return c;
}
