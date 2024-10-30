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

ListaPersona SnocPersona(ListaPersona &l, Persona p){
    ListaPersona nodo_persona = new(nodo_lista_persona);
    nodo_persona->persona = p;
    nodo_persona->sig = NULL;

    if(l==NULL){
        l=nodo_persona;
        return l;
    }else{
        ListaPersona actual = l;
        while(actual->sig != NULL){
            actual = actual->sig;
        }
        actual->sig = nodo_persona;
    }
    return l;
};

void AgregarPersona(ListaPersona &l, Cadena ci, Cadena nom){
    Persona p = new(tipo_persona);
     // Reservar memoria para las cadenas
    p->ci = new char[strlen(ci) + 1];
    p->nom = new char[strlen(nom) + 1];

    // Copiar los valores de las cadenas
    strcpy(p->ci, ci);
    strcpy(p->nom, nom);

    SnocPersona(l, p);
};

void ImprimirPersonas(ListaPersona l){
    if(l==NULL){
        return;
    }
    while(l!=NULL){
        Persona p = ObtenerPersona(l);
        cout << "Nombre: " << p->nom << " CI: " << p->ci << endl;
        l=l->sig;
    }
};

void EliminarPersona(Persona p){
    delete[] p->nom;
    delete[] p->ci;
    delete p;
};

void EliminaListaPersona(ListaPersona l){
    delete l;
};

void EliminarPersonaDeLista(ListaPersona &lista, Cadena ci) {
    ListaPersona actual = lista;
    ListaPersona anterior = NULL;

    // Buscar el nodo que contiene la CI de la persona a eliminar
    while (actual != NULL && strcmp(ObtenerCi(ObtenerPersona(actual)), ci) != 0) {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual != NULL) { // Nodo encontrado
        if (anterior == NULL) { // Si es el primer nodo de la lista
            lista = actual->sig;
        } else {
            anterior->sig = actual->sig; // Saltamos el nodo en la lista
        }

        EliminarPersona(ObtenerPersona(actual)); // Elimina los datos de la persona
        EliminaListaPersona(actual); // Elimina el nodo
    }
}
