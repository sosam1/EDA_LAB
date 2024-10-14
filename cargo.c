#include "cargo.h"
#include "definiciones.h"
#include <string.h> ///////

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
        c->nombre_cargo = new(char[MAX_NOMBRE_CARGO]);
        strcpy (c->nombre_cargo, nombre);
        c->ph = NULL;
        c->sh = NULL;
    }
    return c;
}

Cadena ObtenerNombreCargo(Cargo c) {
    return c->nombre_cargo;
}

bool cargoPertenece(Cargo x, Cadena nombre_cargo){
// Retorna true si nombre_cargo pertenece a la empresa e
	if (x == NULL)
		return false;
	else if (strcmp(x->nombre_cargo, nombre_cargo) == 0){
        return true;
    } 
    else {
        return cargoPertenece(x->ph, nombre_cargo) || cargoPertenece(x->sh, nombre_cargo);
    }
}

Cargo ObtenerCargo(Cargo c, Cadena nombre_cargo){
    if (c == NULL)
		return NULL;
	else if (strcmp(c->nombre_cargo, nombre_cargo) == 0){
        return c; // si el primer nodo coincide lo retorno
    } 
    else {
        Cargo c1, c2; // uno para recorrer los segundos hermanos y otro los primer hijo
        c1 = ObtenerCargo(c->sh, nombre_cargo);
        c2 = ObtenerCargo(c->ph, nombre_cargo);

        if(c1 != NULL){
            return c1;
        }
        else if(c2 != NULL){
            return c2;
        }
        else {
            return NULL;
        }
    }
}

Cargo& ObtenerPH(Cargo x){
    return x->ph;
}

Cargo& ObtenerSH(Cargo x){
    return x->sh;
}

void arbol_imprimir_tree_aux(Cargo x){
    if (x != NULL){
        cout << ObtenerNombreCargo(x) << endl;
        arbol_imprimir_tree_aux(ObtenerPH(x));
        arbol_imprimir_tree_aux(ObtenerSH(x));
    }
}
