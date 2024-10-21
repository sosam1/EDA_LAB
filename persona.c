#include "persona.h"
#include "definiciones.h"
#include <string.h> 

#include <iostream>

using namespace std;

struct tipo_persona{
    Cadena ci;
    Cadena nom;
};

struct nodo_lista_persona{
	ListaPersona sig;
	Persona persona;
};

Persona CrearPersona(Cadena nom, Cadena ci){
    Persona p = new(tipo_persona);
        p->nom=nom;
        p->ci=ci;
        return p;
};

Cadena ObtenerCi(Persona p){
    return p->ci;
};

Cadena ObtenerNom(Persona p){
    return p->nom;
};

Persona ObternerSig(Persona p){
    return p->sig;
}

bool PersonaExisteEnCargo(ListaPersona p, Cadena ci){
    if(p == NULL){
        return false;
    }

    if(strcmp(p->persona->ci, ci) == 0){
        return true;
    }else{
        return PersonaExisteEnCargo(p->sig, ci);
    }
}; 

Persona AgregarPersona(ListaPersona l, Cadena ci, Cadena nom){
    Persona p = new(tipo_persona);
    p->ci = ci;
    p->nom = nom;

    ListaPersona nodo_persona = new(nodo_lista_persona);
    nodo_persona->persona = p;

    nodo_persona = l;
    l->sig = nodo_persona;
};