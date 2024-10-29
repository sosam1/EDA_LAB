#ifndef CARGO_H
#define CARGO_H

#include "definiciones.h" // Definición de Cadena y otros tipos usados
#include "persona.h"

typedef struct nodo_cargo * Cargo;

typedef struct nodo_lista * Lista;

// Funciones para manipular cargos
Cargo CrearNuevoCargo(Cadena nombre);

Cadena ObtenerNombreCargo(Cargo c);

bool cargoPertenece (Cargo x, Cadena nombre_cargo);

Cargo ObtenerCargo(Cargo c, Cadena nombre_cargo);

Cargo& ObtenerPH(Cargo x);

Cargo& ObtenerSH(Cargo x);

/* void arbol_imprimir_tree_aux(Cargo x); */

Lista InsertarCargosALista(Cargo x, Lista &l);

void OrdenarAlfabetico(Lista &l);

void EliminarCargos(Cargo primer_cargo);

bool PersonaExisteEnArbol(Cargo c, Cadena ci);

void InsertarPersonaACargo(Cargo cargo_raiz, Cadena c, Cadena nom, Cadena ci);

void ImprimirPersonasEnUnCargo(Cargo cargo_raiz, Cadena cargo_buscado);

Cargo BuscarCargoPorPersona(Cargo raiz, Cadena ci);

void EliminarPersonaDeCargo(Cargo raiz, Cadena ci);

void ImprimirConIdentacion(Cargo cargo, int nivel);

void ListarCargosPorJerarquia(Cargo cargo_raiz, int nivel); 

#endif