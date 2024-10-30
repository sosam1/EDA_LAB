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

void EliminarPersonasDeCargo(Cargo cargo){
    if(cargo->personas != NULL){
        ListaPersona actual = cargo->personas;
        ListaPersona sig;

        while(actual != NULL){
            sig = ObtenerSig(actual);

            cout << "Eliminando a: " << ObtenerNom(ObtenerPersona(actual)) << endl;
            EliminarPersona(ObtenerPersona(actual));

            EliminaListaPersona(actual);

            actual = sig;
        }
    }
};

void EliminarCargos(Cargo primer_cargo){
    if (primer_cargo != NULL) {
        // Llamar recursivamente a los hijos
        EliminarPersonasDeCargo(primer_cargo);
        EliminarCargos(primer_cargo->ph); 
        EliminarCargos(primer_cargo->sh); 

        delete[] primer_cargo->nombre_cargo; // liberar la cadena
        delete primer_cargo; // liberar el nodo
        primer_cargo = NULL;
    }
};

bool PersonaExisteEnArbol(Cargo c, Cadena ci){
    if(c==NULL){
        return false;
    }
    ListaPersona p = c->personas;

    while(p != NULL){
        if(strcmp(ObtenerCi(ObtenerPersona(p)), ci) == 0){
            return true;
        }else{
            p = ObtenerSig(p);
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

void ImprimirPersonasEnUnCargo(Cargo cargo_raiz, Cadena cargo_buscado) {
    Cargo cargo_a_listar = ObtenerCargo(cargo_raiz, cargo_buscado);
    ListaPersona l = cargo_a_listar->personas;
    cout << "Listado de personas asignadas a " << cargo_a_listar->nombre_cargo << ":" << endl;
    cout << "--------------------------------------" << endl;
    ImprimirPersonas(l);
};

Cargo BuscarCargoPorPersona(Cargo raiz, Cadena ci){
    if(raiz==NULL){
        return NULL;
    }

    ListaPersona l = raiz->personas;

    while(l!=NULL){
        if(strcmp(ObtenerCi(ObtenerPersona(l)), ci) == 0){
            return raiz;
        }
        l = ObtenerSig(l);
    }

    //buscar en ph y sh
    Cargo encontradoEnPH = BuscarCargoPorPersona(raiz->ph, ci); 
    if (encontradoEnPH != NULL){
        return encontradoEnPH;
    }

    return BuscarCargoPorPersona(raiz->sh, ci);
};

void EliminarPersonaDeCargo(Cargo raiz, Cadena ci){
    Cargo cargo_donde_esta_perosna = BuscarCargoPorPersona(raiz, ci);
    EliminarPersonaDeLista(cargo_donde_esta_perosna->personas, ci);
}

void ImprimirConIdentacion(Cargo cargo, int nivel){
    for(int x=0; x<nivel; x++){
        cout << "\t";
    }
    cout << cargo->nombre_cargo << " -" << endl;
};

void ListarCargosPorJerarquia(Cargo cargo_raiz, int nivel){
    if(cargo_raiz != NULL){
        ImprimirConIdentacion(cargo_raiz, nivel);

        ListarCargosPorJerarquia(cargo_raiz->ph, nivel+1);
        ListarCargosPorJerarquia(cargo_raiz->sh, nivel);
    }
}

bool CargoAntecesor(Cargo cargo_raiz, Cadena cargo) {
    if (cargo_raiz == NULL) {
        return false; // Si el nodo es NULL, no hay antecesor
    }
    if (strcmp(cargo_raiz->nombre_cargo, cargo) == 0) {
        return true; // Se encontró el cargo buscado
    }
    if (CargoAntecesor(cargo_raiz->ph, cargo)) {
        return true; 
    }

    // Buscar en el hermano (sh)
    return CargoAntecesor(cargo_raiz->sh, cargo);
}

void ImprimirSuperCargos(Cargo cargo_raiz, Cadena cargo) {
    if (cargo_raiz != NULL) {
        if(CargoAntecesor(cargo_raiz->ph, cargo)) { 
            cout << cargo_raiz->nombre_cargo << endl; 
        }
        ImprimirSuperCargos(cargo_raiz->ph, cargo);
        ImprimirSuperCargos(cargo_raiz->sh, cargo);
    }
}

bool PersonaExisteEnCargo(Cargo cargo_raiz, Cadena cargo, Cadena ci){
    Cargo cargo_buscar = ObtenerCargo(cargo_raiz, cargo);
    ListaPersona l = cargo_buscar->personas;

    while(l != NULL){
        if(strcmp(ObtenerCi(ObtenerPersona(l)), ci) == 0){
            return true;
        }
        l = ObtenerSig(l);
    }
    return false;
};

void ReasignarPersonaACargo(Cargo cargo_raiz, Cadena cargo_nuevo_asignar, Cadena ci){
    Cargo cargo_anterior = BuscarCargoPorPersona(cargo_raiz, ci);
    Cargo cargo_nuevo = ObtenerCargo(cargo_raiz, cargo_nuevo_asignar);
    ListaPersona lista_anterior = cargo_anterior->personas;
    Persona aux = NULL;

    bool encontrado = false;
    
    while(lista_anterior != NULL || !encontrado){
        if(strcmp(ObtenerCi(ObtenerPersona(lista_anterior)), ci) == 0){
            //favor no tocar esta linea, les juro que funciona y es extremadamente necesaria y sensible para pasar bien el nombre
            aux = CrearPersona(strcpy(new char[strlen(ObtenerNom(ObtenerPersona(lista_anterior))) + 1], ObtenerNom(ObtenerPersona(lista_anterior))), ci);
            encontrado = true;
        }
        lista_anterior = ObtenerSig(lista_anterior);
    }
    EliminarPersonaDeCargo(cargo_raiz, ci);
    InsertarPersonaACargo(cargo_raiz, cargo_nuevo_asignar, ObtenerNom(aux), ObtenerCi(aux));
};