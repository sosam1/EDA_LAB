// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// empresa.c
// Modulo de Implementacion de la Empresa

#include "empresa.h"
#include "cargo.h"
#include <iostream>
#include <string.h> 

using namespace std;

struct nodo_empresa{
// aquí deben figurar los campos que usted considere necesarios para manipular el organigrama.
// Se deberan crear nuevos modulos e incluirlos.
	Cargo cargo_raiz;
};

Empresa CrearEmpresa(Cargo primerCargo) {
// Crea la empresa con su cargo raiz
// pre: la empresa debe estar vacia.
    Empresa e = new(nodo_empresa);
    if (e != NULL) {
        e->cargo_raiz = primerCargo;
    }
    return e;
}

TipoRet CrearOrg(Empresa &e, Cadena cargo) {
// Inicializa la empresa y crea el primer cargo de la empresa.
// Originalmente la misma debería  estar vacía, en otro caso la operación quedará sin efecto.
	Cargo primerCargo = CrearNuevoCargo(NULL, cargo, NULL);
	e = CrearEmpresa(primerCargo);
	return OK;
}

TipoRet EliminarOrg(Empresa &e){
// Eliminar el organigrama, elimina toda la estructura del organigrama, liberando la memoria asignada.
// Verificar que la empresa no sea nula
	if(e == NULL) {
		return ERROR;
	}
	else {
		EliminarCargos(e->cargo_raiz);
		delete e;
		e = NULL;
	}
    return OK;
}

TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo){
// Insertar un nuevo cargo como dependiente de otro ya existente.
// El nuevo cargo no debe existir en el sistema.
// PRE: la empresa debe estar creada
	if (e == NULL) {
        return ERROR;
    }

	if(!cargoPertenece(e->cargo_raiz, cargoPadre)) { //si el cargo padre no existe da error
		return ERROR;
	}
	else { 
		if(cargoPertenece(e->cargo_raiz, nuevoCargo)) { //si existe el cargo damos error
			return ERROR;
		} 
		else {
			Cargo aux = CrearNuevoCargo(e->cargo_raiz,nuevoCargo, cargoPadre);
			Cargo padre = ObtenerCargo(e->cargo_raiz, cargoPadre); // busca el nodo del cargo en el arbol

			if(ObtenerPH(padre) == NULL) { //si no tiene ningun hijo creamos el cargo ahi
				ObtenerPH(padre) = aux;
			}
			else {
				Cargo iter = ObtenerPH(padre);
				while(ObtenerSH(iter) != NULL) {
					iter = ObtenerSH(iter);
				}
				ObtenerSH(iter) = aux;
			} 
		}
	} 
	return OK;
}

TipoRet EliminarCargo(Empresa &e, Cadena cargo){
// Eliminar un cargo, junto con sus subcargos y personas asociadas.
// Elimina un cargo en la empresa si cargo ya existe en la misma.
// En otro caso la operación quedará sin efecto.
// Si el cargo a eliminar posee subcargos, éstos deberán ser eliminados también, así como
// las personas asociadas a cada uno de los cargos suprimidos.
	if (e == NULL) {
        return ERROR;
    }

	if(!cargoPertenece(e->cargo_raiz, cargo)){
		return ERROR;
	}
	if(strcasecmp(ObtenerNombreCargo(e->cargo_raiz), cargo) == 0){
		return ERROR;
	}else{
		EliminarCargoYSucesores(e->cargo_raiz, cargo);
	}

	return OK;
}

TipoRet ListarCargosAlf(Empresa e){
// Listar todos los cargos ordenados alfabéticamente.
// Lista todos los cargos de la empresa ordenados alfabéticamente por nombre del cargo. 
    if (e == NULL) {
        return ERROR;
    }

	if (e->cargo_raiz != NULL) {
		Lista l = NULL;
		l = InsertarCargosALista(e->cargo_raiz, l); //recorro arbol y guardo todos los cargos en una lista
		OrdenarAlfabetico(l); // ordeno la lista en cuestion
	}
	return OK;
}

TipoRet ListarJerarquia(Empresa e){
// Listar todos los cargos de la empresa en orden jerárquico. 
// Lista todos los cargos de la empresa ordenados por nivel jerárquico e indentados
// según se muestra el ejemplo de la letra.
	if (e == NULL) {
        return ERROR;
    }
	ListarCargosPorJerarquia(e->cargo_raiz, 0);
	return OK;
}

TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci){
// Asignar una persona a un cargo, si este existe.
// Asigna una persona de nombre nom  y cédula de identidad ci al cargo cargo
// siempre que el cargo exista en la empresa y esa persona no este asignada a
// ese u otro cargo, en caso contrario la operación quedará sin efecto.
	if (e == NULL) {
        return ERROR;
    }

	if(!cargoPertenece(e->cargo_raiz, cargo)){
		return ERROR;
	}
	if(PersonaExisteEnArbol(e->cargo_raiz, ci)){
		return ERROR;
	}
	InsertarPersonaACargo(e->cargo_raiz, cargo, nom, ci);
	return OK;  
}

TipoRet EliminarPersona(Empresa &e, Cadena ci){
// Eliminar una persona de un cargo.
// Elimina una persona de cédula ci de la empresa siempre y cuando la misma exista,
// en caso contrario la operación quedará sin efecto.
	if (e == NULL) {
        return ERROR;
    }

	if(!PersonaExisteEnArbol(e->cargo_raiz, ci)){
		return ERROR;
	}
	EliminarPersonaDeCargo(e->cargo_raiz, ci);
	return OK;
}

TipoRet ReasignarPersona(Empresa &e, Cadena cargo, Cadena ci){
// Reasignar una persona a un nuevo cargo.
// Reasigna una persona de la empresa de cédula ci al nuevo cargo de nombre cargo
// siempre que el cargo exista en la empresa y esa persona no este ya asignada a
// dicho cargo. En caso contrario la operación quedará sin efecto.
	if (e == NULL) {
        return ERROR;
    }

	if(!cargoPertenece(e->cargo_raiz, cargo)){
		return ERROR;
	}
	if(!PersonaExisteEnArbol(e->cargo_raiz, ci)){
		return ERROR;
	}
	
	if(PersonaExisteEnCargo(e->cargo_raiz, cargo, ci)){
		return ERROR;
	}

	ReasignarPersonaACargo(e->cargo_raiz, cargo, ci);

	return OK;
}

TipoRet ListarPersonas(Empresa e, Cadena cargo){
// Dado un cargo listar las personas asignadas al mismo ordenadas por fecha de alta a la empresa. 
// Lista todas las personas asignadas al cargo de nombre cargo.
	if (e == NULL) {
        return ERROR;
    }

	if(!cargoPertenece(e->cargo_raiz, cargo)){
		return ERROR;
	}
	ImprimirPersonasEnUnCargo(e->cargo_raiz, cargo);
	return OK;
}

TipoRet ListarSuperCargos(Empresa e, Cadena cargo){
// Dado un cargo listar los cargos que lo anteceden.
// Lista todas los cargos que anteceden, en la jerarquía, al cargo de nombre cargo.
	if (e == NULL) {
        return ERROR;
    }

	if(!cargoPertenece(e->cargo_raiz, cargo)){
		return ERROR;
	}
	ImprimirSuperCargos(e->cargo_raiz, cargo);
	cout << cargo << endl;

	return OK;
}
