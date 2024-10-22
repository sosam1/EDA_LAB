#ifndef PERSONA_H
#define PERSONA_H

#include "definiciones.h" 
#include "cargo.h"

typedef struct tipo_persona * Persona;

typedef struct nodo_lista_persona * ListaPersona;

Persona CrearPersona(Cadena nom, Cadena ci);

Cadena ObtenerCi(Persona p);

Cadena ObtenerNom(Persona p);

ListaPersona ObtenerSig(ListaPersona l);

Persona ObtenerPersona(ListaPersona l);

bool PersonaExisteEnCargo(ListaPersona p, Cadena ci);

void AgregarPersona(ListaPersona &l, Cadena ci, Cadena nom);


#endif