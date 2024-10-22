#include "cargo.h"
#include "persona.h"
#include "definiciones.h"
#include <string.h> 

#include <iostream>

using namespace std;

struct nodo_cargo {
    Cadena nombre_cargo;
    Cargo ph;
    Cargo sh;
    ListaPersona personas;
};

struct nodo_lista{
	Lista sig;
	Cadena nombre_cargo;
};


// Implementación de la función que crea un nuevo cargo
Cargo CrearNuevoCargo(Cadena nombre) {
    Cargo c = new(nodo_cargo);
    if (c != NULL) {
        c->nombre_cargo = new(char[MAX_NOMBRE_CARGO]);
        strcpy (c->nombre_cargo, nombre);
        c->ph = NULL;
        c->sh = NULL;
        c->personas = NULL;
    }
    return c;
};

Cadena ObtenerNombreCargo(Cargo c) {
    return c->nombre_cargo;
};

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
};

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
};

Cargo& ObtenerPH(Cargo x){
    return x->ph;
};

Cargo& ObtenerSH(Cargo x){
    return x->sh;
};

void arbol_imprimir_tree_aux(Cargo x){
    if (x != NULL){
        Lista l = NULL; 
        InsertarCargosALista(x, l);

        while(l != NULL) {
        cout << l->nombre_cargo << endl;
        l = l->sig;
        }
    }
};

Lista InsertarCargosALista(Cargo x, Lista &l){ //necesario trabajar con la lista original
    if (x != NULL) {
        Lista aux = new nodo_lista();
        aux->nombre_cargo = x->nombre_cargo;

        if(l==NULL) { //solamente va pasar la primera vez
            aux->sig = NULL;
            l = aux;
            InsertarCargosALista(ObtenerPH(x), l); //este nodo no puede tener hermanos pq es el primero
        }
        else {
            aux->sig = l; //pongo el nuevo nodo en el primer lugar de la lista
            l = aux; // para que apunte al primer elemento de la lista
            InsertarCargosALista(x->ph, l);
            InsertarCargosALista(x->sh, l);
        }        
    }
    return l;
};

void OrdenarAlfabetico(Lista &l) {
    if(l==NULL){
        return;
    } 
    else{
        bool huboCambio = false;
        Lista actual = l;

        while(actual->sig != NULL){
            if (strcmp(actual->nombre_cargo, actual->sig->nombre_cargo) > 0){
                Cadena aux = actual->nombre_cargo;
                actual->nombre_cargo = actual->sig->nombre_cargo;
                actual->sig->nombre_cargo = aux;

                huboCambio = true;
            } 
            actual = actual->sig;
        }

        if(huboCambio){
            OrdenarAlfabetico(l);
        }
    }

    //printf de la lista ordenada
    while(l != NULL){
        printf("%s\n", l->nombre_cargo);
        l=l->sig;
    }
};

void EliminarCargos(Cargo primer_cargo){
    if (primer_cargo != NULL) {
        // Llamar recursivamente a los hijos
        EliminarCargos(primer_cargo->ph); 
        EliminarCargos(primer_cargo->sh); 

        delete[] primer_cargo->nombre_cargo; // liberar la cadena
        delete primer_cargo; // liberar el nodo
    }
};

bool PersonaExisteEnArbol(Cargo c, Cadena ci){
    if(c==NULL){
        return false;
    }
    ListaPersona personas = c->personas;

    while(personas != NULL){
        cout << "Ci del pj: " << ObtenerCi(ObtenerPersona(personas)) << endl;
        if(strcmp(ObtenerCi(ObtenerPersona(personas)), ci) == 0){
            return true;
        }else{
            personas = ObtenerSig(personas);
        }
    }

    return PersonaExisteEnArbol(c->ph, ci) || PersonaExisteEnArbol(c->sh, ci);
};

void InsertarPersonaACargo(Cargo cargo_raiz, Cadena c, Cadena nom, Cadena ci){
    if(!PersonaExisteEnArbol(cargo_raiz, ci)){
        Cargo cargo_para_asignar = ObtenerCargo(cargo_raiz, c); //lo pasamos de cargo a Cadena y luego obtenemos el cargo
        AgregarPersona(cargo_para_asignar->personas,ci, nom);
    }
};
