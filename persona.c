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

ListaPersona ObtenerSig(ListaPersona l){
    return l->sig;
}

Persona ObtenerPersona(ListaPersona l){
    return l->persona;
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

void AgregarPersona(ListaPersona &l, Cadena ci, Cadena nom){
    Persona p = new(tipo_persona);
     // Reservar memoria para las cadenas
    p->ci = new char[strlen(ci) + 1];
    p->nom = new char[strlen(nom) + 1];

    // Copiar los valores de las cadenas
    strcpy(p->ci, ci);
    strcpy(p->nom, nom);

    ListaPersona nodo_persona = new(nodo_lista_persona);
    nodo_persona->persona = p;

    nodo_persona->sig = l;
    l = nodo_persona;
};

void ImprimirPersonas(ListaPersona l){
    if(l==NULL){
        return;
    }
    while(l!=NULL){
        Persona p = ObtenerPersona(l);
        cout << "Nombre: " << p->ci << " CI: " << p->nom << endl; //el main los pasa al reves
        l=l->sig;
    }
};