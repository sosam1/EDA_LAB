#ifndef CARGO_H
#define CARGO_H

#include "definiciones.h" // Definición de Cadena y otros tipos usados

typedef struct nodo_cargo * Cargo;

// Funciones para manipular cargos
Cargo CrearNuevoCargo(Cadena nombre);

Cadena ObtenerNombreCargo(Cargo c);

bool cargoPertenece (Cargo x, Cadena nombre_cargo);

Cargo ObtenerCargo(Cargo c, Cadena nombre_cargo);

Cargo& ObtenerPH(Cargo x);

Cargo& ObtenerSH(Cargo x);

void arbol_imprimir_tree_aux(Cargo x);

#endif